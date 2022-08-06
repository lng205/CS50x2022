from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

ls = []
for i in range(height + 2):
    ls.append(" ")
for i in range(height):
    ls[height - 1 - i] = "#"
    ls.append("#")
    print("".join(ls))