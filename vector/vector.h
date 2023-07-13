#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct _vector *Vector;

typedef void (*vectorDestroyFn)(void *);

Vector vector(vectorDestroyFn destroy);
void  *vectorAt(Vector v, int x);
int    vectorSize(Vector v);
void   vectorPush(Vector v, void *data);
void   vectorDestroy(Vector v);

#endif