/***********************************************************
*       &Author: Wang Xianling     
*       &E-mail: wang_xianling@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: 3.list.cpp
*       &Created Time:  2020年02月13日 星期四 14时35分03秒  CST  Day/044 and Week/06 of this year
*       &Description:
***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;


typedef struct List {
    ListNode head;
    int length;
} List;


ListNode *getNewNode (int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = val;
    node->next = NULL;
    return node;
}

List *init_list() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(List *l, int ind, int val) {
    if (l == NULL) return -1;
    if (ind < 0 || ind > l->length) return -1;
    int ret = ind;
    ListNode *p = &(l->head), *node = getNewNode(val);
    while (ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return ret;
}

int erase(List *l, int ind) {
    if (l == NULL) return -1;
    if (ind < 0 || ind >= l->length) return -1;
    int ret = ind;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return ret;
}

/*int search(List *l, int val) {
    int ind = 0;
    ListNode *p = l->head.next;
    while (p && p->data != val) p = p->next, ind++;
    if (ind == l->length) return -1;
    return ind;
}
*/

void output_search(List *l, int ind) {
    char str[100];
    int offset = 3;
    ListNode *p = l->head.next;
    while (ind != -1 && p) {
        offset += sprintf(str, "%d->", p->data);
        ind -= 1;
        p = p->next;
    }
    for (int i = 0; i < offset; i++) printf(" ");
    printf("^\n");
    for (int i = 0; i < offset; i++) printf(" ");
    printf("|\n\n");
    return ;
}

void output(List *l) {
    printf ("head->");
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
    return ;
}


void clear_node(ListNode *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clear_list(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_node(p);
        p = q;
    }
    free(l);
    return ;
}

int main() {
    srand(time(0));
    #define MAX_OP 20
    List *l = init_list();
    int op, ind, val, flag;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to List\n", val, ind);
                flag = insert(l, ind, val);
            } break;
            case 3: {
                printf("erase item at %d from List\n", ind);
                flag = erase(l, ind);
            } break;
        }
        output(l);
        output_search(l, flag);
        printf("\n");
    }
    clear_list(l);
    return 0;
}
