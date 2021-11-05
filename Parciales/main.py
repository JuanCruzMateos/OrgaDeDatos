#! /usr/bin/python3

l = ["cuchara",  "tenedor", "cuchillo", "plato"]

index = ord('a')
for palabra in l:
    res = ord(palabra[0])
    for letra in palabra[1:]:
        res = res ^ ord(letra)
    print(f"{chr(index)}. {palabra} -> h({palabra}) = {res % 127}")
    index += 1
