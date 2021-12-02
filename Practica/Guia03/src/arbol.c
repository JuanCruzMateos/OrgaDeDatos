#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @author Juan Cruz Mateos
 *
 * Compilacion:: gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ./bin/arbol arbol.c
 */

typedef struct nodo_persist {
    int clave;
    int nivel;
    int izq;
    int der;
} nodo_persist_t;

typedef struct nodo {
    int clave;
    struct nodo *izq;
    struct nodo *der;
} nodo_t;

typedef nodo_t *arbol_t;

void addNodo(arbol_t *root, int x);
void preorden(arbol_t root);
void inorden(arbol_t root);
void postorden(arbol_t root);
int esta(arbol_t root, int x);

void add_nodo_ABB(arbol_t *root, int x);
int esta_ABB_rec(arbol_t root, int x);
int esta_ABB_it(arbol_t root, int x);

void persistir_txt(arbol_t root, int nivel, FILE *file);
void persistir_bin(arbol_t root, int nivel, FILE *file);

int main(int argc, char const *argv[]) {
    arbol_t root = NULL;
    FILE *file_txt, *file_bin;

    srand(time(NULL));
    for (int i = 0; i < 15; i++) {
        add_nodo_ABB(&root, rand() % 100);
    }

    file_txt = fopen("./arbol.txt", "wt");
    persistir_txt(root, 0, file_txt);
    fclose(file_txt);

    file_bin = fopen("./arbol.dat", "wb");
    persistir_bin(root, 0, file_bin);
    fclose(file_bin);
    inorden(root);
    return 0;
}

void addNodo(arbol_t *root, int x) {
    *root = (arbol_t)malloc(sizeof(nodo_t));
    (*root)->clave = x;
    (*root)->izq = NULL;
    (*root)->der = NULL;
}

void preorden(arbol_t root) {
    if (root != NULL) {
        printf("%d ", root->clave);
        preorden(root->izq);
        preorden(root->der);
    }
}

void inorden(arbol_t root) {
    if (root != NULL) {
        inorden(root->izq);
        printf("%d ", root->clave);
        inorden(root->der);
    }
}

void postorden(arbol_t root) {
    if (root != NULL) {
        postorden(root->izq);
        postorden(root->der);
        printf("%d ", root->clave);
    }
}

int esta(arbol_t root, int x) {
    if (root == NULL)
        return 0;
    else if (root->clave == x)
        return 1;
    else
        return esta(root->izq, x) || esta(root->der, x);
}

// ABB

void add_nodo_ABB(arbol_t *root, int x) {
    if (*root == NULL) {
        *root = (arbol_t)malloc(sizeof(nodo_t));
        (*root)->clave = x;
        (*root)->izq = NULL;
        (*root)->der = NULL;
    } else {
        if (x < (*root)->clave)
            add_nodo_ABB(&(*root)->izq, x);
        else
            add_nodo_ABB(&(*root)->der, x);
    }
}

int esta_ABB_rec(arbol_t root, int x) {
    if (root == NULL)
        return 0;
    else if (root->clave == x)
        return 1;
    else if (x < root->clave)
        return esta_ABB_rec(root->izq, x);
    else
        return esta_ABB_rec(root->der, x);
}

int esta_ABB_it(arbol_t root, int x) {
    while (root != NULL && root->clave != x) {
        root = x < root->clave ? root->izq : root->der;
    }
    return root != NULL;
}

void persistir_txt(arbol_t root, int nivel, FILE *file) {
    if (root != NULL) {
        if (root->izq != NULL && root->der != NULL)
            fprintf(file, "clave=%d\tnivel=%d\tizq=%d\tder=%d\n", root->clave, nivel, root->izq->clave, root->der->clave);
        else if (root->izq != NULL && root->der == NULL)
            fprintf(file, "clave=%d\tnivel=%d\tizq=%d\tder=null\n", root->clave, nivel, root->izq->clave);
        else if (root->izq == NULL && root->der != NULL)
            fprintf(file, "clave=%d\tnivel=%d\tizq=null\tder=%d\n", root->clave, nivel, root->der->clave);
        else
            fprintf(file, "clave=%d\tnivel=%d\tizq=null\tder=null\n", root->clave, nivel);
        persistir_txt(root->izq, nivel + 1, file);
        persistir_txt(root->der, nivel + 1, file);
    }
}

void persistir_bin(arbol_t root, int nivel, FILE *file) {
    nodo_persist_t persist;

    if (root != NULL) {
        persist.clave = root->clave;
        persist.nivel = nivel;
        if (root->izq != NULL && root->der != NULL) {
            persist.izq = root->izq->clave;
            persist.der = root->der->clave;
        } else if (root->izq != NULL && root->der == NULL) {
            persist.izq = root->izq->clave;
            persist.der = -1;
        } else if (root->izq == NULL && root->der != NULL) {
            persist.izq = -1;
            persist.der = root->der->clave;
        } else {
            persist.izq = -1;
            persist.der = -1;
        }
        fwrite(&persist, sizeof(nodo_persist_t), 1, file);
        persistir_bin(root->izq, nivel + 1, file);
        persistir_bin(root->der, nivel + 1, file);
    }
}
