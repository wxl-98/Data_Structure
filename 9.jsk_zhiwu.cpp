/***********************************************************
*       &Author: Wang Xianling     
*       &E-mail: wang_xianling@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: 9.jsk_zhiwu.cpp
*       &Created Time:  2020年02月19日 星期三 16时43分19秒  CST  Day/050 and Week/07 of this year
*       &Description:
***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}
typedef struct Node {
    int index, dis;
} Node;

typedef struct Heap {
    Node *data;
    int size, length;
} Heap;


Heap *init(Heap * h, int size) {
   // Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (Node *)malloc(sizeof(Node) * size);
    h->size = size;
    h->length = 0;
    return h;
}

int empty(Heap *h) {
    return h->length == 0;
}

int cmd(Node a, Node b) {
    if (a.dis == b.dis) {
        return a.index < b.index;
    }
    return a.dis > b.dis;
}

void push(Heap *h, Node data) {
    if (h->length >= h->size) return ;
    h->data[h->length] = data;
    int current, father;
    current = h->length;
    father = (current - 1) / 2;
    h->length++;
    while (cmd(h->data[current], h->data[father])) {
        swap(h->data[current], h->data[father]);
        current = father;
        father = (current - 1) / 2;
    }
    return ;
}

void update(Heap *h, int pos) {
    int min_loc, lchild, rchild;
    min_loc = pos;
    lchild = pos * 2 + 1;
    rchild = pos * 2 + 2;
    if (lchild < h->length && !cmd(h->data[min_loc], h->data[lchild])) {
        min_loc = lchild;
    }
    if (rchild < h->length && !cmd(h->data[min_loc], h->data[rchild])) {
        min_loc = rchild;
    }
    if (min_loc != pos) {
        swap(h->data[min_loc], h->data[pos]);
        update(h, min_loc);
    }
    return ;
}

void pop(Heap *h) {
    if (empty(h)) return ;
    h->length--;
    swap(h->data[0], h->data[h->length]);
    update(h, 0);
    return ;
}

Node top(Heap *h) {
    return h->data[0];
}

void clear(Heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int main() {
    int t, n, cnt = 0;
    scanf("%d", &t);
    Heap *h[101];
    for (int i = 1; i <= 100; i++) {
        h[i] = (Heap *)malloc(sizeof(Heap));
        init(h[i], 50000);
    }
    while (cnt < t) {
        printf("Case #%d:\n", ++cnt);
        scanf("%d", &n);
        Node node;
        int s;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &node.dis, &s);
            node.index = i + 1;
            push(h[s], node);
        }
        for (int i = 0; i < n; i++) {
            int m = -1;
            Node node1, node2;
            for (int j = 1; j <= 100; j++) {
                if (empty(h[j])) continue;
                if (m == -1) {
                    m = j;
                    continue;
                }
                node1 = top(h[m]);
                node2 = top(h[j]);
                node1.dis = node1.dis + i * m;
                node2.dis = node2.dis + i * j;
                if (cmd(node2, node1)) {
                    m = j;
                }
            }
            printf("%d", top(h[m]).index);
            pop(h[m]);
         	if (i != n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 1; i <= 100; i++) {
        clear(h[i]);
    }
    return 0;
}

