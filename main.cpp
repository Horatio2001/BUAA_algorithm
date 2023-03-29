#include<fstream>
#include<iostream>
#include<queue>
#include<vector>
#include<stack>

using namespace std;


int main() {
    queue<int> a;
    stack<int> b;
    vector<int> c;
    a.push(1);
    b.push(2);
    c.push_back(3);


    cout << a.front() << endl;
    a.pop();

    cout << b.top() << endl;
    b.pop();

    cout << c.front() << endl;
    c.pop_back();

    cout << a.size()<<endl;
    cout << b.size()<<endl;
    cout << c.size()<<endl;

}