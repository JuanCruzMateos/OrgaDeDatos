#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @author Juan Cruz Mateos
 *
 * Compilacion:: gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ./bin/heap heap.c
 */

#define MAX 50

typedef struct heap {
    int *datos;
    int ult;
} heap;

typedef heap *heap_t;

heap_t new_heap();
int padre(int i);
int izq(int i);
int der(int i);
void push(heap_t heap, int x);
int peek(heap_t heap);
int pop(heap_t heap);
void percolate_up(heap_t heap, int i);
void percolate_down(heap_t heap, int i);
void preorden(heap_t heap, int pos);
void inorden(heap_t heap, int pos);
void postorden(heap_t heap, int pos);
int empty(heap_t heap);
void print_heap(heap_t heap);
void free_heap(heap_t heap);

// heap sort

int esta_it(heap_t heap, int x);
int esta_rec(heap_t heap, int pos, int x);
void persistir(heap_t heap, char *filename);
void despersistir(heap_t heap, char *filename);

int main(int argc, char const *argv[]) {
    int vec[5] = {3, 9, 2, 8, 1};
    heap_t heap;

    heap = new_heap();
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++) {
        push(heap, rand() % 20);
    }
    inorden(heap, 0);
    printf("\n");
    // persistir(heap, "../dat/heap.dat");
    free_heap(heap);
    return 0;
}

heap_t new_heap() {
    heap_t h;

    h = (heap_t)malloc(sizeof(heap));
    if (h == NULL)
        return NULL;
    h->datos = (int *)(malloc(sizeof(int) * MAX));
    if (h->datos == NULL)
        return NULL;
    h->ult = -1;
    return h;
}

int padre(int i) {
    return (i - 1) / 2;
}

int izq(int i) {
    return 2 * i + 1;
}

int der(int i) {
    return 2 * i + 2;
}

void push(heap_t heap, int x) {
    int i, temp;

    if (heap->ult != MAX - 1) {
        heap->datos[++heap->ult] = x;
        i = heap->ult;
        // percolate_up(heap, heap->ult);
        while (heap->datos[padre(i)] > heap->datos[i]) {
            temp = heap->datos[padre(i)];
            heap->datos[padre(i)] = heap->datos[i];
            heap->datos[i] = temp;
            i = padre(i);
        }
    }
}

void percolate_up(heap_t heap, int i) {
    int temp;

    // padre(0) == 0
    if (i != 0 && heap->datos[padre(i)] > heap->datos[i]) {
        temp = heap->datos[padre(i)];
        heap->datos[padre(i)] = heap->datos[i];
        heap->datos[i] = temp;
        percolate_up(heap, padre(i));
    }
}

int peek(heap_t heap) {
    if (heap->ult != -1) {
        return heap->datos[heap->ult];
    } else {
        return __INT_MAX__;
    }
}

int pop(heap_t heap) {
    int min = __INT_MAX__;

    if (heap->ult != -1) {
        min = heap->datos[0];
        heap->datos[0] = heap->datos[heap->ult];
        heap->ult -= 1;
        percolate_down(heap, 0);
    }
    return min;
}

void percolate_down(heap_t heap, int i) {
    int min, temp;

    if (i < heap->ult) {
        min = i;
        if (izq(i) <= heap->ult && heap->datos[izq(i)] < heap->datos[min])
            min = izq(i);
        if (der(i) <= heap->ult && heap->datos[der(i)] < heap->datos[min])
            min = der(i);
        if (min != i) {
            temp = heap->datos[min];
            heap->datos[min] = heap->datos[i];
            heap->datos[i] = temp;
            percolate_down(heap, min);
        }
    }
}

int empty(heap_t heap) {
    return heap->ult == -1;
}

void preorden(heap_t heap, int pos) {
    if (pos <= heap->ult) {
        printf("%d ", heap->datos[pos]);
        preorden(heap, izq(pos));
        preorden(heap, der(pos));
    }
}

void inorden(heap_t heap, int pos) {
    if (pos <= heap->ult) {
        inorden(heap, izq(pos));
        printf("%d ", heap->datos[pos]);
        inorden(heap, der(pos));
    }
}

void postorden(heap_t heap, int pos) {
    if (pos <= heap->ult) {
        postorden(heap, izq(pos));
        postorden(heap, der(pos));
        printf("%d ", heap->datos[pos]);
    }
}

void print_heap(heap_t heap) {
    int i;

    printf("| ");
    for (i = 0; i <= heap->ult; i++) {
        printf("%d ", heap->datos[i]);
    }
    printf("|\n");
}

void free_heap(heap_t heap) {
    free(heap->datos);
    free(heap);
}

int esta_it(heap_t heap, int x) {
    int i;

    if (heap->ult == -1 || x < heap->datos[0])
        return 0;
    else {
        i = 0;
        while (i <= heap->ult && heap->datos[i] != x) {
            i += 1;
        }
        return i <= heap->ult;
    }
}

int esta_rec(heap_t heap, int pos, int x) {
    if (pos > heap->ult || x < heap->datos[pos])
        return 0;
    else if (x == heap->datos[pos])
        return 1;
    else
        return esta_rec(heap, izq(pos), x) || esta_rec(heap, der(pos), x);
}

void persistir(heap_t heap, char *filename) {
    FILE *file = fopen(filename, "wb");
    int i = 0;

    while (i <= heap->ult) {
        fwrite(&(heap->datos[i]), sizeof(int), 1, file);
        i++;
    }
    fclose(file);
}

void despersistir(heap_t heap, char *filename) {
    FILE *file = fopen(filename, "rb");
    int i, clave;

    if (file != NULL) {
        i = -1;
        while (fread(&clave, sizeof(int), 1, file) == 1) {
            heap->datos[++i] = clave;
        }
        heap->ult = i;
        fclose(file);
    }
}
