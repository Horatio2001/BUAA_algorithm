//
// Created by Horatio on 2023/3/26.
//
#include<iostream>
#include<map>
#include<set>
#include<cstring>

using namespace std;

int point = 0;
set<string> myset;
char curToken[1005];
char sentence1[1005];
char sentence2[1005];
bool intFlag = false;
bool charFlag = false;

void resetToken() {
    memset(curToken, '\0', sizeof curToken);
}

void readType() {
    int at = 0;
    while (isalpha(sentence1[point])) {
        curToken[at] = sentence1[point];
        point++;
        at++;
    }
    if (strcmp(curToken, "int") == 0) {
        intFlag = true;
    } else if (strcmp(curToken, "char") == 0) {
        charFlag = true;
    } else {
        cout << "undefined type!" << endl;
    }
    resetToken();
}

void readBlank() {
    while (isblank(sentence1[point])) {
        point++;
    }
}

void readBlank2() {
    while (isblank(sentence2[point])) {
        point++;
    }
}

void dealWithArray() {
    while (true) {
        point++;
        if (sentence1[point] == ']') {
            break;
        }
    }
    point++;
}

/*
 * int x, x12, y = 1, a[30], *p;
 */
void readDefine() {
    int at = 0;
    while ((isalpha(sentence1[point]) || isnumber(sentence1[point]) || sentence1[point] == '*' || sentence1[point]=='_')
           && (sentence1[point] != '=' && sentence1[point] != '[' && !isblank(sentence1[point]))) {
        curToken[at] = sentence1[point];
        at++;
        point++;
    }
    if (curToken[0] == '*') {
        char name[1005];
        int i = 1;
        for (; curToken[i] != '\0'; i++) {
            name[i - 1] = curToken[i];
        }
        name[i - 1] = '\0';
        string tmp = name;
        myset.insert(tmp);
    } else {
        string tmp = curToken;
        myset.insert(tmp);
    }

    resetToken();
    readBlank();
    if (sentence1[point] == '=') {
        point++;
        readBlank();
        while (isnumber(sentence1[point])) {
            point++;
        }
    } else if (sentence1[point] == '[') {
        dealWithArray();
        while (sentence1[point] == '[') {
            dealWithArray();
        }
    }
    readBlank();
    while (sentence1[point] == ',') {
        point++;
        readBlank();
        readDefine();
    }
}

void parser1() {
    readType();
    readBlank();
    readDefine();
    if (sentence1[point] != ';') {
        cout << "s1 wrong  " << sentence1[point] << endl;
    }
}

void readVar() {
    int at = 0;
    while ((isalpha(sentence2[point]) || isnumber(sentence2[point]))) {
        curToken[at] = sentence2[point];
        at++;
        point++;
    }
    string tmp = curToken;
    if (myset.find(tmp) == myset.end()) {
        cout << tmp << endl;
    }
    resetToken();
}

void parser2() {
    readVar();
    readBlank2();
    while (sentence2[point] == '=' || sentence2[point] == '+'
           || sentence2[point] == '-' || sentence2[point] == '*'
           || sentence2[point] == '/' || sentence2[point] == '%') {
        point++;
        readBlank2();
        readVar();
        readBlank2();
    }
    if (sentence2[point] != ';') {
        cout << "something wrong with s2   " << sentence2[point] << endl;
    }
}

int main() {
    cin.getline(sentence1, 1005);
    cin.getline(sentence2, 1005);
    parser1();
    point = 0;
    parser2();
    return 0;
}
/*
int x12, y=1, num_stu=89, a[30], *p;
Sum = num + x12*y;
 */