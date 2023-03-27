//
// Created by Horatio on 2023/3/27.
//
#include<iostream>
#include<vector>
using namespace std;



vector<int> getNum(int n) {
    vector<int> nNums;
    for (int i = 1; i <= n / 2; i ++) {
        if (n % i == 0) {
            nNums.push_back(i);
        }
    }
    return nNums;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> nNums;
    vector<int> mNums;
    nNums = getNum(n);
    mNums = getNum(m);
    cout << n << ",";
    int sum = 0;
    int cnt = 0;
    for (auto a : nNums) {
        cnt++;
        cout << a;
        if (cnt != nNums.size()) {
            cout << "+";
        }
        sum += a;
    }
    cout << "=" << sum <<endl;

    cout << m << ",";
    int su = 0;
    cnt = 0;
    for (auto a : mNums) {
        cnt++;
        cout << a;
        if (cnt != mNums.size()) {
            cout << "+";
        }
        su += a;
    }
    cout << "=" << su <<endl;
    if (sum == m && su == n) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}
/*
220 284
 */