#! /usr/bin/python3
from string import ascii_lowercase
from pprint import pprint


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")
    valor_letra = dict(zip(alpha, range(1, len(alpha))))
    letra_valor = dict(zip(range(1, len(alpha)), alpha))

    key = "fe"
    msg = "hoy es el dia"

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
    print(encrip)


if __name__ == "__main__":
    main()
