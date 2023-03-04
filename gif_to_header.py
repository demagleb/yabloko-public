from PIL import Image 
import sys

def convert_to_256(pixel):
    # hardcode a few colors
    if pixel == (255, 255, 255):
        return 0x0f
    if pixel == (43, 37, 37):
        return 0x13
    if pixel == (80, 70, 70):
        return 0x15
    if pixel == (91, 140, 181):
        return 0x96
    if pixel == (214, 154, 124):
        return 0x41
    if pixel == (252, 201, 167):
        return 0x59
    if pixel == (253, 214, 187):
        return 0x5a
    if pixel == (198, 97, 68):
        return 0x2A # bad
    
    
    print(pixel)
    raise Exception() 

def parse_file(filename):
    img = Image.open(filename).convert("RGB")
    res = []
    for i in range(img.width):
        for j in range(img.height):
            res.append(convert_to_256(img.getpixel((i, j)))) 
    return res


def make_header():
    sys.stdout = open("gif.h", "w")
    frames = 4
    width = 200
    height = 200
    print(f"int n_frames = {frames};")
    print(f"int width = {width};")
    print(f"int height = {height};")


def make_bin():
    sys.stdout = open("gif.bin", "wb")
    for i in range(1, 5):
        arr = parse_file(f"gif/{i}.bmp")
        arr = bytearray(arr)
        sys.stdout.write(arr)
make_header()
make_bin()