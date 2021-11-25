#! /usr/bin/python3
# from pprint import pprint

def encriptar(msg: str, salto: int, palabra_clave: str, enie: bool = False) -> str:
    a = ord("a")
    strip_keyword = ''.join(
        sorted(set(palabra_clave), key=palabra_clave.index))
    inicio = a + salto

    i = 0
    dic = {}
    for c in strip_keyword:
        dic[chr(inicio+i)] = c
        i += 1

    init = inicio + i
    for c in range(ord("a"), ord("z") + 1):
        if chr(c) not in strip_keyword:
            if init > ord("z"):
                init = ord("a")
            dic[chr(init)] = chr(c)
            init += 1

    encriptado = ""
    for c in msg:
        encriptado += " " if c == " " else dic[c]
    return encriptado


def main():
    palabra_clave = input("palabra clave: ")
    salto = int(input("salto: "))

    a = ord("a")
    p_clave_sin_dup = ''.join(
        sorted(set(palabra_clave), key=palabra_clave.index))
    inicio = a + salto

    print(p_clave_sin_dup)

    dic = {}

    i = 0
    for c in p_clave_sin_dup:
        dic[chr(inicio+i)] = c
        i += 1

    init = inicio+i
    for c in range(ord("a"), ord("z") + 1):
        if chr(c) not in p_clave_sin_dup:
            if init > ord("z"):
                init = ord("a")
            dic[chr(init)] = chr(c)
            init += 1

    # pprint(dic)

    msg = input("msg = ")
    for c in msg:
        print(dic[c], end="")
    print()


if __name__ == "__main__":
    main()
