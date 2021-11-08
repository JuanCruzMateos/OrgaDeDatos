#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Compilacion:
 * $ gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ejercicio02 ejercicio02.c
 */

/**
 *  Ejercicio de programacion 2:
 *  Suponga un sistema para el manejo de personal de una empresa. 
 *  Los datos a almacenar son 
 *      - apellido y nombre, 
 *      - dirección, 
 *      - teléfono, y 
 *      - fecha de ingreso.
 *  Para la solución se plantea un archivo directo donde el apellido y nombre es la clave de acceso.
 *  
 * Implemente una función hash, creación de archivo principal, alta, modificaciones, bajas. 
 * El manejo de colisiones se debe resolver por área separada de overflow.
 * 
 * Resolucion:
 *  - Como no se indica el tamaño del archivo, y al ser para manerar el personal de una empresa, supongo que
 *    se trata de una empresa grande que dispone de una gran cantidad de empleados, por lo que el archivo debera
 *    manejar una gran cantidad de registros. Por lo tanto, elijo un tamaño de archivo y un espacio de direcciones
 *    de 12007 posiciones, tanto para el archivo principal como para el area separada de overflow.
 * 
 * - Dada la libertad del enuncido, hago coincidir el tamaño del archivo con el espacio de direcciones, fijandolo
 *   en el numero primo 12007 a fin de asegurar un tamaño lo suficientemente grande para el archivo al igual que un
 *   numero primo capaz de asegurar una mejor distribucion de las claves.
 *   De esta manera el archivo constara de 12007 registros estando el espacio de direcciones en el intervalo [0, 12006]
 */

#define LEN 25
#define ADDRSPACE_SIZE 12007

typedef enum estado {
    LIBRE,
    OCUPADO,
} estado_t;

typedef struct personal {
    char nombre[LEN];
    char apellido[LEN];
    char direccion[LEN];
    int telefono;
    char fechaingreso[11];  // YYYY-MM-DD
    estado_t estado;
    long sig;
} personal_t;

/**
 * Inicializa el archivo con todos los registros del archivo ppal y overflow en estado LIBRE.
 */

void init_file(char *mainfilename, char *overflowname);

/**
 * Funcion de hash: metodo de compresion utilizando el nombre y el apellido.
 */
long hash(char *nombre, char *apellido);

/**
 *  Alta de personal.
 */
void alta(char *mainfilename, char *overflowname, char *nombre, char *apellido, char *direccion, int telefono, char *fechaingreso);

/**
 *  Baja de personal.
 */
void baja(char *mainfilename, char *overflowname, char *nombre, char *apellido, char *direccion, int telefono, char *fechaingreso);

/**
 *  Modificacion de personal.
 *  El parametro personal empaqueta toda la informacion del corredor actualizada.
 */
void modificar(char *mainfilename, char *overflowname, personal_t anterior, personal_t nuevo);

/**
 * Devuelve un nuevo registro con los datos pasados por parametro
 */
personal_t new_personal(char *nombre, char *apellido, char *direccion, int telefono, char *fechaingreso, estado_t estado, long sig);

/**
 * Obtener una posicion libre en el archivo overflow
 */
long buscar_posicion_libre(FILE *overflowfile);

/**
 * Compara dos registros a fin de evaluar si todos sus campos son iguales.
 */
int equals(personal_t this, personal_t that);

/**
 * Lista ambos archivos
 */
void listar(char *mainfilename, char *overflowname);

