img = open("img.kif", "w")

width = 640
height = 640

img.write(f"{width}x{height}=\n");
for i in range(0, width * height):
    img.write("00FF00; ")
