//
// Created by Horatio on 2023/3/27.
//
#include<iostream>
#include<vector>

using namespace std;

int winNums = 0;
struct Window {
    int lx, ly, rx, ry;
    int id;
    int level;
    int num;
} wins[10005];

struct Click {
    int lx, ly;
} clicks[10005];

void levelChange(int id) {
    int level = wins[id].level;
    for (int i = 0; i < winNums; i++) {
        if (wins[i].level < level) {
            continue;
        }
        if (id == i) {
            wins[id].level = 0;
            continue;
        }
        wins[i].level--;
    }
}

void dealClick(Click c) {
    vector<int> tmp;
    for (int i = 0; i < winNums; ++i) {
        if (c.lx > wins[i].lx && c.ly > wins[i].ly
            && c.lx < wins[i].rx && c.ly < wins[i].ry) {
            tmp.push_back(wins[i].num);
        }
    }
    int minlevel = 10000;
    int idx;
    for (auto a : tmp) {
        if (wins[a].level < minlevel) {
            minlevel = wins[a].level;
            idx = a;
        }
    }
    levelChange(idx);
}

int cmp(const void *a1, const void *b1) {
    struct Window a = *(struct Window *)a1;
    struct Window b = *(struct Window *)b1;
    return b.level - a.level;
}

int main() {
    int n;
    int level = 0, num = 0;
    cin >> n;
    winNums = n;
    for (int i = 0; i < n; i++) {
        int data, lx, ly, rx, ry;
        cin >> data >> lx >> ly >> rx >> ry;
        wins[i].id = data;
        wins[i].lx = lx;
        wins[i].ly = ly;
        wins[i].rx = rx;
        wins[i].ry = ry;
        wins[i].level = level++;
        wins[i].num = num++;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int lx, ly;
        cin >> lx >> ly;
        clicks[i].lx = lx;
        clicks[i].ly = ly;
    }

    for (auto a: clicks) {
        dealClick(a);
    }
    qsort(wins, winNums, sizeof(struct Window), cmp);
    for (int i = 0; i < winNums; i++) {
        cout << wins[i].id << endl;
    }
}
/*
2
1 1 5 5 1
2 3 5 7 1
3
1 2
4 3
6 4
 */