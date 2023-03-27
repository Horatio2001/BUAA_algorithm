//
// Created by Horatio on 2023/3/27.
//
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

vector<int> calculate(int n) {
    int tmp = n;
    vector<int> ans;
    while (tmp > 0) {
        ans.push_back(tmp % 10);
        tmp /= 10;
    }
    return ans;
}

int cal(int n) {
    int tmp = n;
    int ans = 0;
    while (tmp > 0) {
        ans *= 10;
        ans += tmp % 10;
        tmp /= 10;
    }
    return ans;
}


int main() {
    int n;
    vector<int> ans;
    cin >> n;
    ans = calculate(n);
    if (n % 10 == 0) {
        cout << n << " ";
        for (int an : ans) {
            cout << an;
        }
        cout << endl;
        return 0;
    }
    int m = cal(n);
    if (m % n == 0) {
        cout << n << "*" << m / n << "=" << m << endl;
        return 0;
    }
    cout << n << " ";
    for (int an : ans) {
        cout << an;
    }
    cout << endl;
    return 0;

}