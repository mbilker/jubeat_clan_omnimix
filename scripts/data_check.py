"""
This script validates a jubeat omni/ultimate install for mdb validity.
It ensures that each song in the mdb has a matching
- Thumbnail jacket
- Fullsize jacket
- Audio file
- Chart file

It also notes any songs that have files but don't exist in the mdb
"""

import functools
import itertools
import os
import re
import struct
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Generator

from ifstools import IFS
from kbinxml import KBinXML
from tqdm import tqdm

# whether to print info for each song, or just a summary
VERBOSE = False
# if not None, will create a new mdb with broken songs filtered out
# SAVE_FILTERED_MDB = "./music_ulti_fix.xml"
SAVE_FILTERED_MDB = None
# will need to be changed for different game versions
BANNER_THUMB_REGEX = re.compile(r"^tex_l44fo_bnr_j_.*\.bin", re.IGNORECASE)


@dataclass
class Song:
    music_id: str
    title_name: str
    genre: str


# https://stackoverflow.com/a/32775270/7972801
def readcstr(f):
    toeof = iter(functools.partial(f.read, 1), b"")
    return b"".join(itertools.takewhile(b"\0".__ne__, toeof))


def unpack_f(fmt, f):
    return struct.unpack(fmt, f.read(struct.calcsize(fmt)))


@dataclass
class FS:
    base: Path
    mdb_suffix: str | None = None

    def __post_init__(self):
        base = self.base / "data_mods"
        self._mods = [
            m for m in os.listdir(base) if m != "_cache" and os.path.isdir(base / m)
        ]
        print(f"FS loaded with {self._mods=}")

    @property
    def _basedirs(self) -> Generator[Path, None, None]:
        for m in self._mods:
            yield Path("data_mods") / m

        yield Path("data")

    def find_path(self, path: str):
        for subdir in self._basedirs:
            attempt = self.base / subdir / path
            if os.path.exists(attempt):
                return attempt

        raise FileNotFoundError(f'Path "{path}" not found in any mods nor base data')

    def find_paths_regex(self, base: str, regex: re.Pattern):
        res: set[str] = set()
        for subdir in self._basedirs:
            subdir = self.base / subdir / base
            if not os.path.isdir(subdir):
                continue
            for f in os.listdir(subdir):
                if regex.match(f):
                    res.add(f"{base}/{f}")

        return res

    def open(self, path: str, mode="rb", log=False, **kwargs):
        for subdir in self._basedirs:
            try:
                f = open(self.base / subdir / path, mode, **kwargs)
                if log:
                    print(f"Opened {subdir / path}")
                return f
            except FileNotFoundError:
                continue

        raise FileNotFoundError(f'Path "{path}" not found in any mods nor base data')

    def open_mdb(self):
        suffix = f"_{self.mdb_suffix}" if self.mdb_suffix else "_info"
        return self.open(f"music_info/music{suffix}.xml", log=True)

    def load_mdb(self) -> list[Song]:
        with self.open_mdb() as f:
            xml = KBinXML(f.read()).xml_doc

            songs = []
            for song in xml.findall("./body/data"):
                genres = (
                    "pops",
                    "anime",
                    "socialmusic",
                    "UMU",
                    "game",
                    "classic",
                    "original",
                    "toho",
                )
                genre = "/".join(
                    g for g in genres if song.find(f"./genre/{g}").text == "1"
                )
                songs.append(
                    Song(
                        music_id=song.find("music_id").text,
                        title_name=song.find("title_name").text,
                        genre=genre,
                    )
                )

        print(f"Loaded {len(songs)} songs from mdb")
        return songs

    def filter_mdb(self, dest: str, bad_ids: set[str]):
        with self.open_mdb() as f:
            xml = KBinXML(f.read())

        data_num = 0
        for song in xml.xml_doc.findall("./body/data"):
            music_id = song.find("music_id").text
            if music_id in bad_ids:
                song.getparent().remove(song)
            else:
                data_num += 1

        xml.xml_doc.find("./header/data_num").text = str(data_num)

        with open(dest, "w") as f:
            f.write(xml.to_text())

    def _load_plkt(self, path):
        with self.open(path) as f:
            magic, _total_sz, count = unpack_f("<4sI8xI12x", f)
            if magic != b"TLKP":
                raise ValueError(
                    f'Packlist "{path}" is corrupt, magic should be "TKLP" but was {magic}'
                )

            offsets = []
            for _ in range(count):
                offsets.append(unpack_f("<I", f)[0])

            strings: list[str] = []
            for offset in offsets:
                if offset == 0:
                    continue

                f.seek(offset)
                strings.append(readcstr(f).decode())

        return strings

    def load_packlist(self):
        prefix = self.mdb_suffix or "pack"
        path = f"d3/package/{prefix}list.bin"
        print(f"Loading packlist at {path}")
        packs = self._load_plkt(path)

        texnames = set()
        for pack in packs:
            path = f"d3/package/{pack}"
            print(f"Adding texture names from {path}")
            for tex in self._load_plkt(path):
                if tex in texnames:
                    raise ValueError(f"Texname {tex} is duplicated")
                texnames.add(tex)

        return texnames

    def _load_texbin_names(self, path: str):
        names: set[str] = set()
        with self.open(path) as f:
            magic, name_offset = unpack_f("<4s8x4x4x4x4x4x4x16xI", f)
            if magic != b"PXET":
                raise ValueError(
                    f'Texbin "{path}" is corrupt, magic should be "PXET" but was {magic}'
                )

            f.seek(name_offset)
            magic, names_count = unpack_f("<4s4x8xI2x2x4x", f)

            offsets = []
            for _ in range(names_count):
                _hash, _id, str_offset = unpack_f("<III", f)
                offsets.append(str_offset)

            for offset in offsets:
                f.seek(name_offset + offset)
                names.add(readcstr(f).decode())

        return names

    def load_banner_thumbs(self):
        res: set[str] = set()
        all_thumbs = self.find_paths_regex("d3/model", BANNER_THUMB_REGEX)
        if self.mdb_suffix != "ulti":
            all_thumbs = [f for f in all_thumbs if "_ul_" not in f and "_ex_" not in f]
            if self.mdb_suffix != "omni":
                all_thumbs = [f for f in all_thumbs if "_om_" not in f]

        for path in sorted(all_thumbs):
            print(f"Loading banner thumbs from {path}")
            res.update(self._load_texbin_names(path))

        return res


