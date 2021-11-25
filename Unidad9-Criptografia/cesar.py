#! /usr/bin/python3
from string import ascii_lowercase
from string import ascii_uppercase
from pprint import pprint


def encriptar(alpha: list, shift: int, msg: str) -> str:
    values = alpha[shift:] + alpha[:shift]
    dic = dict(zip(alpha, values))
    # pprint(dic)

    encript = ""
    for char in msg:
        # encript += " " if char == " " else dic[char]
        encript += dic[char]
    return encript


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")

    upper = [char for char in ascii_uppercase]
    upper.insert(14, "Ñ")

    complete = upper + alpha
    complete.append("á")
    complete.append("é")
    complete.append("í")
    complete.append("ó")
    complete.append("ú")
    complete.append(" ")
    complete.append(",")
    complete.append(".")
    # pprint(complete)
    shift = 7
    msg = "En general, los hombres juzgan más por los ojos que por la inteligencia, pues todos pueden ver, pero pocos comprenden lo que ven."

    # values = alpha[shift:] + alpha[:shift]
    # dic = dict(zip(alpha, values))

    # for char in msg:
    #     print(dic[char], end="")
    # print()

    # print(encriptar(alpha, shift, msg))
    print(encriptar(complete, shift, msg))


if __name__ == "__main__":
    main()
