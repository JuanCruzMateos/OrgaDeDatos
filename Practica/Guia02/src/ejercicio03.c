#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @author Juan Cruz Mateos
 * @matricula 15134
 */

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
void baja(FILE *file, int factura);
void mantenimiento(FILE *file, char *filename);
void modificacion(FILE *file, compra_t buscado, compra_t nuevo);

double promedio_ventas_vendedor(FILE *file, unsigned int leg_vendedor);
double promedio_ventas_fecha(FILE *file, char *fecha);
compra_t mayor_venta_local(FILE *file, unsigned int cod_local);
compra_t mayor_venta_cadena(FILE *file, unsigned int cod_local);
double promedio_ventas_produdcto(FILE *file, unsigned int cod_prod);

int main(int argc, char const *argv[]) {
    char *filename = "./dat/compras.dat";
    FILE *file;

    if (access(filename, F_OK) == 0) {
        file = fopen(filename, "r+b");
    } else {
        file = fopen(filename, "w+b");
    }

    compra_t c1;

    fclose(file);
    return 0;
}

void alta(FILE *file, compra_t compra) {
    // todo
}

void baja(FILE *file, int factura) {
    // todo
}

void mantenimiento(FILE *file, char *filename) {
    // todo
}

void modificacion(FILE *file, compra_t buscado, compra_t nuevo) {
    // todo
}

double promedio_ventas_vendedor(FILE *file, unsigned int leg_vendedor) {
    // todo
    return 0;
}

double promedio_ventas_fecha(FILE *file, char *fecha) {
    // todo
    return 0;
}

compra_t mayor_venta_local(FILE *file, unsigned int cod_local) {
    // todo
}

compra_t mayor_venta_cadena(FILE *file, unsigned int cod_local) {
    // todo
}

double promedio_ventas_produdcto(FILE *file, unsigned int cod_prod) {
    // todo
    return 0;
}
