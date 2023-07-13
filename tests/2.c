#include <binaryTree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y, index;
} Cell;

Cell *cell(int x, int y, int index);
Cell *cellRead();
int   cellCmp(void *t1, void *t2);
void  cellShow(Cell *p);
void  cellDestroy(void *x);

int main() {
    BinaryTree bt = binaryTree(cellCmp, cellDestroy);
    int        i, k;
    int        x, y;
    char       action[10];
    scanf("%d%*c", &k);
    for (i = 0; i < k; i++) {
        scanf("%s%*c", action);
        if (!strcmp(action, "SET")) {
            Cell *p = cellRead();
            binaryTreeSet(bt, p);
        }
        if (!strcmp(action, "GET")) {
            scanf("%d %d%*c", &x, &y);
            Cell *mock = cell(x, y, 0);
            Cell *p    = binaryTreeGet(bt, mock);
            cellShow(p);
            cellDestroy(mock);
        }
    }
    binaryTreeDestroy(bt);
    return 0;
}

Cell *cell(int x, int y, int index) {
    Cell *c  = calloc(1, sizeof(Cell));
    c->x     = x;
    c->y     = y;
    c->index = index;
    return c;
}

Cell *cellRead() {
    int x, y, index;
    scanf("%d %d %d%*c", &x, &y, &index);
    return cell(x, y, index);
}

int cellCmp(void *t1, void *t2) {
    Cell *c1 = t1;
    Cell *c2 = t2;
    if (c1->x == c2->x && c1->y == c2->y) return 0;
    if (c1->x < c2->x) return -1;
    return 1;
}

void cellShow(Cell *c) {
    printf("%d\n", c->index);
}

void cellDestroy(void *x) {
    free(x);
}
