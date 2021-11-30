#! /usr/bin/python3
# @author Juan Cruz Mateos

# Se basa en la repeticion de elementos consecutivos
# Si se repiten tres o más elementos consecutivamente, se utiliza el método de compresión RLE.
# De lo contrario, se inserta un carácter de control seguido del número de elementos de la cadena no comprimida.
# Su principal ventaja radica en que RLE se puede usar aun cuando no se pueda analizar el texto o imagen completa a enviar

def main():
    msg = "PPOPTTTKKKKLLLLLVVVVV"

    frec = 1
    for i in range(len(msg) - 1):
        if msg[i] == msg[i+1]:
            frec += 1
        else:
            # print(f"{msg[i]}{frec}", end="")
            print(f"{frec}{msg[i]}", end="")
            frec = 1
    # print(f"{msg[i+1]}{frec}")
    print(f"{frec}{msg[i+1]}")


if __name__ == "__main__":
    main()
