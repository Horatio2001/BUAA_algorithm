//
// Created by Horatio on 2023/3/26.
//题目描述：（看的网上学弟的题目描述，很全）一个关于三叉树的题目，
// 小于100的值代表树叶，大于100的值为分支点，建树的过程是水平方向建树，输入格式：
// 先输入n，代表有n组数据，接下来n行，输入4个数，第一个数代表根节点，
// 接下来分别代表三个子节点，-1代表子节点不存在，
// 输入的顺序按照层次遍历的次序。接下来，要求寻找叶子节点的最短路径，最短路径是指不经过重复的边。
// 输入方式，首先输入一个值m，代表m行，接下来m行输入m个叶子节点和对应的优先级，
// 要求按优先级输出从上次到达的位置到该节点的最短路径，每条路径的最后一个节点要求输出目标叶子节点，最后要求回到根节点。
#include<vector>
#include<iostream>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
#define inf numeric_limits<int>::max()
const int MAXN = 1005;
struct Node {
    int data;
    vector<int> neighbor;
} Nodes[1005];

struct Post {
    int data;
    int order = -1;
} posts[1005];

map<int, int> mymap;

int cmp(const void *a1, const void *b1) {
    struct Post a = *(struct Post *) a1;
    struct Post b = *(struct Post *) b1;
    return a.order - b.order;
}

int nodeNums = 0;
int dist[MAXN];

int pred[MAXN];



int visited[MAXN];
void DFS() {
    for (int i = 0; i < nodeNums; i++) {
        int minDist = inf;
        int cur = 0;
        for (int j = 0; j < nodeNums; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                cur = Nodes[j].data;
            }
        }
        for (auto child : Nodes[mymap[cur]].neighbor) {
            if (dist[mymap[cur]] + 1 < dist[mymap[child]]) {
                dist[mymap[child]] = dist[mymap[cur]] + 1;
                pred[mymap[child]] = cur;
            }
        }
        visited[mymap[cur]] = true;
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
            Nodes[mymap[father]].data = father;
        }
        for (int j = 0; j < 3; j++) {
            cin >> child;
            if (child != -1) {
                if (mymap.find(child) == mymap.end()) {
                    mymap[child] = nums++;
                    Nodes[mymap[child]].data = child;
                }
                Nodes[mymap[father]].neighbor.push_back(child);
                Nodes[mymap[child]].neighbor.push_back(father);
            }
        }
    }
    nodeNums = nums;
//    cout <<nodeNums<<endl;
//    for (int i = 0; i < nums; i++) {
//        cout << Nodes[i].data << endl;
//    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int data, order;
        cin >> data >> order;
        posts[i].data = data;
        posts[i].order = order;
    }
    qsort(posts, m, sizeof(struct Post), cmp);

    Node preNode = Nodes[mymap[100]];

    for (int i = 0; i < m; i++) {
        memset(dist, 1, sizeof dist);
        memset(visited, 0, sizeof visited);
        for (int j = 0; j < nodeNums; j++) {
            cout << dist[j] <<"----" << visited[j]<< endl;
        }
        memset(pred, -1, sizeof pred);
        Node target = Nodes[mymap[posts[i].data]];
        dist[mymap[preNode.data]] = 0;
        DFS();

//        vector<int> ans;
//        int tmp = target.data;
//        cout << tmp << " ";
//        while(pred[mymap[tmp]] != -1) {
//            cout << pred[mymap[tmp]] << " ";
//            tmp = pred[mymap[tmp]];
//        }
//        cout << endl;
//        preNode = target;
    }

    return 0;
}



//样例：
/*
10
100 101 108 107
101 1 102 2
108 103 104 105
107 17 109 18
102 3 4 5
103 7 8 9
104 10 106 11
105 15 16 -1
109 19 20 21
106 12 13 14
5
8 1
14 3
16 2
5 0
19 4
*/
//
//answer:
//
//100 101 102 5
//102 101 100 108 103 8
//103 108 105 16
//105 108 104 106 14
//106 104 108 100 107 109 19
//109 107 100