def main():
    if len(sys.argv) not in (2, 3):
        print("Usage: data_check.py JUBEAT_FOLDER [mdb_suffix]")
        print("")
        print("Example: data_check.py C:/games/jubeat ulti")
        exit(1)

    src = sys.argv[1]
    mdb_suffix = None
    if len(sys.argv) == 3:
        mdb_suffix = sys.argv[2]

    fs = FS(base=Path(src), mdb_suffix=mdb_suffix)
    mdb = fs.load_mdb()
    textures = fs.load_packlist()
    banner_thumbs = fs.load_banner_thumbs()

    total_errs = 0
    song_errs = 0
    all_errs = defaultdict(int)
    bad_ids: set[str] = set()

    for song in tqdm(mdb, desc="Checking songs..."):
        errors = []

        def err_both(msg: str):
            errors.append(msg)
            all_errs[msg] += 1

        ifs_path = f"ifs_pack/d{song.music_id[:-1]}/{song.music_id}_msc.ifs"
        ifs_abspath = None
        try:
            ifs_abspath = fs.find_path(ifs_path)
        except FileNotFoundError:
            errors.append(f"No IFS file, should be at {ifs_path}")
            all_errs["No IFS file"] += 1

        if ifs_abspath:
            ifs = IFS(fs.find_path(ifs_path))
            files = ifs.tree.files
            for file, msg in (
                ("bsc.eve", "No basic chart"),
                ("adv.eve", "No advanced chart"),
                ("ext.eve", "No extreme chart"),
                ("idx.bin", "No preview audio"),
                ("bgm.bin", "No bgm audio"),
            ):
                if file not in files:
                    err_both(msg)

        mdl_name = f"mdl_l44_bnr_big_id{song.music_id}.bin"
        # This fails for many stock songs, probably not an issue
        # if mdl_name not in textures:
        #     err_both(f"Big banner .mdl not referenced in any packlists")
        try:
            mdl_path = f"d3/model/{mdl_name}"
            fs.find_path(mdl_path)
        except FileNotFoundError:
            errors.append(f"No jacket .mdl file, should be at {mdl_path}")
            all_errs["No jacket .mdl"] += 1

        tex_name = f"tex_l44_bnr_big_id{song.music_id}.bin"
        # This fails for many stock songs, probably not an issue
        # if tex_name not in textures:
        #     err_both(f"Big banner .bin not referenced in any packlists")
        try:
            tex_path = f"d3/model/{tex_name}"
            fs.find_path(tex_path)
        except FileNotFoundError:
            errors.append(f"No jacket .tex file, should be at {tex_path}")
            all_errs["No jacket .tex"] += 1

        bnr_thumb = f"BNR_ID{song.music_id}"
        bnr_title = f"IDX_ID{song.music_id}"
        bnr_title_thumb = f"IDX_MINI_ID{song.music_id}"

        if bnr_thumb not in banner_thumbs:
            err_both("No jacket thumbnail")
        if bnr_title not in banner_thumbs:
            err_both("No song title texture")
        if bnr_title_thumb not in banner_thumbs:
            err_both("No song title thumbnail")

        if errors:
            bad_ids.add(song.music_id)
            song_errs += 1
            if VERBOSE:
                tqdm.write(
                    f"FAIL: {song.music_id} ({song.title_name}), genres: {song.genre or 'NONE'}"
                )
            for error in errors:
                total_errs += 1
                if VERBOSE:
                    tqdm.write(f"  {error}")

    print(f"Found {total_errs} issues from {song_errs}/{len(mdb)} songs")
    for msg, count in all_errs.items():
        print(f"  {msg}: {count}")

    if SAVE_FILTERED_MDB:
        print(f"Creating filtered mdb and saving to {SAVE_FILTERED_MDB}")
        fs.filter_mdb(SAVE_FILTERED_MDB, bad_ids)


if __name__ == "__main__":
    main()
