#ifndef DEQUE_H
#define DEQUE_H

typedef struct _deque *Deque;
typedef void (*dequeDestroyFn)(void *);

Deque deque(dequeDestroyFn destroy);
void  dequePushBack(Deque d, void *data);
void  dequePushFront(Deque d, void *data);
void *dequePopBack(Deque d);
void *dequePopFront(Deque d);
void *dequeAt(Deque d, int i);
int   dequeSize(Deque d);
void  dequeDestroy(Deque d);

#endif