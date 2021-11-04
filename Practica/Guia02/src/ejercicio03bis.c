#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FMT_OBS 100
#define FMT_FECHA 11
#define FMT_HORA 9

typedef struct compra {
    char fecha[FMT_FECHA];    // C10    'YYYY-MM-DD'
    char hora[FMT_HORA];      // C5     'HH:MM:SS'
    unsigned int cod_prob;    // E4
    unsigned int cod_ciu;     // E4
    unsigned int cod_local;   // E4
    unsigned int leg_ved;     // E4
    int factura;              // E4
    unsigned int cod_prod;    // E4
    unsigned short int cant;  // E2
    double valor_un;          // F8
    double total_rg;          // F8
    char obs[FMT_OBS];        // C100
} compra_t;

/**
 * 
 *  Identificadores:
 *      - factura
 * 
 *  Registros desordenados:
 *   > altas: append
 *   > bajas: marcado -> cambio signo del identificador (factura)
 *   > modificaciones
 *   > consultas - promedio de ventas vendedor
 *               - promedio de ventas para fecha
 *               - mayor venta de un local
 *               - mayor venta de una cadena
 *               - promedio de ventas de un producto
 * 
 */

void alta(FILE *file, compra_t compra);
void print_file(FILE *file);
void natural_merge_sort(FILE **file);

int main(int argc, char const *argv[]) {
    char *filename = "./dat/compras.dat";
    FILE *file;
    compra_t c1, c2, c3;

    c1.factura = 1345;
    c2.factura = 7852;
    c3.factura = 4256;

    if (access(filename, F_OK) == 0) {
        file = fopen(filename, "r+b");
    } else {
        file = fopen(filename, "w+b");
        alta(file, c1);
        alta(file, c2);
        alta(file, c3);
    }

    print_file(file);
    // natural_merge_sort(&file);
    fclose(file);
    return 0;
}

void natural_merge_sort(FILE **file) {
    FILE *aux1, *aux2, *temp;
    char *fname1 = "./dat/aux1.dat";
    char *fname2 = "./dat/aux2.dat";
    char *fname3 = "./dat/aux2.dat";
    int ordenado = 0;
    compra_t ant, act;

    ant.factura = -1;
    while (!ordenado) {
        aux1 = fopen(fname1, "w+b");
        aux2 = fopen(fname2, "w+b");
        temp = fopen(fname3, "w+b");

        while (fread(&act, sizeof(compra_t), 1, *file) == 1) {
        }

        fclose(aux1);
        fclose(aux2);
        fclose(temp);
    }

    remove(fname1);
    remove(fname2);
}

void print_file(FILE *file) {
    size_t count = 0;
    compra_t c;

    // posicionamiento al comienzo del archivo
    fseek(file, 0, SEEK_SET);
    while (fread(&c, sizeof(compra_t), 1, file) == 1) {
        printf("#%ld\n", ++count);
        printf("factura = %d\n", c.factura);
    }
}

void alta(FILE *file, compra_t compra) {
    fseek(file, 0, SEEK_END);
    fwrite(&compra, sizeof(compra_t), 1, file);
}