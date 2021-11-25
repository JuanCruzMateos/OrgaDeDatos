#! /usr/bin/python3
from string import ascii_lowercase
from pprint import pprint


def encriptar(alpha: list, shift: int, msg: str) -> str:
    values = alpha[shift:] + alpha[:shift]
    dic = dict(zip(alpha, values))

    encript = ""
    for char in msg:
        encript += " " if char == " " else dic[char]
    return encript


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")

    shift = 15
    msg = "pedro"

    # values = alpha[shift:] + alpha[:shift]
    # dic = dict(zip(alpha, values))

    # for char in msg:
    #     print(dic[char], end="")
    # print()

    print(encriptar(alpha, shift, msg))


if __name__ == "__main__":
    main()
