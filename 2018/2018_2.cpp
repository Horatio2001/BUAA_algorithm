//
// Created by Horatio on 2023/3/26.
//
#include<iostream>
#include<map>
#include<vector>
#include<queue>

using namespace std;
map<int, int> mymap;
vector<int> nodesInPre;
struct node {
    int id;
    vector<int> sons;
    vector<int> neighbors;
} Nodes[1005];

int cmp(const void *a1, const void *b1) {
    struct node a = *(struct node *) a1;
    struct node b = *(struct node *) b1;
    return a.neighbors.size() - b.neighbors.size();
}

void preOrder() {
    queue<int> q;
    q.push(Nodes[0].id);
    while (!q.empty()) {
        int top = q.front();
        q.pop();
        nodesInPre.push_back(top);
        for (auto child: Nodes[mymap[top]].sons) {
            q.push(child);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int nums = 0;
    for (int i = 0; i < n; i++) {
        int father, child;
        cin >> father;
        if (mymap.find(father) == mymap.end()) {
            mymap[father] = nums++;
        }
        Nodes[mymap[father]].id = father;
        for (int j = 0; j < 3; j++) {
            cin >> child;
            if (child != -1) {
                if (mymap.find(child) == mymap.end()) {
                    mymap[child] = nums++;
                    Nodes[mymap[child]].id = child;
                }
                Nodes[mymap[father]].sons.push_back(child);
                Nodes[mymap[father]].neighbors.push_back(child);
                Nodes[mymap[child]].neighbors.push_back(father);
            }
        }
    }
    qsort(Nodes, nums, sizeof(struct node), cmp);
    preOrder();
    vector<int> an;
    an.push_back(Nodes[0].id);
    int ans = Nodes[0].neighbors.size();
    int i = 0;
    for (;; i++) {
        if (Nodes[i].neighbors.size() != ans) break;
        an.push_back(Nodes[i].id);
    }
    if (an.size() == 1) {
        cout << an.back() << endl;
    } else {
        for (int j = 0; j < nums; j++) {
            for (int k : an) {
                if (nodesInPre[j] == k) {
                    cout << k <<endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}