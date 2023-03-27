//
// Created by Horatio on 2023/3/27.
//
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<map>

using namespace std;
struct Node {
    string data;
    vector<string> neighbors;
    vector<string> sons;
} nodes[1005];

map<string, int> mymap;
int visited[1005];
int dist[1005];
vector<string> nodesInPreOrder1;
vector<string> nodesInPreOrder2;

void DFS(string st, int d) {
    dist[mymap[st]] = d;
    for (auto child: nodes[mymap[st]].sons) {
        DFS(child, d + 1);
    }
}

void PreOrder1(string st) {
    int level = dist[mymap[st]];
    queue<string> q;
    q.push(st);
    while (!q.empty()) {
        string top = q.front();
        q.pop();
        visited[mymap[top]] = 1;
        if (dist[mymap[top]] < level) {
            nodesInPreOrder1.push_back(top);
        }
        for (auto child: nodes[mymap[top]].neighbors) {
            if (!visited[mymap[child]]) {
                q.push(child);
            }
        }
    }
}

void PreOrder2(string st) {
    int level = dist[mymap[st]];

    queue<string> q;
    q.push(st);
    while (!q.empty()) {
        string top = q.front();
        q.pop();
        visited[mymap[top]] = 1;
        if (dist[mymap[top]] < level) {
            nodesInPreOrder2.push_back(top);
        }
        for (auto child: nodes[mymap[top]].neighbors) {
            if (!visited[mymap[child]]) {
                q.push(child);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    int nums = 0;
    for (int i = 0; i < n; i++) {
        string fa, c1;
        cin >> fa;
        if (mymap.find(fa) == mymap.end()) {
            mymap[fa] = nums++;
        }
        nodes[mymap[fa]].data = fa;
        for (int j = 0; j < 2; j++) {
            cin >> c1;
            if (mymap.find(c1) == mymap.end()) {
                mymap[c1] = nums++;
            }
            nodes[mymap[c1]].data = c1;
            nodes[mymap[fa]].neighbors.push_back(c1);
            nodes[mymap[fa]].sons.push_back(c1);
            nodes[mymap[c1]].neighbors.push_back(fa);
        }
    }

    string ob1, ob2;
    cin >> ob1 >> ob2;
    DFS(nodes[0].data, 0);
    memset(visited, 0, sizeof visited);
    PreOrder1(ob1);
    memset(visited, 0, sizeof visited);
    PreOrder2(ob2);
//    for (auto a: nodesInPreOrder1) {
//        cout << a << "  " << dist[mymap[a]] << endl;
//    }
//    for (auto b: nodesInPreOrder2) {
//        cout << "      " << b << "   " << dist[mymap[b]] << endl;
//    }
    for (auto a: nodesInPreOrder1) {
        for (auto b: nodesInPreOrder2) {
            if (a == b) {
                cout << a << endl;
                return 0;
            }
        }
    }
}


/*
 Input :
 4
 Ye Shu Ba
 Shu Ge Mei1
 Ba Self Mei2
 Ge Son1 Son2
 Son2 Mei1

 Output:
    Shu 1
 */