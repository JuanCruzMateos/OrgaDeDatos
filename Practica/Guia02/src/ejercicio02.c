#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * @author Juan Cruz Mateos
 * @matricula 15134
 */

#define FMT_OBS 100

typedef struct examen {
    unsigned int cod_uni;   // E4
    unsigned int cod_facu;  // E4
    unsigned int cod_asig;  // E4
    unsigned int legajo;    // E4
    unsigned int edad;      // E4
    unsigned int cod_doc;   // E4
    int nota;               // E4
    char obs[FMT_OBS];      // C100
} examen_t;

/**
 *
 *  Identificadores:
 *      - cod_asig
 *      - legajo
 *      - nota
 *
 *  Registros desordenados:
 *   > altas: append
 *   > bajas: marcado -> cambio signo del identificador (nota)
 *   > modificaciones
 *   > consultas - promedio con y sin aplazo del alumno
 *               - cantidad de materias rendidas
 *               - promedio de notas de una materia dada.
 *
 */

long getfilesize(char *filename);
long int filesize(FILE *file);

void alta(FILE *file, examen_t examen);
void baja(FILE *file, unsigned int asig, unsigned int legajo, int nota);
void mantenimiento(FILE **file, char *filename);

void modificacion(FILE *file, examen_t ant, examen_t nuevo);
double promedio_con_aplazos(FILE *file, unsigned int legajo);
double promedio_sin_aplazos(FILE *file, unsigned int legajo);
int materias_rendidas(FILE *file, unsigned int legajo);
double promedio_materia(FILE *file, unsigned int cod_asig);

void init_file(char *inputfile, FILE *newfile);
void print_file(FILE *file);

int main(int argc, char const *argv[]) {
    char *filename = "./dat/examenes.dat";
    FILE *file;

    if (access(filename, F_OK) == 0) {
        file = fopen(filename, "r+b");
    } else {
        file = fopen(filename, "w+b");
        init_file("./dat/examenes.txt", file);
    }

    // if (filesize(file) == 0) {
    // init_file("./dat/examenes.txt", file);
    // }

    examen_t e1 = {.cod_uni = 0, .cod_facu = 0, .cod_asig = 0, .legajo = 0, .edad = 0, .cod_doc = 0, .nota = 0, .obs = "0"};
    examen_t e2 = {.cod_uni = 1, .cod_facu = 1, .cod_asig = 1, .legajo = 1, .edad = 1, .cod_doc = 1, .nota = 1, .obs = "1"};
    examen_t e3 = {.cod_uni = 2, .cod_facu = 2, .cod_asig = 2, .legajo = 2, .edad = 2, .cod_doc = 2, .nota = 2, .obs = "2"};

    // print_file(file);

    alta(file, e1);
    alta(file, e2);
    alta(file, e3);

    // print_file(file);

    unsigned int legajo = 134;
    unsigned int asignatura = 13;

    printf("prom con aplazos leg=%d ==  %lf\n", legajo, promedio_con_aplazos(file, legajo));
    printf("prom sin aplazos leg=%d ==  %lf\n", legajo, promedio_sin_aplazos(file, legajo));
    printf("materias rendidas leg=%d == %d\n", legajo, materias_rendidas(file, legajo));
    printf("promedio notas mat=%d == %lf\n", asignatura, promedio_materia(file, asignatura));

    baja(file, 12, 15134, 10);
    baja(file, 1, 1, 1);

    print_file(file);

    mantenimiento(&file, filename);

    print_file(file);

    fclose(file);
    return 0;
}

long int filesize(FILE *file) {
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

void alta(FILE *file, examen_t examen) {
    // posicionamiento al final de archivo
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        fwrite(&examen, sizeof(examen_t), 1, file);
    }
}

void baja(FILE *file, unsigned int asig, unsigned int legajo, int nota) {
    long int pos = -1;
    examen_t act;

    if (file != NULL) {
        fseek(file, 0, SEEK_SET);
        // primero pregunto por pos para que una vez que sea != no haga el read modificando act
        while (pos == -1 && fread(&act, sizeof(examen_t), 1, file) == 1) {
            if (act.cod_asig == asig && act.legajo == legajo && act.nota == nota) {
                pos = ftell(file) - sizeof(examen_t);  // retrocedo a la posicion leida
            }
        }
        if (pos != -1) {
            act.nota = act.nota * -1;
            fseek(file, pos, SEEK_SET);
            fwrite(&act, sizeof(examen_t), 1, file);
        }
    }
}

