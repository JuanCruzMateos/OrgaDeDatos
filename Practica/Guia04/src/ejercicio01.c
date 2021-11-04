#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Compilacion:
 * $ gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ejercicio01 ejercicio01.c
 */

/**
 *  Ejercicio de programacion 1.
 *  nota: todo el codigo esta en un unico archivo a fin reducir el numero de archivos a enviar.
 */

/**
 * Espacio de direcciones.
 * Funcion de hash: metodo de modulo.
 * Ya que se quieren guardar 12000 registros elijo el numero primo mas cercano a ese valor, que es 12007.
 * De esta manera, el archivo quedara 12000/12007 = 99.9% completo
 * 
 * El espacio de direcciones estara luego en el intervalo [0, 12006]
 */
#define ADDRSPACE_SIZE 12007

/**
 * Estados posibles de los registros en el archivo.
 */
typedef enum estado {
    LIBRE,
    OCUPADO,
    BORRADO
} estado_t;

/**
 * Definicion del registro corredor.
 * Incluye campo estado para resolver las coliciones por medio de progressive overflow.
 */
typedef struct corredor {
    int dni;
    char nombre[25];
    char sexo;
    int edad;
    int categoria;
    float tiempo;
    estado_t estado;
} corredor_t;

/**
 * Inicializa el archivo con todos los registros en estado LIBRE.
 */
void init_file(char *filename);

/**
 * Funcion de hash: metodo de modulo.
 */
long int hash(int dni);

/**
 *  Alta de un corredor. tiempo se setea en 0 y estado del registro en el archivo en OCUPADO.
 */
void alta(char *filename, char *nombre, int dni, char sexo, int edad, int categoria);

/**
 *  Baja de un corredor.
 */
void baja(char *filename, int dni);

/**
 *  Modificacion de un corredor.
 *  El parametro corredor empaqueta toda la informacion del corredor actualizada.
 */
void modificacion(char *filename, corredor_t corredor);

/**
 *  Asigna tiempo a un corredor.
 */
void cargar_tiempo(char *filename, int dni, float tiempo);

/**
 *  Listado de tiempo general.
 */
void listado_tiempo_general(char *filename);

/**
 *  Listado de tiempo por categoria.
 */
void listado_tiempo_categoria(char *filename);

/**
 *  Devuelve el contenido del archivo correspondiente al dni del corredor.
 */
long int buscar_posicion(FILE *file, int dni);

/**
 * 
 */
corredor_t new_corredor(char *nombre, int dni, char sexo, int edad, int categoria, estado_t estado, float tiempo);

int main(int argc, char const *argv[]) {
    char *filename = "./dat/corredores.dat";
    init_file(filename);

    alta(filename, "juan Cruz", 38443617, 'M', 27, 1);
    alta(filename, "cande ", 39251478, 'F', 25, 3);
    alta(filename, "guada mateos", 40251478, 'F', 24, 2);
    alta(filename, "loli ", 41251478, 'F', 22, 5);
    alta(filename, "pepe argento", 38443617, 'M', 41, 7);
    listado_tiempo_general(filename);
    listado_tiempo_categoria(filename);
    baja(filename, 38443617);
    listado_tiempo_general(filename);
    baja(filename, 38443617);
    listado_tiempo_general(filename);
    baja(filename, 38443617);
    listado_tiempo_general(filename);
    return 0;
}

void init_file(char *filename) {
    FILE *file = fopen(filename, "wb");
    corredor_t corredor = {.estado = LIBRE};

    for (int i = 0; i < ADDRSPACE_SIZE; i++) {
        fwrite(&corredor, sizeof(corredor_t), 1, file);
    }
    fclose(file);
}

long int hash(int dni) {
    return (long)sizeof(corredor_t) * (dni % ADDRSPACE_SIZE);
}

/**
 * Si la ubucacion esta OCUPADA -> ubicacion + 1 hasta encontrar una posicion LIBRE || BORRADA.
 * Se graba el registro alli.
 */
void alta(char *filename, char *nombre, int dni, char sexo, int edad, int categoria) {
    corredor_t reg;
    long int pos;
    FILE *file;

    file = fopen(filename, "rb+");
    pos = hash(dni);
    fseek(file, pos, SEEK_SET);
    fread(&reg, sizeof(corredor_t), 1, file);
    if (reg.estado != OCUPADO) {
        reg = new_corredor(nombre, dni, sexo, edad, categoria, OCUPADO, 0.0);
        fseek(file, pos, SEEK_SET);
        fwrite(&reg, sizeof(corredor_t), 1, file);
    } else {
        while (reg.estado == OCUPADO && ftell(file) != pos) {
            fread(&reg, sizeof(corredor_t), 1, file);
            if (feof(file)) {
                fseek(file, 0L, SEEK_SET);
            }
        }
        if (reg.estado != OCUPADO) {
            reg = new_corredor(nombre, dni, sexo, edad, categoria, OCUPADO, 0.0);
            pos = ftell(file) - (long)sizeof(corredor_t);
            fseek(file, pos, SEEK_SET);
            fwrite(&reg, sizeof(corredor_t), 1, file);
        }
    }
    fclose(file);
}

