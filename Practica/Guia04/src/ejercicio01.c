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

#define LEN_NOMBRE 25

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
    char nombre[LEN_NOMBRE];
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
long hash(int dni);

/**
 *  Devuelve la psoicion  del archivo correspondiente al registro cuyo dni
 *  es el indicado o -1 en caso de no existir.
 */
long buscar_posicion(FILE *file, int dni);

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
 *  Devuelve un struct con los campos indicados,.
 */
corredor_t new_corredor(char *nombre, int dni, char sexo, int edad, int categoria, estado_t estado, float tiempo);

int main(int argc, char const *argv[]) {
    char *filename = "./dat/corredores.dat";
    init_file(filename);

    alta(filename, "ultimo", 12006, 'M', 27, 1);
    alta(filename, "ultimo otro", 24013, 'M', 27, 1);
    alta(filename, "primero", 0, 'M', 27, 1);
    alta(filename, "primero otro", 12007, 'M', 27, 1);
    alta(filename, "juan Cruz", 38443617, 'M', 27, 1);
    alta(filename, "juan carlos", 38431610, 'M', 27, 1);
    alta(filename, "cande ", 39251478, 'F', 25, 3);
    alta(filename, "guada mateos", 40251478, 'F', 24, 2);
    alta(filename, "loli ", 41251478, 'F', 22, 5);
    alta(filename, "pepe argento", 14443618, 'M', 41, 7);
    listado_tiempo_general(filename);
    // listado_tiempo_categoria(filename);

    // bajas
    baja(filename, 0);
    listado_tiempo_general(filename);
    baja(filename, 0);
    listado_tiempo_general(filename);
    baja(filename, 2);
    listado_tiempo_general(filename);
    baja(filename, 24013);
    listado_tiempo_general(filename);
    baja(filename, 12006);
    listado_tiempo_general(filename);
    alta(filename, "ultimo act", 12006, 'M', 27, 1);
    alta(filename, "ultimo otro act", 24013, 'M', 27, 1);
    listado_tiempo_general(filename);
    baja(filename, 38443617);
    listado_tiempo_general(filename);

    // cargar tiempo
    cargar_tiempo(filename, 12006, 12.3f);
    cargar_tiempo(filename, 12007, 15.4f);
    cargar_tiempo(filename, 24013, 22.3f);
    cargar_tiempo(filename, 38443617, 369.3f);
    listado_tiempo_general(filename);

    // modificar
    corredor_t edit1 = new_corredor("carolina", 39251478, 'F', 29, 7, OCUPADO, 33.3f);
    corredor_t edit2 = new_corredor("florencia", 12007, 'F', 24, 7, OCUPADO, 25.3f);
    corredor_t edit3 = new_corredor("juan cruz", 39443617, 'M', 27, 7, OCUPADO, 33.3f);
    modificacion(filename, edit1);
    listado_tiempo_general(filename);
    modificacion(filename, edit2);
    listado_tiempo_general(filename);
    modificacion(filename, edit3);
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

long hash(int dni) {
    return (long)sizeof(corredor_t) * (dni % ADDRSPACE_SIZE);
}

/**
 * Devuelve la posicion del registro en el archivo o -1 en caso de no existir.
 */
long buscar_posicion(FILE *file, int dni) {
    long pos_hash, posicion;
    corredor_t c;

    pos_hash = hash(dni);
    fseek(file, pos_hash, SEEK_SET);
    fread(&c, sizeof(corredor_t), 1, file);
    if (c.estado == LIBRE)
        posicion = -1;
    else {
        while (!(c.estado == OCUPADO && c.dni == dni) && c.estado != LIBRE && ftell(file) != pos_hash) {
            fread(&c, sizeof(corredor_t), 1, file);
            if (feof(file))
                fseek(file, 0L, SEEK_SET);
        }
        if (c.estado == OCUPADO && c.dni == dni) {
            posicion = ftell(file) - (long)sizeof(corredor_t);
        } else {
            posicion = -1;
        }
    }
    fseek(file, 0, SEEK_SET);
    return posicion;
}

/**
 * Si la ubucacion esta OCUPADA -> ubicacion + 1 hasta encontrar una posicion LIBRE || BORRADA.
 */
void alta(char *filename, char *nombre, int dni, char sexo, int edad, int categoria) {
    FILE *file;
    long pos;
    corredor_t reg;

    file = fopen(filename, "rb+");
    if (file != NULL) {
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
}

/**
 * Si pos lleva a un registro OCUPADO || BORRADO se procede a buscar secuencialmente hasta encontrar
 * el registro cuyo dni es igual al pasado por parametro o hasta llegar a un registro LIBRE, en cuyo caso
 * no existe ningun registro identificado por el dni.
 */

void baja(char *filename, int dni) {
    FILE *file;
    long pos;
    corredor_t c;

    file = fopen(filename, "rb+");
    if (file != NULL) {
        pos = buscar_posicion(file, dni);
        if (pos != -1) {
            fseek(file, pos, SEEK_SET);
            fread(&c, sizeof(corredor_t), 1, file);
            c.estado = BORRADO;
            fseek(file, pos, SEEK_SET);
            fwrite(&c, sizeof(corredor_t), 1, file);
        }
        fclose(file);
    }
}

void modificacion(char *filename, corredor_t corredor) {
    FILE *file;
    long pos;

    file = fopen(filename, "rb+");
    if (file != NULL) {
        pos = buscar_posicion(file, corredor.dni);
        if (pos != -1) {
            fseek(file, pos, SEEK_SET);
            fwrite(&corredor, sizeof(corredor_t), 1, file);
        }
        fclose(file);
    }
}

void cargar_tiempo(char *filename, int dni, float tiempo) {
    FILE *file;
    long pos;
    corredor_t c;

    file = fopen(filename, "rb+");
    if (file != NULL) {
        pos = buscar_posicion(file, dni);
        if (pos != -1) {
            fseek(file, pos, SEEK_SET);
            fread(&c, sizeof(corredor_t), 1, file);
            c.tiempo = tiempo;
            fseek(file, pos, SEEK_SET);
            fwrite(&c, sizeof(corredor_t), 1, file);
        }
        fclose(file);
    }
}

void listado_tiempo_general(char *filename) {
    corredor_t c;
    FILE *file;
    int i;

    file = fopen(filename, "rb+");
    if (file != NULL) {
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
}

void listado_tiempo_categoria(char *filename) {
    corredor_t c;
    FILE *file;
    int cat_actual, max_categoria = -1;
    int printed = 0;

    file = fopen(filename, "rb");
    if (file != NULL) {
        while (fread(&c, sizeof(corredor_t), 1, file) == 1) {
            if (c.estado == OCUPADO && c.categoria > max_categoria) {
                max_categoria = c.categoria;
            }
        }
        cat_actual = 1;
        printf("Listado por Categoria:\n");
        while (cat_actual <= max_categoria) {
            fseek(file, 0L, SEEK_SET);
            while (fread(&c, sizeof(corredor_t), 1, file) == 1) {
                if (c.estado == OCUPADO && c.categoria == cat_actual) {
                    printf("\t* nombre=%-15s dni=%-10d categoria=%-3d tiempo=%0.2f\n", c.nombre, c.dni, c.categoria, c.tiempo);
                    printed = 1;
                }
            }
            if (printed) printf(("\n"));
            cat_actual += 1;
        }
        printf("\n");
        fclose(file);
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