int main(int argc, char const *argv[]) {
    char *mainfile = "./dat/personal.dat";
    char *overflowfile = "./dat/personaloverflow.dat";

    init_file(mainfile, overflowfile);

    alta(mainfile, overflowfile, "juan cruz", "mateos", "almafuerte 1234", 4512154, "2021-08-15");
    alta(mainfile, overflowfile, "maria", "lopez", "mitre 1234", 155258963, "2020-10-15");
    alta(mainfile, overflowfile, "lucia", "perez", "paso 1234", 154258963, "2021-03-20");
    alta(mainfile, overflowfile, "pedro", "gonzales", "falucho 1234", 154123456, "2021-11-13");
    alta(mainfile, overflowfile, "pablo", "rodriguez", "matheu 1234", 1524793254, "2019-12-17");
    alta(mainfile, overflowfile, "sofia", "rojas", "san luis 1234", 156362514, "2021-01-02");

    alta(mainfile, overflowfile, "juan cruz", "mateos", "otro1", 4512154, "2021-08-15");
    alta(mainfile, overflowfile, "pedro", "gonzales", "otro1", 154123456, "2021-11-13");
    alta(mainfile, overflowfile, "juan cruz", "mateos", "otro2", 4512154, "2021-08-15");
    alta(mainfile, overflowfile, "pablo", "rodriguez", "otro1", 1524793254, "2019-12-17");
    alta(mainfile, overflowfile, "cande", "mateos", "almafuerte 1234", 15245635, "2022-08-15");
    alta(mainfile, overflowfile, "pedro", "gonzales", "otro2", 154123456, "2021-11-13");
    alta(mainfile, overflowfile, "pedro", "gonzales", "otro3", 154123456, "2021-11-13");

    listar(mainfile, overflowfile);

    baja(mainfile, overflowfile, "lucia", "perez", "paso 1234", 154258963, "2021-03-20");
    printf("baja = lucia perez \n");
    listar(mainfile, overflowfile);
    baja(mainfile, overflowfile, "pedro", "gonzales", "otro3", 154123456, "2021-11-13");
    printf("baja = pedro gonzales otro3\n");
    listar(mainfile, overflowfile);
    baja(mainfile, overflowfile, "pedro", "gonzales", "falucho 1234", 154123456, "2021-11-13");
    printf("baja = pedro gonzales falusho 1234\n");
    listar(mainfile, overflowfile);

    personal_t p1ant = new_personal("juan cruz", "mateos", "otro2", 4512154, "2021-08-15", OCUPADO, -1);
    personal_t p1nuevo = new_personal("juan cruz", "mateos", "actualizo", 155937802, "2021-08-15", OCUPADO, -1);
    // personal_t p2 = new_personal("maria", "lopez", "mitre 1234", 155258963, "2020-10-15", OCUPADO, -1);
    // personal_t p5 = new_personal("pablo", "rodriguez", "matheu 1234", 1524793254, "2019-12-17", OCUPADO, -1);
    // personal_t p6 = new_personal("sofia", "rojas", "san luis 1234", 156362514, "2021-01-02", OCUPADO, -1);
    // personal_t p7 = new_personal("juan cruz", "mateos", "otro1", 4512154, "2021-08-15", OCUPADO, -1);
    // personal_t p8 = new_personal("pedro", "gonzales", "otro1", 154123456, "2021-11-13", OCUPADO, -1);
    // personal_t p9 = new_personal("juan cruz", "mateos", "otro2", 4512154, "2021-08-15", OCUPADO, -1);
    // personal_t p10 = new_personal("pablo", "rodriguez", "otro1", 1524793254, "2019-12-17", OCUPADO, -1);
    // personal_t p11 = new_personal("cande", "mateos", "almafuerte 1234", 15245635, "2022-08-15", OCUPADO, -1);
    // personal_t p12 = new_personal("pedro", "gonzales", "otro2", 154123456, "2021-11-13", OCUPADO, -1);

    modificar(mainfile, overflowfile, p1ant, p1nuevo);
    listar(mainfile, overflowfile);
    return 0;
}

void init_file(char *mainfilename, char *overflowname) {
    FILE *stream_file, *stream_over;
    personal_t p = {.estado = LIBRE};

    stream_file = fopen(mainfilename, "wb");
    stream_over = fopen(overflowname, "wb");
    for (int i = 0; i < ADDRSPACE_SIZE; i++) {
        fwrite(&p, sizeof(personal_t), 1, stream_file);
        fwrite(&p, sizeof(personal_t), 1, stream_over);
    }
    fclose(stream_file);
    fclose(stream_over);
}

