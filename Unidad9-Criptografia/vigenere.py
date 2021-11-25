#! /usr/bin/python3
from string import ascii_lowercase
from pprint import pprint


def split_by(msg: str, x: int) -> list:
    return [msg[i:i+x] for i in range(0, len(msg), x)]


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")

    # pos = 0
    # d = {
    #     v: alpha[i+pos] if i+pos < len(alpha) else alpha[i + pos - len(alpha)] for i, v in enumerate(alpha)
    # }
    # pprint(d)

    m = {
        v: {
            v: alpha[i+pos] if i+pos < len(alpha) else alpha[i + pos - len(alpha)] for i, v in enumerate(alpha)
        } for pos, v in enumerate(alpha)
    }

    key = "organizacion"
    # msg = "organizacion de datos es una materia de tercer año"
    msg = "ingenieria en informatica es una carrera en auge"

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
    final = "".join(arr)
    print(final)


if __name__ == "__main__":
    main()
