#! /usr/bin/python3

def main(args):
    if (len(args) == 1):
        claves = ["limon", "gato", "vodka", "ojo",
                  "ojota", "caradura", "caradura", "ah"]
    else:
        claves = args[1:]

    M = 509
    for key in claves:
        print(f"clave = {key}")
        xor = ord(key[0])
        binary = bin(ord(key[0])).replace("0b", "")
        print(f"{key[0]}: {binary}")
        for char in key[1:]:
            binary = bin(ord(char)).replace("0b", "")
            print(f"{char}: {binary}")
            xor = xor ^ ord(char)
        print(f"xor mod {M} = {xor % M}", end="\n\n")


if __name__ == "__main__":
    import sys
    main(sys.argv)
