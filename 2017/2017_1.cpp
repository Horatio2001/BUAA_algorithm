//
// Created by Horatio on 2023/3/26.
//
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct ans {
    int idx;
    int num;
} an[1005];

int cmp(const void *a1, const void *b1) {
    struct ans a = *(struct ans *) a1;
    struct ans b = *(struct ans *) b1;
    return a.num - b.num;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        an[i].idx = i + 1;
        an[i].num = tmp;
    }
    qsort(an, n, sizeof(struct ans), cmp);
    if (n % 2 == 1) {
        int idx = n / 2;
        cout << an[idx].num << " " << an[idx].idx << endl;
    } else {
        int idx1 = n / 2 - 1;
        int idx2 = n / 2;
        cout << an[idx1].num << " " << an[idx1].idx << endl;
        cout << an[idx2].num << " " << an[idx2].idx << endl;
    }
}
