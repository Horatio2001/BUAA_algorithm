//
// Created by Horatio on 2023/3/26.
//
#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<vector<int>> findSeq(vector<int> primes) {
    vector<vector<int>> ans;
    unordered_set<int> se{primes.begin(), primes.end()};
    int n = primes.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int step = primes[j] - primes[i];
            vector<int> seq = {primes[i], primes[j]};
            for (int k = j + 1;; k++) {
                if (se.count(seq.back() + step) == 0) {
                    break;
                }
                seq.push_back(seq.back() + step);
            }
            if (seq.size() > 2) {
                ans.push_back(seq);
            }
        }
    }
    return ans;
}

int main() {
    int a, b;
    vector<int> primes;
    cin >> a >> b;
    for (int i = a; i <= b; i++) {
        if (isPrime(i)) {
//            cout << "  -----"<<i <<endl;
            primes.push_back(i);
        }
    }
    if (primes.size() < 3) return 0;
    vector<vector<int>> ans = findSeq(primes);
    for (auto a: ans) {
        for (auto b : a) {
            cout << b << " ";
        }
        cout << endl;
    }
    return 0;
}