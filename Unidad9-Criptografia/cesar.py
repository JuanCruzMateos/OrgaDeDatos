#! /usr/bin/python3

from string import ascii_lowercase
from pprint import pprint


def main():
    alpha = [char for char in ascii_lowercase]
    alpha.insert(14, "ñ")

    shift = 15
    values = alpha[shift:] + alpha[:shift]
    dic = dict(zip(alpha, values))

    msg = "pedro"
    for char in msg:
        print(dic[char], end="")
    print()


if __name__ == "__main__":
    main()
