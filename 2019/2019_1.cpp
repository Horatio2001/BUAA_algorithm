//
// Created by Horatio on 2023/3/25.
//
#include<cstdio>
#include<algorithm>
#include<iostream>
#include <string>
#include <iostream>
#include<vector>

using namespace std;

bool isPrime(int n) {
    if (n < 2 || n == 4) return false;
    if (n == 2 || n == 3) return true;
    for (int i = 2; i < n / 2; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<int> mask(n+1, 0);
    for (int i = 0; i <= n; i++) {
        if (!isPrime(i)) {
            mask[i] = 1;
        }
    }
    int LIdx, RIdx = 0;
    int max_len = 0;
    int max_start = 0;
    for (int i = 0; i < mask.size(); i++) {
        if (mask[i] == 0) {
            LIdx = i + 1;
        } else {
            RIdx = i;
            if (RIdx - LIdx + 1 > max_len) {
                max_len = RIdx - LIdx + 1;
                max_start = LIdx;
            }
        }
    }
    for (int i = max_start; i < max_start + max_len; i++) {
        cout << i <<endl;
    }
    return 0;
}

/*
 50
 */
