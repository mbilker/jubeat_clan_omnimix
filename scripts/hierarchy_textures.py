import string
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

out = Path("tex_l44fo_smc_mm_hierarchy_ul")
font_file = "DFPHSMaruGothic-W4.ttf"
pt = 11
w = 144
h = 20

lines = [
    ("Ultimate", "UL_ARCH_ULTIMATE"),
    ("Omnimix", "UL_ARCH_OMNIMIX"),
    ("Jubeat Plus", "UL_ARCH_JUBEAT_PLUS"),
    ("Jukebeat", "UL_ARCH_JUKEBEAT"),
    ("Western Music", "UL_ARCH_WESTERN"),
    ("0-9", "UL_ARCH_0_9"),
    *[(l, f"UL_ARCH_{l}") for l in string.ascii_uppercase],
]

out.mkdir(exist_ok=True)

font = ImageFont.truetype(font_file, 14)

for text, name in lines:
    img = Image.new("RGBA", (144, 20))
    draw = ImageDraw.Draw(img)
    bbox = draw.textbbox((0, 0), text, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    x = (img.width - text_width) // 2
    y = (img.height - text_height) // 2
    draw.text((x, y), text, font=font, fill="white")

    img.save(out / f"{name}_JA.png")
