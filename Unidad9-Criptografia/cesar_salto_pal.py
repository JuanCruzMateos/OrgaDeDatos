#! /usr/bin/python3
from pprint import pprint
from string import ascii_lowercase


def encriptar(alpha: str, valor_letra: dict, letra_valor: dict, p_key: str, salto: int, msg: str) -> str:
    p_clave_sin_dup = ''.join(
        sorted(set(p_key), key=p_key.index))

    dic = {}
    for i, c in enumerate(p_clave_sin_dup):
        dic[letra_valor[salto + i]] = c

    pos = salto+i+1
    for _, char in enumerate(alpha):
        if char not in dic.values():
            if pos == len(alpha):
                pos = 0
            dic[letra_valor[pos]] = char
            pos += 1

    encrip = ""
    for char in msg:
        encrip += " " if char == " " else dic[char]
    return encrip


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")

    valor_letra = dict(zip(alpha, range(len(alpha))))
    letra_valor = dict(zip(range(len(alpha)), alpha))

    palabra_clave = "amor"
    salto = 8
    mensajes = ["lo esencial es invisible a los ojos",
                "la g de gnu hace a la definicion recursiva"]
    for msg in mensajes:
        e = encriptar(alpha, valor_letra, letra_valor,
                      palabra_clave, salto, msg)
        print(e.upper())

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
