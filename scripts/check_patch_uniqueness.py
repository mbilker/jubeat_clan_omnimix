from tqdm import tqdm

# patch = bytes.fromhex('69 35 E8 41 3E 10 14 20 01 00 33 C0 B9')
# mask =  bytes.fromhex('ff ff 00 00 00 00 ff ff ff ff ff ff ff')# 00 00 00 ff ff')

# fmt: off
patch = [0x69, 0x35, 0xE8, 0x41, 0x3E, 0x10, 0x14, 0x40, 0x02, 0x00, 0x33, 0xC0, 0xB9]
mask =  [   1,    1,    0,    0,    0,    0,    0,    0,    0,    0,    1,    1,    1]
# fmt: on

# mask = [1 for _ in range(len(patch))]

dll = "../../../jubeat/modules/sequence.dll"
with open(dll, "rb") as f:
    dll = f.read()

matches = 0
for i in tqdm(range(len(dll))):
    slc = dll[i : i + len(patch)]
    ok = True
    for p, m, s in zip(patch, mask, slc):
        if m and p != s:
            ok = False
            break

    if ok:
        tqdm.write(f"Match at 0x{i:X}")
        matches += 1

print(f"Total matches: {matches}")
print("patch: " + ", ".join(f"0x{x:02X}" for x in patch))
print("mask:  " + ", ".join(f"{1 if x else 0: 4d}" for x in mask))
