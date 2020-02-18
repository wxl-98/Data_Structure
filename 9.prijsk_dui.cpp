/***********************************************************
*       &Author: Wang Xianling     
*       &E-mail: wang_xianling@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: 9.prijsk_dui.cpp
*       &Created Time:  2020年02月18日 星期二 22时44分40秒  CST  Day/049 and Week/07 of this year
*       &Description:
***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct Heap {
    double *data;
    int size, length;
} Heap;

Heap *init(int size) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (double *)malloc(sizeof(double) * size);
    h->size = size;
    h->length = 0;
    return h;
}

int empty(Heap *h) {
    return h->length == 0;
}

void output(Heap *h) {
    printf("Heap = [");
    for (int i = 0; i < h->length; i++) {
        printf("%.4f, ", h->data[i]);
    }
    printf("]\n");
    return ;
}

void update(Heap *h, int ind) {
    int max_ind, lchild, rchild;
    max_ind = ind;
    lchild = ind * 2 + 1;
    rchild = ind * 2 + 2;
    if (lchild < h->length && h->data[max_ind] < h->data[lchild]) {
        max_ind = lchild;
    }
    if (rchild < h->length && h->data[max_ind] < h->data[rchild]) {
        max_ind = rchild;
    }
    if (max_ind != ind) {
        swap(h->data[ind], h->data[max_ind]);
        update(h, max_ind);
    }
    return ;
}

int push(Heap *h, double data) {
    if (h->length >= h->size) return 0;
    int current, father;
    current = h->length;
    father = (current - 1) / 2;
    h->data[h->length] = data;
    h->length++;
    while (h->data[current] > h->data[father]) {
        swap(h->data[current], h->data[father]);
        current = father;
        father = (current - 1) / 2;
    }
    return 1;
}

void pop(Heap *h) {
    if (empty(h)) return ;
    h->length--;
    swap(h->data[0], h->data[h->length]);
    update(h, 0);
    return ;
}

double top(Heap *h) {
    return h->data[0];
}

void clear(Heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

void haf(Heap *h) {
    if (empty(h)) return ;
    while (h->length > 1) {
        double a, b;
        a = top(h);
        pop(h);
        b = top(h);
        pop(h);
        push(h, pow(a, 1.0 / 3.0) * pow(b, 2.0 / 3.0));
    }
    return ;
}


int main() {
    int n;
    scanf("%d", &n);
    Heap *h = init(n * 2 + 5);
    for (int i = 0; i < n; i++) {
        double temp;
        scanf("%lf", &temp);
        push(h, temp);
    }
    haf(h);
    printf("%lf\n", top(h));
    clear(h);
    return 0;
}
