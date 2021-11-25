#! /usr/bin/python3

# Se basa en la repeticion de elementos consecutivos
# Si se repiten tres o más elementos consecutivamente, se utiliza el método de compresión RLE.
# De lo contrario, se inserta un carácter de control seguido del número de elementos de la cadena no comprimida.
# Su principal ventaja radica en que RLE se puede usar aun cuando no se pueda analizar el texto o imagen completa a enviar

def main():
    msg = "bAAAAAAAAghhh"

    frec = 1
    for i in range(len(msg) - 1):
        if msg[i] == msg[i+1]:
            frec += 1
        else:
            print(f"{msg[i]}{frec}", end="")
            frec = 1
    print(f"{msg[i+1]}{frec}")


if __name__ == "__main__":
    main()
