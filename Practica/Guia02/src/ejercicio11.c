#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @author Juan Cruz Mateos
 * @matricula 15134
 *
 * Compilacion:
 * $ gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ejercicio11 ejercicio11.c
 */

#define FMT_PROD 16
#define FMT_DESC 51
#define CANT_REG 100000

typedef struct producto {
    int id;
    char producto[FMT_PROD];
    char desc[FMT_DESC];
} producto_t;

void generar_archivo(char *filename);
void print_file(FILE *file);
void merge_sort(FILE *file);
void shell(producto_t vec[], int n);

int main(int argc, char const *argv[]) {
    char *filename = "./dat/bigfile.dat";

    generar_archivo(filename);

    FILE *file = fopen(filename, "r+b");
    if (file == NULL)
        return -1;
    // print_file(file);
    merge_sort(file);
    // print_file(file);
    fclose(file);
    return 0;
}

void merge_sort(FILE *file) {
    int tope = CANT_REG / 100;
    producto_t arr[CANT_REG / 100];
    clock_t time;
    long fileptr_ini;

    time = clock();

    while (!feof(file)) {
        fileptr_ini = ftell(file);
        for (int i = 0; i < tope; i++) {
            fread(&arr[i], sizeof(producto_t), 1, file);
        }
        shell(arr, tope);
        fseek(file, fileptr_ini, SEEK_SET);
        for (int i = 0; i < tope; i++) {
            fwrite(&arr[i], sizeof(producto_t), 1, file);
        }
    }
    time = clock() - time;
    double duration = (double)time / CLOCKS_PER_SEC;
    printf("time = %f\n", duration);
}

void shell(producto_t vec[], int n) {
    int cambio, aux, i, paso;

    paso = n / 2;
    do {
        do {
            cambio = 0;
            for (i = 0; i < n - paso; i++) {
                if (vec[i].id > vec[i + paso].id) {
                    aux = vec[i].id;
                    vec[i].id = vec[i + paso].id;
                    vec[i + paso].id = aux;
                    cambio = 1;
                }
            }
        } while (cambio);
        paso = paso / 2;
        printf("Cambio de paso a %d\n", paso);
    } while (paso != 0);
}

void generar_archivo(char *filename) {
    FILE *file = fopen(filename, "wb");
    producto_t producto;
    int id;
    char p[FMT_PROD];
    char d[FMT_DESC];

    for (int i = 0; i < CANT_REG; i++) {
        id = rand() % 150000;
        producto.id = id;
        sprintf(p, "prod %d", id);
        sprintf(d, "desc %d", id);
        strcpy(producto.producto, p);
        strcpy(producto.desc, d);
        fwrite(&producto, sizeof(producto_t), 1, file);
    }
    fclose(file);
}

void print_file(FILE *file) {
    producto_t producto;

    fseek(file, 0, SEEK_SET);
    while (fread(&producto, sizeof(producto_t), 1, file) == 1) {
        printf("id=%-8d %-s %-20s\n", producto.id, producto.producto, producto.desc);
    }
}
