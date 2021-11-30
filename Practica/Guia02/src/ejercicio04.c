#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @author Juan Cruz Mateos
 * @matricula 15134
 */

#define FMT_DESC 100

typedef struct item {
    int id;
    char desc[FMT_DESC];
    double valor;
} item_t;

int main(int argc, char const *argv[]) {
    FILE *file;
    char *filename = "./dat/maestro.dat";

    if (access(filename, F_OK) == 0) {
        file = fopen(filename, "r+b");
    } else {
        file = fopen(filename, "w+b");
    }

    item_t item;
    char desc[FMT_DESC];

    for (int i = 0; i < 5; i++) {
        item.id = i + 1;
        sprintf(desc, "decripcion %d", i + 1);
        strcpy(item.desc, desc);
        item.valor = 120.0 + i + 1;
        fwrite(&item, sizeof(item), 1, file);
    }

    fseek(file, 0, SEEK_SET);
    while (fread(&item, sizeof(item_t), 1, file) == 1) {
        printf("id = %d\tdesc = %-20s\tval = %0.2lf\n", item.id, item.desc, item.valor);
    }
    printf("eof == %d\n", feof(file));
    fread(&item, sizeof(item_t), 1, file);
    printf("ultimo\nid = %d\tdesc = %-20s\tval = %0.2lf\n", item.id, item.desc, item.valor);
    fclose(file);
    return 0;
}
