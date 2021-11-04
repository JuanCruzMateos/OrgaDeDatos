import random
from time import time


def merge(arr, l, m, r):
    n1 = m - l + 1
    n2 = r - m

    # create temp arrays
    L = [0] * (n1)
    R = [0] * (n2)

    # Copy data to temp arrays L[] and R[]
    for i in range(0, n1):
        L[i] = arr[l + i]

    for j in range(0, n2):
        R[j] = arr[m + 1 + j]

    # Merge the temp arrays back into arr[l..r]
    i = 0     # Initial index of first subarray
    j = 0     # Initial index of second subarray
    k = l     # Initial index of merged subarray

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    # Copy the remaining elements of L[], if there
    # are any
    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    # Copy the remaining elements of R[], if there
    # are any
    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1

# l is for left index and r is right index of the
# sub-array of arr to be sorted


def mergeSort(arr, l, r):
    if l < r:

        # Same as (l+r)//2, but avoids overflow for
        # large l and h
        m = (l+(r-1))//2

        # Sort first and second halves
        mergeSort(arr, l, m)
        mergeSort(arr, m+1, r)
        merge(arr, l, m, r)


def inicializarArray(arr):
    for _ in range(150000):
        arr.append([0, "Producto", "Descripcion"])


def crearArray(arr):
    for i in range(150000):
        arr[i] = ([random.randint(0, 150000), "Producto", "Descripcion"])


def main():
    archivo = open("datos1.bin", "wb")
    # SE CREA ARCHIVO
    for i in range(150000):
        archivo.write([random.randint(0, 150000), "Producto", "Descripcion"])
    archivo.close()
    # ARCHIVO CREADO, AHORA SE LEE DE ARCHIVO PARA PONER EN EL ARREGLO
    archivo = open("datos1.bin", "rb")
    arr = []
    inicializarArray(arr)
    tiempo_inicio = time()
    for i in range(150000):
        arr[i] = archivo.read()
    tiempo_final = time()
    archivo.close()
    # ARREGLO CREADO, AHORA SE ORDENA EL MISMO
    print("Tiempo de creacion del arreglo: ", tiempo_final-tiempo_inicio)
    n = len(arr)
    tiempo_inicio = time()
    mergeSort(arr, 0, n-1)
    tiempo_final = time()
    print("Tiempo de ordenado: ", tiempo_final-tiempo_inicio)
    # ARREGLO ORDENADO, AHORA SE CREA NUEVO ARCHIVO Y SE GUARDAN LOS REGISTROS
    archivo = open("datos_nuevo.bin", "w")
    tiempo_inicio = time()
    for i in range(150000):
        archivo.write(arr[i])
    tiempo_final = time()
    print("Tiempo de guardado en archivo: ", tiempo_final-tiempo_inicio)
    archivo.close()


if __name__ == "__main__":
    main()
