#! /usr/bin/python3
# @author Juan Cruz Mateos
from string import ascii_lowercase
from string import ascii_uppercase
from pprint import pprint


def encriptar(alpha: list, shift: int, msg: str) -> str:
    values = alpha[shift:] + alpha[:shift]
    dic = dict(zip(alpha, values))

    encript = ""
    for char in msg:
        encript += " " if char == " " else dic[char]
        # encript += dic[char]
    return encript


def desencriptar(alpha: list, shift: int, msg: str) -> str:
    values = alpha[shift:] + alpha[:shift]
    dic = dict(zip(values, alpha))

    decript = ""
    for char in msg:
        decript += " " if char == " " else dic[char]
    return decript


def main():
    lower = [char for char in ascii_lowercase]
    lower.insert(14, "ñ")
    upper = [char for char in ascii_uppercase]
    upper.insert(14, "Ñ")
    complete = lower + upper
    complete += list("áéíóú,;.")

    shift = 10
    msg = "El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."
    noe = "Ñu mroBkny MdCkBh ñC Ewk nñ ukC DdmwrmkC vcC CrvzuñCi mywCrCDñ ñw BññvzukJkB mknk uñDBk zyB yDBk AEñ Cñ ñwmEñwDBk Ew wgvñBy orsy nñ zyCrmrywñC vcC knñukwDñj"

    # print(encriptar(complete, shift, msg))
    noe_msg = desencriptar(complete, shift, noe)
    print(noe_msg)
    print(msg == noe_msg)


if __name__ == "__main__":
    main()
