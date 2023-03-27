//
// Created by Horatio on 2023/3/25.
//
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<map>
#include<queue>
#include<vector>

using namespace std;

const int maxn = 10000;

struct Node {
    int data;
    vector<int> adj;
} Nodes[maxn];

struct dengJiKou {
    int data;
    int weight;
} DJK[maxn];

vector<int> typerInPreOrder;

map<int, int> mymap;

int cmp(const void *a1, const void *b1) {
    struct dengJiKou a = *(struct dengJiKou*)a1;
    struct dengJiKou b = *(struct dengJiKou*)b1;
    if (a.weight != b.weight) {
        return b.weight - a.weight;
    } else {
        return a.data - b.data;
    }

}

void BFS() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (Nodes[now].data < 100) {
            typerInPreOrder.push_back(Nodes[now].data);
        }
        for (int i = 0; i < Nodes[now].adj.size(); i++) {
            int temp = Nodes[now].adj[i];
            q.push(temp);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    mymap[100] = 0;
    Nodes[0].data = 100;
    int num = 1;
    int leafNum = 0;
    int father, child;
    for (int i = 0; i < n; i++) {
        scanf("%d", &father);
        for (int i = 0; i < 3; i++) {
            scanf("%d", &child);
            if (child != -1) {
                if (mymap.find(child) == mymap.end()) {
                    mymap[child] = num++;//??????????num
//                    cout <<"--------"<< child << "  "<<num - 1<<endl;
                }
                Nodes[mymap[child]].data = child;
                Nodes[mymap[father]].adj.push_back(mymap[child]);
                if (child < 100) {
                    leafNum++;
                }
            }
        }
    }
    BFS();
    for (int i = 0; i < leafNum; i++) {
        scanf("%d%d", &DJK[i].data, &DJK[i].weight);
    }
//    sort(DJK, DJK + leafNum, cmp);
    qsort(DJK, leafNum, sizeof(struct dengJiKou), cmp);
    for (int i = 0; i < leafNum; i++) {
        int temp = DJK[i].data;
        printf("%d %d\n", temp, typerInPreOrder[i]);
    }
    return 0;
}
/*
12
100 101 102 103
103 14 108 13
101 5 104 6
104 7 8 -1
102 105 106 107
106 1 110 2
108 16 15 -1
107 18 111 17
110 3 4 -1
105 9 109 10
111 20 19 -1
109 11 12 -1
17 865
5 668
20 3000
13 1020
11 980
8 2202
15 1897
6 1001
14 922
7 2178
19 2189
1 1267
12 3281
2 980
18 1020
10 980
3 1876
9 1197
16 980
4 576
 */
