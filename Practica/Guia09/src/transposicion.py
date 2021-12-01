#! /usr/bin/python3
from string import ascii_lowercase
from string import ascii_uppercase


def main():
    i = 0

    msg = "El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."

    bigList = []
    mylist = []
    for letra in msg:
        mylist.append(letra)
        i += 1
        if i == 5:
            bigList.append(mylist)
            mylist = []
            i = 0
    while i != 0 and i < 5:
        mylist.append("")
        i += 1
    bigList.append(mylist)

    print(bigList)

    orden = [5, 2, 1, 3, 4]

    codificado = ""
    i = 0
    for lista in bigList:
        for i in range(5):
            codificado += lista[orden[i]-1]

    print("\n\n")
    print(codificado)


if __name__ == "__main__":
    main()
