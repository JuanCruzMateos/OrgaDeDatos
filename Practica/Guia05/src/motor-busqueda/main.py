#! /usr/bin/python3
# Juan Cruz Mateos
import os
import re


def parse(dic: dict, filename: str) -> None:
    """Lee el archivo y guarda en dic las palabras con su frecuencia y el nombre del archivo al que pertenecen"""
    with open(filename, "rt") as file:
        lista = file.read().split()
        arr = [re.sub("[\W_]+", "", palabra).upper() for palabra in lista]
        for palabra in arr:
            donde = dic.get(palabra, None)
            if not donde:
                dic[palabra] = {filename: 1}
            else:
                donde[filename] = donde.get(filename, 0) + 1


def main(args: list) -> None:
    palabras = {}
    base = "./" if len(args) == 1 else args[1]
    for root, _, files in os.walk(base):
        for name in files:
            if name != os.path.basename(__file__) and name[-4:] == ".txt":
                parse(palabras, os.path.join(root, name))
    res = 'y'
    while res == 'y':
        ask = input("palabra = ")
        if ask.upper() not in palabras:
            print("No existe la palabra={} en el directorio {}".format(ask, base))
        else:
            for archivo, frecuencia in palabras[ask.upper()].items():
                print(f"file={archivo:<35s} frec={frecuencia}")
        res = input("\nBuscar otra palabra? y/n ")


if __name__ == "__main__":
    import sys
    main(sys.argv)