long hash(char *nombre, char *apellido) {
    long pos;
    int i;

    pos = nombre[0];
    for (i = 1; i < strlen(nombre); i++) {
        pos ^= nombre[i];
    }
    for (i = 0; i < strlen(apellido); i++) {
        pos ^= apellido[i];
    }
    return (pos % ADDRSPACE_SIZE) * (long)sizeof(personal_t);
}

long buscar_posicion_libre(FILE *overflowfile) {
    personal_t p;
    long pos;

    fseek(overflowfile, 0L, SEEK_SET);
    do {
        fread(&p, sizeof(personal_t), 1, overflowfile);
    } while (p.estado == OCUPADO);
    pos = ftell(overflowfile) - (long)sizeof(personal_t);
    fseek(overflowfile, 0L, SEEK_SET);
    return pos;
}

/**
 *  Alta de personal.
 */
void alta(char *mainfilename, char *overflowname, char *nombre, char *apellido, char *direccion, int telefono, char *fechaingreso) {
    FILE *mainfile, *overflowfile;
    long pos_main, pos_act, pos_ant, pos_overflow_nuevo;
    personal_t personal, nuevo, personal_over;

    mainfile = fopen(mainfilename, "rb+");
    if (mainfile != NULL) {
        nuevo = new_personal(nombre, apellido, direccion, telefono, fechaingreso, OCUPADO, -1);

        pos_main = hash(nombre, apellido);
        fseek(mainfile, pos_main, SEEK_SET);
        fread(&personal, sizeof(personal_t), 1, mainfile);
        fseek(mainfile, pos_main, SEEK_SET);

        if (personal.estado == LIBRE) {  // grabo el registro en ese lugar
            fwrite(&nuevo, sizeof(personal_t), 1, mainfile);
        } else {
            overflowfile = fopen(overflowname, "rb+");
            if (overflowfile != NULL) {
                pos_overflow_nuevo = buscar_posicion_libre(overflowfile);
                fseek(overflowfile, pos_overflow_nuevo, SEEK_SET);
                fwrite(&nuevo, sizeof(personal_t), 1, overflowfile);
                if (personal.sig == -1) {
                    // actualizo el registro en el main
                    personal = new_personal(personal.nombre, personal.apellido, personal.direccion, personal.telefono, personal.fechaingreso, OCUPADO, pos_overflow_nuevo);
                    fwrite(&personal, sizeof(personal_t), 1, mainfile);
                } else {  // tengo que recorrer la lista en el otro archivo
                    pos_act = personal.sig;
                    do {
                        pos_ant = pos_act;
                        fseek(overflowfile, pos_act, SEEK_SET);
                        fread(&personal_over, sizeof(personal_t), 1, overflowfile);
                        pos_act = personal_over.sig;
                    } while (personal_over.sig != -1);
                    personal_over = new_personal(personal_over.nombre, personal_over.apellido, personal_over.direccion, personal_over.telefono, personal_over.fechaingreso, personal_over.estado, pos_overflow_nuevo);
                    fseek(overflowfile, pos_ant, SEEK_SET);
                    fwrite(&personal_over, sizeof(personal_t), 1, overflowfile);
                }
            }
            fclose(overflowfile);
        }
        fclose(mainfile);
    }
}

/**
 *  Baja de personal.
 */
