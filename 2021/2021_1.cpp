//
// Created by Horatio on 2023/3/25.
//
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unordered_map>
#include<limits>

struct Block {
    int position;
    int length;
    int nextPosition;
    int prePosition;
} blocks[1000];
std::unordered_map<int, struct Block> mymap;
int request[1000];
bool noBlockFlag = false;
int idx;
int blocknum = 0;

void dealRequest(int request) {
    int tmpidx = idx;
    for (int i = 0; i < blocknum; i++) {
        Block curblock = mymap.at(tmpidx);
        if (curblock.length == request) {
            if (blocknum > 1) {
                mymap[curblock.prePosition].nextPosition = curblock.nextPosition;
                mymap[curblock.nextPosition].prePosition = curblock.prePosition;
                idx = curblock.nextPosition;
            } else {
                noBlockFlag = true;
            }
            blocknum--;
            return;
        } else {
            tmpidx = curblock.nextPosition;
        }
    }

    tmpidx = idx;
    bool findBlock = false;
    int blockMark = idx;
    int blockMinLen = std::numeric_limits<int>::max();
    for (int i = 0; i < blocknum; i++) {
        Block curblock = mymap.at(tmpidx);
        if (curblock.length > request && blockMinLen > curblock.length) {
            blockMinLen = curblock.length;
            blockMark = curblock.position;
            findBlock = true;
        }
        tmpidx = curblock.nextPosition;
    }
    if (findBlock) {
        mymap[blockMark].length -= request;
        idx = blockMark;
//        std::cout << "     " << blockMark << " " << mymap[blockMark].length << std::endl;
        return;
    }
}

int main() {
    std::cin >> blocknum;
    std::cin >> blocks[0].position >> blocks[0].length;
    if (blocknum == 1) {
        mymap[blocks[0].position] = blocks[0];
    }
    idx = blocks[0].position;
    int i = 1;
    for (; i < blocknum; i++) {
        std::cin >> blocks[i].position >> blocks[i].length;
        blocks[i - 1].nextPosition = blocks[i].position;
        blocks[i].prePosition = blocks[i - 1].position;
        mymap[blocks[i - 1].position] = blocks[i - 1];
    }
    if (blocknum > 1) {
        blocks[i - 1].nextPosition = blocks[0].position;
        blocks[0].prePosition = blocks[i - 1].position;
        mymap[blocks[i - 1].position] = blocks[i - 1];
    }
    int requestNum = 0;
//    std::cout << "tst";
    for (;; requestNum++) {
        std::cin >> request[requestNum];
        if (request[requestNum] == -1) {
            break;
        }
    }
    for (int j = 0; j < requestNum ; j++) {
        int curReq = request[j];
        dealRequest(curReq);
    }

    for (int j = 0; j < blocknum; j++) {
        std::cout << mymap.at(idx).position << " " << mymap.at(idx).length << std::endl;
        idx = mymap.at(idx).nextPosition;
    }
    return 0;
}
/*
12
1024 2048
8192 512
16384 1024
32768 8192
65536 8192
77824 1024
80896 3072
86016 1024
91136 5120
99328 512
104448 1024
112640 3072
1024 2560 10240 512 1024 6400 512 -1
 *
 */