/**
 * Si pos lleva a un registro OCUPADO || BORRADO se procede a buscar secuencialmente hasta encontrar
 * el registro cuyo dni es igual al pasado por parametro o hasta llegar a un registro LIBRE, en cuyo caso
 * no existe ningun registro identificado por el dni.
 */
void baja(char *filename, int dni) {
    corredor_t c = {.estado = BORRADO};
    long int pos;
    FILE *file;
    int encontrado = 0;

    file = fopen(filename, "rb+");
    pos = hash(dni);
    fseek(file, pos, SEEK_SET);
    fread(&c, sizeof(corredor_t), 1, file);
    while (!encontrado && c.estado != LIBRE && ftell(file) != pos) {
        if (c.estado == OCUPADO && c.dni == dni) {
            encontrado = 1;
            c.estado = BORRADO;
            fseek(file, ftell(file) - (long)sizeof(corredor_t), SEEK_SET);
            fwrite(&c, sizeof(corredor_t), 1, file);
        } else {
            if (feof(file))
                fseek(file, 0L, SEEK_SET);
            fread(&c, sizeof(corredor_t), 1, file);
        }
    }
    fclose(file);
}

void modificacion(char *filename, corredor_t corredor) {
    long int pos;
    FILE *file;

    file = fopen(filename, "rb+");
    pos = hash(corredor.dni);

    fseek(file, pos, SEEK_SET);
    fwrite(&corredor, sizeof(corredor_t), 1, file);
    fclose(file);
}

void cargar_tiempo(char *filename, int dni, float tiempo) {
    corredor_t c;
    long int pos;
    FILE *file;
    int encontrado = 0;

    file = fopen(filename, "rb+");
    pos = hash(dni);
    fseek(file, pos, SEEK_SET);
    fread(&c, sizeof(corredor_t), 1, file);
    while (!encontrado && ftell(file) != pos && c.estado != LIBRE) {
        if (c.estado == OCUPADO && c.dni == dni) {
            c.tiempo = tiempo;
            encontrado = 1;
        }
        if (feof(file))
            fseek(file, 0L, SEEK_SET);
        fread(&c, sizeof(corredor_t), 1, file);
        if (c.estado == OCUPADO && c.dni == dni) {
            encontrado = 1;
        }
    }
    fseek(file, pos, SEEK_SET);
    fwrite(&c, sizeof(corredor_t), 1, file);
    fclose(file);
}

void listado_tiempo_general(char *filename) {
    corredor_t c;
    FILE *file;
    int i;

    file = fopen(filename, "rb+");
    i = 0;
    while (fread(&c, sizeof(corredor_t), 1, file) == 1) {
        if (c.estado == OCUPADO) {
            printf("%8d. nombre=%-15s dni=%-10d categoria=%-3d tiempo=%0.2f\n", i, c.nombre, c.dni, c.categoria, c.tiempo);
        }
        i += 1;
    }
    fclose(file);
    printf("\n");
}

void listado_tiempo_categoria(char *filename) {
    corredor_t c;
    FILE *file;
    int cat_actual, max_categoria = -1;

    file = fopen(filename, "rb");
    while (fread(&c, sizeof(corredor_t), 1, file) == 1) {
        if (c.categoria > max_categoria) {
            max_categoria = c.categoria;
        }
    }
    cat_actual = 1;
    while (cat_actual <= max_categoria) {
        fseek(file, 0L, SEEK_SET);
        while (fread(&c, sizeof(corredor_t), 1, file) == 1) {
            if (c.categoria == cat_actual) {
                printf("nombre=%-15s dni=%-10d categoria=%-3d tiempo=%0.2f\n", c.nombre, c.dni, c.categoria, c.tiempo);
            }
        }
        cat_actual += 1;
    }
    printf("\n");
    fclose(file);
}

long int buscar_posicion(FILE *file, int dni) {
    corredor_t c;
    long int pos;

    pos = hash(dni);
    fseek(file, pos, SEEK_SET);
    fread(&c, sizeof(corredor_t), 1, file);
    if (c.estado == LIBRE)
        return -1;
    else {
        while (!(c.estado == OCUPADO && c.dni == dni) && c.estado != LIBRE && ftell(file) != pos) {
            if (feof(file))
                fseek(file, 0L, SEEK_SET);
            fread(&c, sizeof(corredor_t), 1, file);
        }
        if (c.estado == OCUPADO && c.dni == dni) {
            return ftell(file) - (long)sizeof(corredor_t);
        } else {
            return -1;
        }
    }
}

corredor_t new_corredor(char *nombre, int dni, char sexo, int edad, int categoria, estado_t estado, float tiempo) {
    corredor_t c;

    strcpy(c.nombre, nombre);
    c.dni = dni;
    c.sexo = sexo;
    c.edad = edad;
    c.categoria = categoria;
    c.estado = estado;
    c.tiempo = tiempo;
    return c;
}
