//
// Created by Horatio on 2023/3/25.
//
#include<stdio.h>
#include<string>
#include<iostream>

struct result {
    int smallInd;
    int bigInd;
    int len;
} rets[400];

char a[50][50];
int at = 0;
int length = 0;
int cnt(int a1, int a2) {
    int dis = 0;
    for (int i = 0; i < length; i++) {
        if (a[a1][i] != a[a2][i]) {
            dis++;
        }
    }
    return dis;
}
int cmp (const void *a1, const void *a2) {
    struct result aa = *(struct result*) a1;
    struct result bb = *(struct result*) a2;
    if (aa.len < bb.len) {
        return -1;
    } else if (aa.len > bb.len) {
        return 1;
    } else {
        if (aa.smallInd != bb.smallInd){
            return strcmp(a[aa.smallInd], a[bb.smallInd]);
        } else {
            return strcmp(a[aa.bigInd], a[bb.bigInd]);
        }
    }
}

int main() {
    int n;
    std::cin >> n;
//    std::cout << n << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (length < strlen(a[i])) {
            length = (int) strlen(a[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(a[i], a[j]) < 0) {
                rets[at].smallInd = i;
                rets[at].bigInd = j;
            } else {
                rets[at].smallInd = j;
                rets[at].bigInd = i;
            }
            rets[at].len = cnt(i,j);
            at++;
        }
    }
    qsort(rets, at, sizeof(struct result), cmp);
    for (int i = 0; i < at && i < 6; i++) {
        printf("%s %s %d\n", a[rets[i].smallInd], a[rets[i].bigInd], rets[i].len);
//        std::cout << a[rets[i].smallInd] << " " << a[rets[i].bigInd] << " " << rets[i].len << std::endl;
    }
    return 0;
}

/*
7
01010
11011
10101
10011
Roses
roses
cotes
 */