
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

struct _vector {
    void          **data;
    int             size, allocated;
    vectorDestroyFn destroy;
};

Vector vector(vectorDestroyFn destroy) {
    Vector v     = calloc(1, sizeof(struct _vector));
    v->allocated = 100;
    v->destroy   = destroy;
    v->size      = 0;
    v->data      = calloc(v->allocated, sizeof(void *));
    return v;
}

int vectorSize(Vector v) {
    return v->size;
}

void *vectorAt(Vector v, int i) {
    return v->data[i];
}

void vectorPush(Vector v, void *data) {
    if (v->size == v->allocated) {
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof(void *));
    }

    v->data[v->size++] = data;
}

void vectorDestroy(Vector v) {
    int i;
    for (i = 0; i < v->size; i++) {
        v->destroy(v->data[i]);
    }
    free(v->data);
    free(v);
}