#! /usr/bin/python3
# @author Juan Cruz Mateos
from pprint import pprint
from string import ascii_lowercase
from string import ascii_uppercase
from string import digits


def generate_dicts(alphabet: list, palabra_clave: str, salto: int) -> tuple:
    encode = {}
    decode = {}

    # valor_letra = dict(zip(alphabet, range(len(alphabet))))
    letra_valor = dict(zip(range(len(alphabet)), alphabet))

    p_clave_sin_dup = ''.join(
        sorted(set(palabra_clave), key=palabra_clave.index))
    for i, c in enumerate(p_clave_sin_dup):
        encode[letra_valor[salto + i]] = c
        decode[c] = letra_valor[salto + i]

    pos = salto + i + 1
    for _, char in enumerate(alphabet):
        if char not in encode.values():
            if pos == len(alphabet):
                pos = 0
            encode[letra_valor[pos]] = char
            decode[char] = letra_valor[pos]
            pos += 1
    return encode, decode


def cesar(code: dict, msg: str) -> str:
    modif = ""
    for char in msg:
        modif += " " if char == " " else code[char]
    return modif


def main():
    # lower = [char for char in ascii_lowercase]
    # lower.insert(14, "ñ")
    upper = [char for char in ascii_uppercase]
    # upper.insert(14, "Ñ")
    numbers = [nro for nro in digits]

    complete = upper + numbers
    # complete += list("áéíóú,;.")

    palabra_clave = "MURCIELAGO"
    # salto = 5

    # msg = "El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."
    # noe = "va ,RSió;f tWjóiá .j lcó ;. aój kW,cR,ój bVj jRbga.jé ,fcjRjk. .c i..bgaóqói ,ó;ó a.kió gfi fkió hl. j. .c,l.ckió lc cZb.if SRTf ;. gfjR,Rfc.j bVj ó;.aóck.í"

    enc = "18 EX8LU 01 Z1EXI 1IX JN D 8X Z8XG1 9AIZ518X3U"
    # noe_msg = cesar(decode, noe)
    # print(noe_msg)
    # yo_enc = cesar(encode, msg)

    # print(msg == noe_msg)
    # print(yo_enc == noe)

    for i in range(len(complete)-1):
        encode, decode = generate_dicts(complete, palabra_clave, i)
        print(f"test({i}) {cesar(decode, enc)}\n")

    # p_clave_sin_dup = ''.join(
    #     sorted(set(palabra_clave), key=palabra_clave.index))
    # print(p_clave_sin_dup)

    # dic = {}
    # for i, c in enumerate(p_clave_sin_dup):
    #     dic[letra_valor[salto + i]] = c

    # pos = salto+i+1
    # for _, char in enumerate(alpha):
    #     if char not in dic.values():
    #         if pos == len(alpha):
    #             pos = 0
    #         dic[letra_valor[pos]] = char
    #         pos += 1

    # for c in alpha:
    #     print(c, dic[c])


if __name__ == "__main__":
    main()
