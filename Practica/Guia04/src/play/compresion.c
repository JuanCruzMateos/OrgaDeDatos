#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *toBinaryString(int num) {
    char *bin;
    char arr[30];
    int i = 0;

    arr[0] = 0;
    while (num != 0) {
        arr[i++] = (char)(num % 2);
        num /= 2;
    }
    bin = (char *)malloc(sizeof(char) * (unsigned long)(i + 1));
    for (int j = i; j >= 0; j--) {
        bin[i - j] = '0' + arr[j];
    }
    bin[i + 1] = '\0';
    return bin;
}

int main(int argc, char const *argv[]) {
    int xor ;
    int M = 512;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
            xor = argv[i][0];
            printf("%c = %s\n", argv[i][0], toBinaryString(argv[i][0]));
            for (int j = 1; j < strlen(argv[i]); j++) {
                xor ^= argv[i][j];
                printf("%c = %s\n", argv[i][j], toBinaryString(argv[i][j]));
            }
            printf("xor %% %d = %d\n\n", M, xor % M);
        }
    }
    return 0;
}
