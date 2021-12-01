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

    orden = [5, 2, 1, 3, 4]
    orden2 = [item-1 for item in orden]
    # print(bigList)

    codificado = ""
    i = 0
    for lista in bigList:
        for i in range(5):
            codificado += lista[orden2[i]]

    print("\n\n")
    print(codificado)

    # decodifico
    bigList2 = []
    mylist2 = []
    i = 0
    for letra in codificado:
        mylist2.append(letra)
        i += 1
        if i == 5:
            bigList2.append(mylist2)
            mylist2 = []
            i = 0
    while i != 0 and i < 5:
        mylist2.append("")
        i += 1
    bigList2.append(mylist2)

    decodificado = ""
    i = 0

    # print("orden2", orden2)
    for lista in bigList2:
        zipped_lists = zip(orden2, lista)
        sorted_zipped_lists = sorted(zipped_lists)
        sorted_list1 = [element for _, element in sorted_zipped_lists]
        # print(sorted_zipped_lists)
        decodificado += "".join(sorted_list1)

    print("\n\n")
    print(decodificado)


if __name__ == "__main__":
    main()
