#include <deque.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void **block;

struct _deque {
    block         *data;
    int            allocatedBlock;
    int            blockSize;
    int            blockUp, blockDown;
    int            begin, end;
    dequeDestroyFn destroy;
};

void _dequeShiftBlocksUp(Deque d, int shift) {
    int i;
    for (i = d->blockUp; i < d->blockDown; i++) {
        d->data[i - shift] = d->data[i];
        d->data[i]         = NULL;
    }
    d->blockUp -= shift;
    d->blockDown -= shift;
}

void _dequeShiftBlocksDown(Deque d, int shift) {
    int i;
    for (i = d->blockDown; i > d->blockUp; i--) {
        d->data[i + shift] = d->data[i];
        d->data[i]         = NULL;
    }
    d->blockUp += shift;
    d->blockDown += shift;
}

int _dequeUnusedBlockUp(Deque d) {
    return d->blockUp;
}

int _dequeUnusedBlockDown(Deque d) {
    return d->allocatedBlock - d->blockDown - 1;
}

void _dequeResolveBlockDown(Deque d) {
    int unusedBlockUp = _dequeUnusedBlockUp(d);
    if (unusedBlockUp > 5) {
        _dequeShiftBlocksUp(d, unusedBlockUp / 2);
    } else {
        int size = d->allocatedBlock;
        d->allocatedBlock *= 2;
        block *b = calloc(d->allocatedBlock, sizeof(block));
        memcpy(b, d->data, size * sizeof(block));
        free(d->data);
        d->data = b;
    }
}

void _dequeResolveBlockUp(Deque d) {
    int unusedBlockDown = _dequeUnusedBlockDown(d);
    if (unusedBlockDown > 5) {
        _dequeShiftBlocksDown(d, (unusedBlockDown / 2) + 1);
    } else {
        int size = d->allocatedBlock;
        d->allocatedBlock *= 2;
        block *b = calloc(d->allocatedBlock, sizeof(block));
        memcpy(b, d->data, size * sizeof(block));
        free(d->data);
        d->data         = b;
        unusedBlockDown = _dequeUnusedBlockDown(d);
        _dequeShiftBlocksDown(d, (unusedBlockDown / 2) + 1);
    }
}

Deque deque(dequeDestroyFn destroy) {
    Deque d           = calloc(1, sizeof(struct _deque));
    d->allocatedBlock = 10;
    d->blockSize      = 10;
    d->blockUp = d->blockDown = (d->allocatedBlock) / 2;
    d->begin = d->end = 0;
    d->data           = calloc(d->allocatedBlock, sizeof(block));
    d->destroy        = destroy;
    return d;
}

void dequePushBack(Deque d, void *data) {
    if (d->blockDown == d->allocatedBlock) {
        _dequeResolveBlockDown(d);
    }
    if (!d->data[d->blockDown]) {
        d->data[d->blockDown] = calloc(d->blockSize, sizeof(void **));
    }
    d->data[d->blockDown][d->end] = data;
    d->end += 1;
    if (d->end == d->blockSize) {
        d->blockDown += 1;
        d->end = 0;
    }
}

void dequePushFront(Deque d, void *data) {
    d->begin -= 1;
    if (d->begin == -1) {
        d->blockUp -= 1;
        d->begin = d->blockSize - 1;
    }
    if (d->blockUp == -1) {
        _dequeResolveBlockUp(d);
    }
    if (!d->data[d->blockUp]) {
        d->data[d->blockUp] = calloc(d->blockSize, sizeof(void **));
    }
    d->data[d->blockUp][d->begin] = data;
}

void *dequePopBack(Deque d) {
    if (d->begin == d->end && d->blockUp == d->blockDown) {
        printf("error: pop with empty deque\n.");
        exit(1);
    }
    int   last = dequeSize(d) - 1;
    void *data = dequeAt(d, last);
    d->end -= 1;
    if (d->end == 0) {
        free(d->data[d->blockDown]);
        d->data[d->blockDown] = NULL;
    }
    if (d->end == -1) {
        d->end = d->blockSize - 1;
        d->blockDown -= 1;
    }
    return data;
}

void *dequePopFront(Deque d) {
    if (d->begin == d->end && d->blockUp == d->blockDown) {
        printf("error: pop with empty deque\n.");
        exit(1);
    }
    void *data = dequeAt(d, 0);
    d->begin += 1;
    if (d->begin == d->blockSize) {
        d->begin = 0;
        free(d->data[d->blockUp]);
        d->data[d->blockUp] = NULL;
        d->blockUp += 1;
    }
    return data;
}

void *dequeAt(Deque d, int i) {
    int at    = (i + d->begin) % d->blockSize;
    int block = (i + d->begin) / d->blockSize;
    return d->data[d->blockUp + block][at];
}

int dequeSize(Deque d) {
    int size = d->end - d->begin + d->blockSize * (d->blockDown - d->blockUp);
    return size;
}

void dequeDestroy(Deque d) {
    int i;
    int size = dequeSize(d);
    for (i = 0; i < size; i++) {
        void *data = dequePopBack(d);
        d->destroy(data);
    }
    for (i = 0; i < d->allocatedBlock; i++) {
        free(d->data[i]);
    }
    free(d->data);
    free(d);
}