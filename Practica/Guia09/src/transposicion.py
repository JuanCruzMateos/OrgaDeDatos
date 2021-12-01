#! /usr/bin/python3


def encode(msg: str, transposicion: list) -> str:
    # armo tabla
    i = 0
    row = []
    table = []
    for letra in msg:
        i += 1
        row.append(letra)
        if i == len(transposicion):
            table.append(row)
            row = []
            i = 0
    while i != 0 and i < len(transposicion):
        row.append("")
        i += 1
    table.append(row)

    # corrijo indices con -1
    orden = [item-1 for item in transposicion]

    codificado = ""
    for lista in table:
        for i in range(len(transposicion)):
            codificado += lista[orden[i]]
    return codificado


def decode(msg: str, transposicion: list) -> str:
    i = 0
    row = []
    table = []
    for letra in msg:
        i += 1
        row.append(letra)
        if i == len(transposicion):
            table.append(row)
            row = []
            i = 0
    while i != 0 and i < len(transposicion):
        row.append("")
        i += 1
    table.append(row)

    orden = [item-1 for item in transposicion]

    decodificado = ""
    for lista in table:
        zipped_list = list(zip(orden, lista))
        sorted_zipped_list = sorted(zipped_list, key=lambda item: item[0])
        sorted_list1 = [element for _, element in sorted_zipped_list]
        decodificado += "".join(sorted_list1)
    return decodificado


def main():
    msg = "El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."
    transposicion = [5, 2, 1, 3, 4]

    codificado = encode(msg, transposicion)
    print(codificado)

    decodificado = decode(codificado, transposicion)
    print(decodificado)

    print(f"msg == decodificado = {msg == decodificado}")


if __name__ == "__main__":
    main()
