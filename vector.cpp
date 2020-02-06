/***********************************************************
*       &Author: Wang Xianling     
*       &E-mail: wang_xianling@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: vector.cpp
*       &Created Time:  2020年02月04日 星期二 21时44分54秒  CST  Day/035 and Week/05 of this year
*       &Description:
***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vector {
    int *data;
    int size, length;
} Vector;


Vector *init(int n) { //初始化一个存储n个元素的顺序表
    Vector *vec = (Vector *)malloc(sizeof(Vector));  //定义指针，开辟顺序表的空间
    vec->data = (int *)malloc(sizeof(int) * n); //申请连续存储区空间
    vec->size = n; //初始化
    vec->length = 0;
    return vec;
}

int expand(Vector *vec) {
    int new_size = vec->size * 2;
    int *p = (int *)realloc(vec->data, sizeof(int) * new_size);
    if (p == NULL) return 0;
    vec->size = new_size;
    vec->data = p;
    return 1;
}

int insert(Vector *vec, int ind, int val) {
    if (vec == NULL) return 0;
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("expand vector size to %d success\n", vec->size);
    }
    if (ind < 0 || ind > vec->length) return 0;
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;
    return 1;
}


int erase(Vector *vec, int ind) {
    if (vec == NULL) return 0;
    if (vec->length == 0) return 0;
    if (ind < 0 || ind >= vec->length) return 0;
    for (int i = ind + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void clear(Vector *vec) {
    if (vec == NULL) return ;
    free(vec->data);
    free(vec);
    return ;
}

void output(Vector *vec) {
    printf("Vector(%d) = [", vec->length);
    for (int i = 0; i < vec->length; i++) {
        if (i != 0) printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return ;
}


int main() {
    srand(time(0));
    #define MAX_OP 20
    Vector *vec = init(1);
    int op, ind, val;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 2;
        ind = rand() % (vec->length + 1);
        val = rand() % 100;
        switch (op) {
            case 2:
            case 3:
            case 0: {
                printf("insert %d at %d to vector\n", val, ind);
                insert(vec, ind, val);
            } break;
            case 1: {
                printf("erase item at %d from vector\n", ind);
                erase(vec, ind);
            } break;
        }
        output(vec);
    }

    return 0;
}