void baja(char *mainfilename, char *overflowname, char *nombre, char *apellido, char *direccion, int telefono, char *fechaingreso) {
    personal_t elim = new_personal(nombre, apellido, direccion, telefono, fechaingreso, OCUPADO, -1);
    FILE *mainfile, *overflowfile;
    personal_t persona, persona_overflow, ant_over;
    long pos_main, pos_ant, pos_act;

    mainfile = fopen(mainfilename, "rb+");
    if (mainfile != NULL) {
        pos_main = hash(nombre, apellido);
        fseek(mainfile, pos_main, SEEK_SET);
        fread(&persona, sizeof(personal_t), 1, mainfile);
        if (persona.estado != LIBRE) {
            if (equals(persona, elim)) {  // si es el primero
                if (persona.sig == -1) {  // si es el unico
                    persona.estado = LIBRE;
                    fseek(mainfile, pos_main, SEEK_SET);
                    fwrite(&persona, sizeof(personal_t), 1, mainfile);
                } else {  // si hay mas elementos en la lista
                    pos_ant = -1;
                    pos_act = persona.sig;
                    overflowfile = fopen(overflowname, "rb+");
                    if (overflowfile != NULL) {
                        fseek(overflowfile, pos_act, SEEK_SET);
                        fread(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                        while (persona_overflow.sig != -1) {
                            pos_ant = pos_act;
                            pos_act = persona_overflow.sig;
                            fseek(overflowfile, pos_act, SEEK_SET);
                            fread(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                        }
                        persona_overflow.sig = persona.sig;  // ultimo -> primro
                        fseek(mainfile, pos_main, SEEK_SET);
                        fwrite(&persona_overflow, sizeof(personal_t), 1, mainfile);  // escribo el ultimo en primero
                        persona_overflow.estado = LIBRE;                             // marco ultimo como libre
                        fseek(overflowfile, pos_act, SEEK_SET);
                        fwrite(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                        if (pos_ant != -1) {
                            fseek(overflowfile, pos_ant, SEEK_SET);
                            fread(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                            persona_overflow.sig = -1;
                            fseek(overflowfile, pos_ant, SEEK_SET);
                            fwrite(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                        }
                        fclose(overflowfile);
                    }
                }
            } else {  // si no es el primer elemento
                overflowfile = fopen(overflowname, "rb+");
                if (overflowname != NULL) {
                    pos_ant = -1;
                    pos_act = persona.sig;
                    fseek(overflowfile, pos_act, SEEK_SET);
                    fread(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                    while (!equals(persona_overflow, elim) && persona_overflow.sig != -1) {
                        pos_ant = pos_act;
                        pos_act = persona_overflow.sig;
                        fseek(overflowfile, pos_act, SEEK_SET);
                        fread(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                    }
                    if (equals(persona_overflow, elim)) {
                        if (pos_ant == -1) {
                            persona_overflow.estado = LIBRE;
                            fseek(overflowfile, pos_act, SEEK_SET);
                            fwrite(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                            persona.sig = -1;
                            fseek(overflowfile, pos_main, SEEK_SET);
                            fwrite(&persona, sizeof(personal_t), 1, overflowfile);
                        } else {
                            fseek(overflowfile, pos_ant, SEEK_SET);
                            fread(&ant_over, sizeof(personal_t), 1, overflowfile);
                            ant_over.sig = persona_overflow.sig;
                            fseek(overflowfile, pos_ant, SEEK_SET);
                            fwrite(&ant_over, sizeof(personal_t), 1, overflowfile);
                            persona_overflow.estado = LIBRE;
                            fseek(overflowfile, pos_act, SEEK_SET);
                            fwrite(&persona_overflow, sizeof(personal_t), 1, overflowfile);
                        }
                    }
                    fclose(overflowfile);
                }
            }
        }
        fclose(mainfile);
    }
}

/**
 *  Modificacion de personal.
 */
void modificar(char *mainfilename, char *overflowname, personal_t anterior, personal_t nuevo) {
    FILE *mainfile, *overflowfile;
    personal_t p;
    long pos;

    mainfile = fopen(mainfilename, "rb+");
    if (mainfile != NULL) {
        pos = hash(anterior.nombre, anterior.apellido);
        fseek(mainfile, pos, SEEK_SET);
        fread(&p, sizeof(personal_t), 1, mainfile);
        if (equals(p, anterior)) {
            if (strcmp(anterior.nombre, nuevo.nombre) != 0 || strcmp(anterior.apellido, nuevo.apellido) != 0) {
                baja(mainfilename, overflowname, anterior.nombre, anterior.apellido, anterior.direccion, anterior.telefono, anterior.fechaingreso);
                alta(mainfilename, overflowname, nuevo.nombre, nuevo.apellido, nuevo.direccion, nuevo.telefono, nuevo.fechaingreso);
            } else {
                strcpy(p.direccion, nuevo.direccion);
                p.telefono = nuevo.telefono;
                strcpy(p.fechaingreso, nuevo.fechaingreso);
                fseek(mainfile, pos, SEEK_SET);
                fwrite(&p, sizeof(personal_t), 1, mainfile);
            }
        } else {
            overflowfile = fopen(overflowname, "rb+");
            if (overflowfile != NULL) {
                pos = p.sig;
                fseek(overflowfile, p.sig, SEEK_SET);
                fread(&p, sizeof(personal_t), 1, overflowfile);
                while (!equals(p, anterior) && p.sig != -1) {
                    pos = p.sig;
                    fseek(overflowfile, pos, SEEK_SET);
                    fread(&p, sizeof(personal_t), 1, overflowfile);
                }
                if (equals(p, anterior)) {
                    if (strcmp(anterior.nombre, nuevo.nombre) != 0 || strcmp(anterior.apellido, nuevo.apellido) != 0) {
                        baja(mainfilename, overflowname, anterior.nombre, anterior.apellido, anterior.direccion, anterior.telefono, anterior.fechaingreso);
                        alta(mainfilename, overflowname, nuevo.nombre, nuevo.apellido, nuevo.direccion, nuevo.telefono, nuevo.fechaingreso);
                    } else {
                        strcpy(p.direccion, nuevo.direccion);
                        p.telefono = nuevo.telefono;
                        strcpy(p.fechaingreso, nuevo.fechaingreso);
                        fseek(overflowfile, pos, SEEK_SET);
                        fwrite(&p, sizeof(personal_t), 1, overflowfile);
                    }
                }
                fclose(overflowfile);
            }
        }
        fclose(mainfile);
    }
}

personal_t new_personal(char *nombre, char *apellido, char *direccion, int telefono, char *fechaingreso, estado_t estado, long sig) {
    personal_t p;

    strcpy(p.nombre, nombre);
    strcpy(p.apellido, apellido);
    strcpy(p.direccion, direccion);
    p.telefono = telefono;
    strcpy(p.fechaingreso, fechaingreso);
    p.estado = estado;
    p.sig = sig;
    return p;
}

int equals(personal_t this, personal_t that) {
    int iguales = 1;

    iguales &= strcmp(this.nombre, that.nombre) == 0 ? 1 : 0;
    iguales &= strcmp(this.apellido, that.apellido) == 0 ? 1 : 0;
    iguales &= strcmp(this.direccion, that.direccion) == 0 ? 1 : 0;
    iguales &= (this.telefono == that.telefono);
    iguales &= strcmp(this.fechaingreso, that.fechaingreso) == 0 ? 1 : 0;
    return iguales;
}

void listar(char *mainfilename, char *overflowname) {
    FILE *main = fopen(mainfilename, "rb");
    FILE *overflow = fopen(overflowname, "rb");
    personal_t p;
    int i;

    if (main != NULL) {
        printf("MAIN FILE:\n");
        i = 0;
        while (fread(&p, sizeof(personal_t), 1, main) == 1) {
            if (p.estado == OCUPADO) {
                printf("[%010d] %10s %10s %15s %10d %10s %ld\n", i, p.nombre, p.apellido, p.direccion, p.telefono, p.fechaingreso, p.sig == -1 ? p.sig : (p.sig / (long)sizeof(personal_t)));
            }
            i += 1;
        }
        fclose(main);
    }
    if (overflow != NULL) {
        printf("OVERFLOW FILE:\n");
        i = 0;
        while (fread(&p, sizeof(personal_t), 1, overflow) == 1) {
            if (p.estado == OCUPADO) {
                printf("[%010d] %10s %10s %10s %10d %10s %ld\n", i, p.nombre, p.apellido, p.direccion, p.telefono, p.fechaingreso, p.sig == -1 ? p.sig : (p.sig / (long)sizeof(personal_t)));
            }
            i += 1;
        }
        fclose(overflow);
    }
    printf("\n");
}
