//
// Created by Horatio on 2023/3/26.
// 某单位信息网络结构呈树形结构，网络中结点可以为交换机，计算机，打印机三种设备，
// 计算机和打印机只能位于树的叶结点上，若要从一台计算机上打印文档，
// 请为它选择最近的打印机（经过交换机最少）。在该网络结构中，根交换机的编号为0，
// 其他设备编号为任意有效正整数，每个交换机有8个端口（编号0-7），
// 当存在多个满足条件的打印机时，选择按树前序遍历序排在前面的打印机。
// 原文链接：https://blog.csdn.net/qingqiqiuwhy/article/details/104771253
//输入：
//当前网络中设备数m
//<设备ID><设备类型><设备父节点ID><端口号>（类型：0表示交换机，1表示计算机，2表示打印机）
//输出：
//最近打印机的ID
//
#include<iostream>
#include<vector>
#include<map>
#include<cstdio>
#include<stack>
#include<limits>
#include<queue>

using namespace std;
#define inf numeric_limits<int>::max()
const int MAXN = 1005;
struct Node {
    int order = -1;
    int data;
    int type;
    int port;
    int father = -1;
    int sons[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    vector<int> neibor;
} Nodes[10005];
vector<int> typerInPreOrder;
map<int, int> mymap;

int dist[MAXN];
bool visited[MAXN];


void preOrder() {
    stack<int> sstack;
    sstack.push(0);
    int num = 0;
    while (!sstack.empty()) {
        int top = sstack.top();
        sstack.pop();
        if (Nodes[mymap[top]].type == 2) {
            Nodes[mymap[top]].order = num++;
        }
        for (int i = 7; i >= 0; i--) {
            if (Nodes[mymap[top]].sons[i] != -1) {
                sstack.push(Nodes[mymap[top]].sons[i]);
            }
        }
    }
}

void DFS(int st, int d) {
    visited[mymap[st]] = true;
    dist[mymap[st]] = d;
    for (auto a: Nodes[mymap[st]].neibor) {
        if (!visited[mymap[a]]) {
            DFS(a, d + 1);
        } else if (dist[mymap[a]] != -1) {
            dist[mymap[st]] = min(dist[mymap[st]], dist[mymap[a]] + 1);
        }
    }
}

int main() {
    int m;
    cin >> m;
    int nums = 1;
    int typerCnt = 0;
    int computerCnt = 0;
    Nodes[0].data = 0;
    mymap[0] = 0;
    int id, type, fatherId, port;
    for (int i = 0; i < m; i++) {
        cin >> id >> type >> fatherId >> port;
        if (mymap.find(id) == mymap.end()) {
            mymap[id] = nums++;
        }
        Nodes[mymap[fatherId]].sons[port] = id;
        Nodes[mymap[fatherId]].neibor.push_back(id);
        Nodes[mymap[id]].father = fatherId;
        Nodes[mymap[id]].neibor.push_back(fatherId);
        Nodes[mymap[id]].data = id;
        Nodes[mymap[id]].type = type;
        Nodes[mymap[id]].port = port;
        if (type == 2) {
            typerCnt++;
        } else if (type == 1) {
            computerCnt++;
        }
    }
    preOrder();
    memset(visited, false, sizeof visited);
    memset(dist, -1, sizeof dist);
    int computerPost;
    cin >> computerPost;
    DFS(computerPost, 0);
    int mindis = inf;
    int mindistyper = 0;
    for (int i = 0; i < m + 1; i++) {
        if (Nodes[i].type == 2) {
            if (mindis > dist[i]) {
                mindis = dist[i];
                mindistyper = Nodes[i].data;
            } else if (mindis == dist[i]) {
                if (Nodes[i].order < Nodes[mymap[mindistyper]].order) {
                    mindistyper = Nodes[i].data;
                }
            }
        }
    }
    cout << mindistyper << endl;
    return 0;
}
/*
15
1 0 0 0
4 0 0 1
8 0 0 2
2 0 1 0
3 1 1 1
5 1 4 0
7 0 4 1
29 1 4 2
16 0 8 0
9 0 2 0
6 1 2 1
13 0 7 0
15 2 7 1
17 2 16 0
28 1 16 1
*/