#! /usr/bin/python3
# @author Juan Cruz Mateos
from string import ascii_lowercase
from pprint import pprint


def encriptar(alpha: list, valor_letra: dict, letra_valor: dict, key: str, msg: str) -> str:
    i = 0
    encrip = ""
    for char in msg:
        if i == len(key):
            i = 0
        if char == " ":
            encrip += " "
        else:
            p = valor_letra[char] + valor_letra[key[i]]
            if p > len(alpha):
                p -= len(alpha)
            i += 1
            encrip += letra_valor[p]
    return encrip


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")
    valor_letra = dict(zip(alpha, range(1, len(alpha))))
    letra_valor = dict(zip(range(1, len(alpha)), alpha))

    # key = "fe"
    # msg = "hoy es el dia"
    # encrip = NTE JY JQ IÑF

    # msg = "el unico modo de hacer un gran trabajo es amar lo que haces"
    # ua gvkle ceox fn wqrpa wv vipy ctjqqya nu jbqh wx sdt xpñnu
    # msg = "es muy simple"
    # ui xda bxcfwn

    key = "polibio"
    mensajes = [
        "el unico modo de hacer un gran trabajo es amar lo que haces", "es muy simple"]
    for msg in mensajes:
        encrip = encriptar(alpha, valor_letra, letra_valor, key, msg)
        print(encrip.upper())


if __name__ == "__main__":
    main()
