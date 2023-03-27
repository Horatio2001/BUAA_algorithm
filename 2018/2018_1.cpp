//
// Created by Horatio on 2023/3/26.
//
#include<iostream>

using namespace std;
struct line {
    int lxInx;
    int lyInx;
    int rxInx;
    int ryInx;
    int segNum;
} lines[1005];

int cmp(const void *a1, const void *a2) {
    struct line a = *(struct line *) a1;
    struct line b = *(struct line *) a2;
    return a.segNum - b.segNum;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        lines[i].lxInx = a1;
        lines[i].lyInx = a2;
        lines[i].rxInx = b1;
        lines[i].ryInx = b2;
        lines[i].segNum = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((lines[i].lxInx == lines[j].rxInx && lines[i].lyInx == lines[j].ryInx)) {
                //i左端点和j右端点
                lines[i].lxInx = lines[j].lxInx;
                lines[i].lyInx = lines[j].lyInx;
                lines[j].rxInx = lines[i].rxInx;
                lines[j].ryInx = lines[i].ryInx;
                lines[i].segNum += lines[j].segNum;
                lines[j].segNum = lines[i].segNum;
            } else if (lines[i].rxInx == lines[j].lxInx && lines[i].ryInx == lines[j].lyInx) {
                //j左端点和i右端点
                lines[j].lxInx = lines[i].lxInx;
                lines[j].lyInx = lines[i].lyInx;
                lines[i].rxInx = lines[j].rxInx;
                lines[i].ryInx = lines[j].ryInx;
                lines[i].segNum += lines[j].segNum;
                lines[j].segNum = lines[i].segNum;
            }
        }
    }
    qsort(lines, n, sizeof(struct line), cmp);
    cout << lines[0].segNum << " " << lines[0].lxInx << " " << lines[0].lyInx;
    return 0;
}