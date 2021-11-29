#! /usr/bin/python3
# Juan Cruz Mateos
from sys import argv


def main(args):
    if (len(args) == 1):
        claves = ["limon", "gato", "vodka", "ojo",
                  "ojota", "caradura", "caradura", "ah"]
        M = 509
    else:
        M = int(argv[1])
        claves = args[2:]

    for key in claves:
        print(f"clave = {key}")
        xor = ord(key[0])
        binary = bin(ord(key[0])).replace("0b", "")
        print(f"{key[0]}: {binary}")
        for char in key[1:]:
            binary = bin(ord(char)).replace("0b", "")
            print(f"{char}: {binary}")
            xor = xor ^ ord(char)
        print(f"xor = {xor}")
        print(f"{xor} mod {M} = {xor % M}", end="\n\n")


if __name__ == "__main__":
    import sys
    main(sys.argv)
