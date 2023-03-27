//
// Created by Horatio on 2023/3/27.
//
#include<iostream>
#include<cstring>
#include<set>
#include<algorithm>
#include<list>

using namespace std;

char input[1005];
int point = 0;
char curToken[1005];
char curValue[1005];
int lastValue = -1;
list<string> ans;


void readBlank() {
    while (isblank(input[point])) {
        point++;
    }
}

void resetGlobal() {
    memset(curToken, '\0', sizeof curToken);
    memset(curValue, '\0', sizeof curValue);
}

void readVar() {
    int at = 0;
    while (isalpha(input[point])) {
        curToken[at] = input[point];
        at++;
        point++;
    }
    readBlank();
    if (input[point] == '=') {
        point++;
        int sp = 0;
        readBlank();
        while (!isblank(input[point]) && input[point] != ',' && input[point] != '}') {
            curValue[sp] = input[point];
            point++;
            sp++;
        }
        string a = curToken;
        string b = curValue;
        string an = a + b;
        ans.push_back(an);
        lastValue = stoi(curValue);
    } else if (input[point] == ',' || input[point] == '}') {
        string a = curToken;
        string b = to_string(++lastValue);
        string an = a + b;
        ans.push_back(an);
    }
    resetGlobal();
}

int main() {
    cin.getline(input, 1005);
    while (input[point] != '{') {
        point++;
    }
    point++;
    readBlank();
    readVar();
    readBlank();
    while (input[point] == ',') {
        point++;
        readBlank();
        readVar();
        readBlank();
    }

    for (auto a : ans) {
        cout << a << endl;
    }
}
/*
enumBOOL{true, false}
enumData{JAN=1,FEB,MAR,APR,MAY,JUN,JULY,AUG,SEP,OCT,NOV,DEC,MON=1,TUE,WED,THU,FRI,SAT,SUN,found=1949};
 */