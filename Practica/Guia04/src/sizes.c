#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    printf("%-20s %ld \n", "void*", sizeof(void *));
    printf("%-20s %ld \n", "void", sizeof(void));
    printf("%-20s %ld \n", "char", sizeof(char));
    printf("%-20s %ld \n", "int", sizeof(int));
    printf("%-20s %ld \n", "short int", sizeof(short int));
    printf("%-20s %ld \n", "long int", sizeof(long int));
    printf("%-20s %ld \n", "short", sizeof(short));
    printf("%-20s %ld \n", "long", sizeof(long));
    printf("%-20s %ld \n", "unsigned int", sizeof(unsigned int));
    printf("%-20s %ld \n", "unsigned short int", sizeof(unsigned short int));
    printf("%-20s %ld \n", "unsigned long int", sizeof(unsigned long int));
    printf("%-20s %ld \n", "float", sizeof(float));
    printf("%-20s %ld \n", "double", sizeof(double));
    return 0;
}
