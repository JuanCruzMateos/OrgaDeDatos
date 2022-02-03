#! /usr/bin/python3
# @author Juan Cruz Mateos
from string import ascii_lowercase
from string import ascii_uppercase
from string import digits


def encode(dic: dict, msg: str) -> str:
    encodemsg = ""
    for char in msg:
        encodemsg += dic[char] if char != " " else " "
    return encodemsg


# def decode(dic: dict, msg: str) -> str:
#     original = ""
#     nospaces = msg.split(" ")
#     splittedmdg = [msg[i:i+2]
#                    for msg in nospaces for i in range(0, len(msg), 2)]
#     for i in splittedmdg:
#         original += dic[i]
#     return original

def decode(dic: dict, msg: str) -> str:
    i = 0
    original = ""
    while i < len(msg):
        if msg[i] == " ":
            original += " "
            i += 1
        else:
            original += dic[msg[i:i+2]]
            i += 2
    return original


def main():
    # original
    # i = 10
    # codedict = {}
    # decodedict = {}
    # for c in range(ord('a'), ord('z') + 1):
    #     letra = chr(c)
    #     if letra != 'j':
    #         i += 1
    #         codedict[letra] = str(i)
    #         decodedict[str(i)] = letra
    #         if i % 10 == 5:
    #             i += 5

    # TP
    codedict = {}
    decodedict = {}
    # lower = [char for char in ascii_lowercase]
    # lower.insert(14, "ñ")
    upper = [char for char in ascii_uppercase]
    # beta.insert(14, "Ñ")
    numbers = [nro for nro in digits]
    complete = upper + numbers
    # complete += list("áéíóú,;._-")

    # print(upper[19:])
    # print(upper[:19])
    complete = upper[19:] + numbers + upper[:19]
    i = 10
    for c in complete:
        letra = c
        i += 1
        codedict[letra] = str(i)
        decodedict[str(i)] = letra
        if i % 10 == 6:
            i += 4

    # msg = "todos usamos linux"
    # encodedmsg = encode(codedict, msg)
    # print(encodedmsg)

    # msg = "El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."
    msg = "LA CALCULADORA NO TE VA A DAR 1 PALABRA"
    # enc_msg = "4824 13191633111428 467834113384 1534 362611 1415 241134 3578132619131134 257734 3419252924153485 1328263419343515 1526 33151525292411431133 13111411 2415353311 292833 28353311 323615 3415 152613361526353311 3626 268325153328 16192228 1415 29283419131928261534 257734 111415241126351586"

    # enc_mio = encode(codedict, msg)
    # originalmsg = decode(decodedict, enc_msg)
    print(msg)
    enc = encode(codedict, msg)
    print(enc)
    # print(enc_msg == enc_mio)


if __name__ == "__main__":
    main()
