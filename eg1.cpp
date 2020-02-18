/***********************************************************
*       &Author: Wang Xianling     
*       &E-mail: wang_xianling@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: eg1.cpp
*       &Created Time:  2020年02月18日 星期二 14时24分18秒  CST  Day/049 and Week/07 of this year
*       &Description:
***********************************************************/


#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100

int calc(const char *str, int l, int r) {
    int prior = 0x3f3f3f3f - 1, temp = 0, pos = -1;     //pos记录优先级最低,temp记录符号优先级,prior初始化优先级
    for (int i = l; i <= r; i++) {
        int cur_prior = 0x3f3f3f3f;
        switch(str[i]) {
            case '(': temp += 100; break;
            case ')': temp -= 100; break;
            case '+':
            case '-': cur_prior = temp + 1; break;
            case '*':
            case '/': cur_prior = temp + 2; break;
            case '^': cur_prior = temp + 3; break;
        }
        if (cur_prior <= prior) {
            prior = cur_prior;
            pos = i;
        }
    }
    if (pos == -1) {
        int num = 0;
        for (int i = l; i <= r; i++) {
            if (str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    }
    int a = calc(str, l, pos - 1);
    int b = calc(str, pos + 1, r);
    switch(str[pos]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return (int)pow(a, b);
    }
    return 0;
    
}

int main() {
    char str[MAX_N + 5] = {0};
    while (scanf("%[^\n]s", str) != EOF) {
        getchar();
        printf("%d\n", calc(str, 0, strlen(str) - 1));
    }
    return 0;
}
