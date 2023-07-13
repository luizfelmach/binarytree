#include <binaryTree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int   age;
    float height;
} People;

People *people(char *name, int age, float height);
People *peopleRead();
int     peopleCmp(void *t1, void *t2);
void    peopleShow(People *p);
void    peopleDestroy(void *x);

int main() {
    BinaryTree bt = binaryTree(peopleCmp, peopleDestroy);
    int        i, k;
    char       action[10], name[200];
    scanf("%d%*c", &k);
    for (i = 0; i < k; i++) {
        scanf("%s%*c", action);
        if (!strcmp(action, "SET")) {
            People *p = peopleRead();
            binaryTreeSet(bt, p);
        }
        if (!strcmp(action, "GET")) {
            scanf("%s%*c", name);
            People *mock = people(name, 0, 0);
            People *p    = binaryTreeGet(bt, mock);
            peopleShow(p);
            peopleDestroy(mock);
        }
        if (!strcmp(action, "POP_MAX")) {
            if (!binaryTreeEmpty(bt)) {
                People *p = binaryTreeMaxPop(bt);
                peopleShow(p);
                peopleDestroy(p);
            } else {
                printf("ARVORE VAZIA\n");
            }
        }
        if (!strcmp(action, "POP_MIN")) {
            if (!binaryTreeEmpty(bt)) {
                People *p = binaryTreeMinPop(bt);
                peopleShow(p);
                peopleDestroy(p);
            } else {
                printf("ARVORE VAZIA\n");
            }
        }
    }
    binaryTreeDestroy(bt);
    return 0;
}

People *people(char *name, int age, float height) {
    People *p = calloc(1, sizeof(People));
    p->name   = strdup(name);
    p->age    = age;
    p->height = height;
    return p;
}

People *peopleRead() {
    char  cpf[200], name[200];
    int   age;
    float height;
    scanf("%s %d %f%*c", name, &age, &height);
    return people(name, age, height);
}

int peopleCmp(void *t1, void *t2) {
    People *p1 = t1;
    People *p2 = t2;
    return strcmp(p1->name, p2->name);
}

void peopleShow(People *p) {
    printf("%s %d %.2f\n", p->name, p->age, p->height);
}

void peopleDestroy(void *x) {
    People *p = x;
    free(p->name);
    free(p);
}
