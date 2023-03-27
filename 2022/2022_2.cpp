//
// Created by Horatio on 2023/3/25.
//
#include<iostream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include <unordered_map>

char input[500];
char waiting[50];
double stack[10000];
int topStack = 0;
int charAt = 0;
std::unordered_map<char, double> myMap;
int waitTop = 0;

void A();

void B();

void expr();

void B() {
    if (input[charAt] == '(') {
        charAt++;
        expr();
        charAt++;
    } else if (input[charAt] >= 'a' && input[charAt] <= 'z') {
        stack[topStack] = myMap.at(input[charAt]);
        topStack++;
        charAt++;
    } else if (input[charAt] >= '0' && input[charAt] <= '9') {
        char c[100];
        int i;
        for (i = 0; input[charAt] >= '0' && input[charAt] <= '9'; i++, charAt++) {
            c[i] = input[charAt];
        }
        c[i] = '\0';
        stack[topStack] = (double) atoi(c);
        topStack++;
    }
}

void A() {
    B();
    while (true) {
        if (!(input[charAt] == '*' || input[charAt] == '/' || input[charAt]=='+' || input[charAt]=='-')) {
            return;
        }
        char c = input[charAt];
        charAt++;
        B();
        if (c == '*') {
            stack[topStack - 2] = stack[topStack - 2] * stack[topStack - 1];
            stack[topStack - 1] = 0;
            topStack--;
        } else if (c== '/'){
            stack[topStack - 2] = stack[topStack - 2] / stack[topStack - 1];
            stack[topStack - 1] = 0;
            topStack--;
        }
    }
}

void expr() {
    A();
    while(true) {
        if (!(input[charAt]=='+' || input[charAt]=='-')) {
            return;
        }
        char c = input[charAt];
        charAt++;
        A();
        if (c == '+') {
            stack[topStack - 2] = stack[topStack - 2] + stack[topStack - 1];
            stack[topStack - 1] = 0;
            topStack--;
        } else if(c == '-'){
            stack[topStack - 2] = stack[topStack - 2] - stack[topStack - 1];
            stack[topStack - 1] = 0;
            topStack--;
        }
    }
}

int main() {

    while (true) {
        scanf("%s", input);
        if (strcmp(input, "Exit") == 0) {
            return 0;
        } else if (strcmp(input, "read") == 0) {
            while (true) {
                scanf("%c", &input[0]);
                if ('a' <= input[0] && input[0] <= 'z') {
                    waiting[waitTop++] = input[0];
                } else if (input[0] == '\n') {
                    break;
                }
            }
            for (int i = 0; i < waitTop; i++) {
                scanf("%s", input);
                double v = (double) atoi(input);
                myMap[waiting[i]] = v;
                waiting[i] = 0;
            }
            waitTop = 0;
        } else if (strcmp(input, "print") == 0) {
            while (true) {
                scanf("%c", &input[0]);
                if ('a' <= input[0] && input[0] <= 'z') {
                    waiting[waitTop++] = input[0];
                } else if (input[0] == '\n') {
                    break;
                }
            }
            for (int i = 0; i < waitTop; i++) {
                printf("%.2lf", myMap.at(waiting[i]));
                if (i + 1 != waitTop) {
                    printf(" ");
                } else {
                    printf("\n");
                }
                waiting[i] = 0;
            }
            waitTop = 0;
        } else {
            char tmp = input[0];
            charAt = 2;
            expr();
            myMap[tmp] = stack[--topStack];
            stack[topStack] = 0;
        }
    }
}

/*
read a
10
b=20
c=(a+b)/3
print a b c
//10.00 20.00 10.00
Exit
 */