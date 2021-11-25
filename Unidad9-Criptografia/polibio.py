def encode(dic: dict, msg: str) -> str:
    encodemsg = ""
    for char in msg:
        encodemsg += dic[char]
    return encodemsg


def decode(dic: dict, msg: str) -> str:
    original = ""
    splittedmdg = [msg[i:i+2] for i in range(0, len(msg), 2)]
    for i in splittedmdg:
        original += dic[i]
    return original


def main():
    i = 10
    codedict = {}
    decodedict = {}
    for c in range(ord('a'), ord('z') + 1):
        letra = chr(c)
        if letra != 'j':
            i += 1
            codedict[letra] = str(i)
            decodedict[str(i)] = letra
            if i % 10 == 5:
                i += 5

    msg = input("msg = ")
    encodedmsg = encode(codedict, msg)
    print(encodedmsg)
    originalmsg = decode(decodedict, encodedmsg)
    print(originalmsg)


if __name__ == "__main__":
    main()