void mantenimiento(FILE **file, char *filename) {
    char *tempname = "./dat/aux.bin";
    FILE *temp = fopen(tempname, "wb");
    examen_t examen;

    fseek(*file, 0, SEEK_SET);
    while (fread(&examen, sizeof(examen_t), 1, *file) == 1) {
        if (examen.nota > 0) {
            fwrite(&examen, sizeof(examen_t), 1, temp);
        }
    }

    fclose(*file);
    fclose(temp);
    remove(filename);
    rename(tempname, filename);
    *file = fopen(filename, "r+b");
}

void modificacion(FILE *file, examen_t ant, examen_t nuevo) {
    // TODO
}

double promedio_con_aplazos(FILE *file, unsigned int legajo) {
    examen_t examen;
    unsigned int suma = 0, total = 0;

    if (file != NULL) {
        fseek(file, 0, SEEK_SET);
        while (fread(&examen, sizeof(examen_t), 1, file) == 1) {
            if (examen.legajo == legajo) {
                suma += examen.nota;
                total += 1;
            }
        }
    }
    return (total == 0) ? 0.0 : (double)suma / total;
}

double promedio_sin_aplazos(FILE *file, unsigned int legajo) {
    examen_t examen;
    unsigned int suma = 0, total = 0;

    if (file != NULL) {
        fseek(file, 0, SEEK_SET);
        while (fread(&examen, sizeof(examen_t), 1, file) == 1) {
            if (examen.legajo == legajo && examen.nota >= 4) {
                suma += examen.nota;
                total += 1;
            }
        }
    }
    return (total == 0) ? 0.0 : (double)suma / total;
}

int materias_rendidas(FILE *file, unsigned int legajo) {
    unsigned int rendidas[50], n = 0, i;
    examen_t examen;
    int cant = 0;

    if (file != NULL) {
        fseek(file, 0, SEEK_SET);
        while (fread(&examen, sizeof(examen_t), 1, file) == 1) {
            if (examen.legajo == legajo) {
                i = 0;
                while (i < n && examen.cod_asig != rendidas[i]) {
                    i += 1;
                }
                if (i == n) {
                    cant += 1;
                    rendidas[n++] = examen.cod_asig;
                }
            }
        }
    }
    return cant;
}

double promedio_materia(FILE *file, unsigned int cod_asig) {
    unsigned int suma = 0, cant = 0;
    examen_t examen;

    if (file != NULL) {
        fseek(file, 0, SEEK_SET);
        while (fread(&examen, sizeof(examen_t), 1, file) == 1) {
            if (examen.cod_asig == cod_asig) {
                suma += examen.nota;
                cant += 1;
            }
        }
    }
    return cant == 0 ? 0.0 : (double)suma / cant;
}

void init_file(char *inputfile, FILE *newfile) {
    FILE *source;
    examen_t examen;

    source = fopen(inputfile, "rt");
    if (source != NULL) {
        fscanf(source, "%*[^\n]\n");  // skip first line
        while (fscanf(source, "%u%u%u%u%u%u%d", &examen.cod_uni, &examen.cod_facu, &examen.cod_asig, &examen.legajo, &examen.edad, &examen.cod_doc, &examen.nota) == 7) {
            fgets(examen.obs, FMT_OBS, source);
            fwrite(&examen, sizeof(examen_t), 1, newfile);
        }
        fclose(source);
    }
}

void print_file(FILE *file) {
    size_t count = 0;
    examen_t examen;

    // posicionamiento al comienzo del archivo
    fseek(file, 0, SEEK_SET);
    while (fread(&examen, sizeof(examen_t), 1, file) == 1) {
        printf("#%ld\n", ++count);
        printf("cod_univ=%d\n", examen.cod_uni);
        printf("cod_fac=%d\n", examen.cod_facu);
        printf("cod_asig=%d\n", examen.cod_asig);
        printf("legajo=%d\n", examen.legajo);
        printf("edad=%d\n", examen.edad);
        printf("cod_doc=%d\n", examen.cod_doc);
        printf("nota=%d\n", examen.nota);
        printf("obs=%s\n\n\n", examen.obs);
    }
}

// not portable
long getfilesize(char *filename) {
    struct stat file_status;
    if (stat(filename, &file_status) < 0) {
        return -1;
    }
    return file_status.st_size;
}