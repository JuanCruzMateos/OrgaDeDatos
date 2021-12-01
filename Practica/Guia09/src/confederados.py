#! /usr/bin/python3
# @author Juan Cruz Mateos
from string import ascii_lowercase
from string import ascii_uppercase
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


def desencriptar(alpha: list, valor_letra: dict, letra_valor: dict, key: str, msg: str) -> str:
    i = 0
    desencrip = ""
    for char in msg:
        if i == len(key):
            i = 0
        if char == " ":
            desencrip += " "
        else:
            p = valor_letra[char] - valor_letra[key[i]]
            if p < 1:
                p += len(alpha)
            i += 1
            desencrip += letra_valor[p]
    return desencrip


def main():
    lower = [char for char in ascii_lowercase]
    lower.insert(14, "ñ")
    upper = [char for char in ascii_uppercase]
    upper.insert(14, "Ñ")
    complete = lower + upper
    complete += list("áéíóú,;.")

    valor_letra = dict(zip(complete, range(1, len(complete) + 1)))
    letra_valor = dict(zip(range(1, len(complete) + 1), complete))

    key = "NoTenemosClave"
    mensajes = ["El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."]
    enc_noe = "kA WnswnsI ,ftwwL tf zAf pt EDE upháxWfG qfI MLxqHj;ñ WtAxuINH pñ ÑjRBcpñEnH vDob Hj.HU uCw BJLD CvA xR t.hIjzJLD Gñ JbZtet snvE wH BpOnPxbrrx yiM DofHfáJYe"

    for msg in mensajes:
        encrip = encriptar(complete, valor_letra, letra_valor, key, msg)
        print(encrip)
        print(enc_noe == encrip)

    noe_msg = desencriptar(complete, valor_letra, letra_valor, key, enc_noe)
    print(noe_msg)
    print(noe_msg == mensajes[0])


if __name__ == "__main__":
    main()
