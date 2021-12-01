#! /usr/bin/python3
# @author Juan Cruz Mateos
from string import ascii_lowercase
from string import ascii_uppercase


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
    i = 10
    codedict = {}
    decodedict = {}
    alpha = [char for char in ascii_lowercase]
    beta = [char for char in ascii_uppercase]
    alpha.insert(14, "ñ")
    beta.insert(14, "Ñ")
    alpha = alpha + beta + list("áéíóú,;._-")

    for c in alpha:
        letra = c
        i += 1
        codedict[letra] = str(i)
        decodedict[str(i)] = letra
        if i % 10 == 9:
            i += 2

    # msg = "todos usamos linux"
    # encodedmsg = encode(codedict, msg)
    # print(encodedmsg)

    msg = "El cifrado César, es una de las técnicas más simples; consiste en reemplazar cada letra por otra que se encuentra un número fijo de posiciones más adelante."
    enc_msg = "4824 13191633111428 467834113384 1534 362611 1415 241134 3578132619131134 257734 3419252924153485 1328263419343515 1526 33151525292411431133 13111411 2415353311 292833 28353311 323615 3415 152613361526353311 3626 268325153328 16192228 1415 29283419131928261534 257734 111415241126351586"

    enc_mio = encode(codedict, msg)
    originalmsg = decode(decodedict, enc_msg)
    print(originalmsg)
    print(msg == originalmsg)
    print(enc_msg == enc_mio)


if __name__ == "__main__":
    main()
