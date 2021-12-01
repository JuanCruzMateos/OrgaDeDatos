#! /usr/bin/python3
# @author Juan Cruz Mateos
from string import ascii_lowercase
from string import ascii_uppercase
from pprint import pprint


def split_by(msg: str, x: int) -> list:
    return [msg[i:i+x] for i in range(0, len(msg), x)]


def create_tables(alphabet: list) -> tuple:
    m = {
        v: {
            v: alphabet[i+pos] if i+pos < len(alphabet) else alphabet[i + pos - len(alphabet)] for i, v in enumerate(alphabet)
        } for pos, v in enumerate(alphabet)
    }

    n = {
        v: {
            v: alphabet[i+pos] if i+pos < len(alphabet) else alphabet[i + pos - len(alphabet)] for i, v in enumerate(alphabet)
        } for pos, v in enumerate(alphabet)
    }
    return m, n


def enciptar(m: dict, key: str, msg: str) -> str:
    sin_espacios = msg.replace(" ", "")
    frase_en_grupos = split_by(sin_espacios, len(key))

    encript = ""
    for grupo in frase_en_grupos:
        for fila, col in zip(key, grupo):
            encript += m[fila][col]

    arr = [c for c in encript]
    for i in range(len(msg)):
        if msg[i] == " ":
            arr.insert(i, " ")
    return "".join(arr)


def desencriptar(m: dict, key: str, msg: str) -> str:
    sin_espacios = msg.replace(" ", "")
    frase_en_grupos = split_by(sin_espacios, len(key))

    decrypt = ""
    for grupo in frase_en_grupos:
        for fila, col in zip(key, grupo):
            vals = list(m[fila].values())
            i = 0
            while m[fila][vals[i]] != col:
                i += 1
            decrypt += vals[i]

    arr = [c for c in decrypt]
    for i in range(len(msg)):
        if msg[i] == " ":
            arr.insert(i, " ")
    return "".join(arr)


def main():
    lower = [char for char in ascii_lowercase]
    lower.insert(14, "ñ")
    upper = [char for char in ascii_uppercase]
    upper.insert(14, "Ñ")
    complete = lower + upper
    complete += list("áéíóú,;.")

    # pos = 0
    # d = {
    #     v: complete[i+pos] if i+pos < len(complete) else complete[i + pos - len(complete)] for i, v in enumerate(complete)
    # }
    # pprint(d)

    key = "Ventilado"
    m, _ = create_tables(complete)

    mensajes = ["El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."]
    noe = "ro oBnCagD p,Ftzi ev Jae px sls wiXquviD móH gmyJsosb qcqFBAEe hB fiqFxvaCof gnwi vewGV tBL wErd Fii Fx mxcxsaxEt Cx n.AZvB ypto gs dsFBksopsg pfM iñeñoaxqs"

    for msg in mensajes:
        enc = enciptar(m, key, msg)
        print(enc)
        print(enc == noe)

    noe_msg = desencriptar(m, key, noe)
    print(noe_msg)
    print(noe_msg == mensajes[0])


if __name__ == "__main__":
    main()
