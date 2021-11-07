#include <stdio.h>
#include <stdlib.h>

typedef struct persona {
    char nombre[20];
    int edad;
} persona_t;

int main(int argc, char const *argv[]) {
    persona_t p1 = {
        .nombre = "Juan",
        .edad = 27};

    persona_t p2 = {
        .nombre = "Cande",
        .edad = 26};

    persona_t p3 = {
        .nombre = "Guada",
        .edad = 24};

    FILE *file = fopen("personas.dat", "wb+");
    fwrite(&p1, sizeof(persona_t), 1, file);
    fwrite(&p2, sizeof(persona_t), 1, file);
    fwrite(&p3, sizeof(persona_t), 1, file);
    fclose(file);

    persona_t p;

    file = fopen("personas.dat", "rb+");

    // while (fread(&p, sizeof(persona_t), 1, file) == 1) {
    //     printf("%s %d FEOF=%d\n", p.nombre, p.edad, feof(file));
    // }
    // printf("%s %d FEOF=%d\n", p.nombre, p.edad, feof(file));

    fseek(file, -sizeof(persona_t), SEEK_END);
    fread(&p, sizeof(persona_t), 1, file);
    printf("%s %d FEOF=%d\n", p.nombre, p.edad, feof(file));

    printf("FTELL=%ld\n", ftell(file));

    fseek(file, ftell(file) - (long)sizeof(persona_t), SEEK_END);
    fread(&p, sizeof(persona_t), 1, file);

    printf("%s %d FEOF=%d\n", p.nombre, p.edad, feof(file));
    printf("FTELL=%ld\n", ftell(file));

    // para que feof de true hay que leer el fin de archivo, no basta que apunte al fin
    fclose(file);
    return 0;
}
