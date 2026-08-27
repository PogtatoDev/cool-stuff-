from PIL import Image
import os, sys

for input in sys.argv[1:]:
    f, e = os.path.splitext(input)
    out = f + ".kif"
    if input != out:
        img = Image.open(input).convert('RGB')
        pixels = img.get_flattened_data()
        hex_list = [f"#{r:02x}{g:02x}{b:02x}" for (r, g, b) in pixels]
        resolution = img.size
        img = open(out, "w")

        img.write(f"{resolution[0]}x{resolution[1]}=\n")

        for hex in hex_list:
            img.write(hex[1:].upper())
            img.write(";")
