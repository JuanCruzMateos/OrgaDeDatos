#! /usr/bin/python3

def main():
    claves = ["limon", "gato", "vodka", "ojo",
              "ojota", "caradura", "caradura", "ah"]

    M = 512
    for key in claves:
        print(f"clave = {key}")
        xor = ord(key[0])
        print(f"{key[0]}: {bin(ord(key[0]))}")
        for char in key[1:]:
            print(f"{char}: {bin(ord(char))}")
            xor = xor ^ ord(char)
        print(f"xor mod {M} = {xor % M}", end="\n\n")


if __name__ == "__main__":
    main()
