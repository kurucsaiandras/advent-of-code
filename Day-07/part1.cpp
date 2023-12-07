#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

std::array<std::vector<int>, 7> handIdxs;
std::vector<std::string> hands;
std::vector<int> bids;

int map(char c) {
    if ('2' <= c && c <= '9') {
        return c - 50;
    }
    switch (c) {
    case 'T': return 8;
    case 'J': return 9;
    case 'Q': return 10;
    case 'K': return 11;
    case 'A': return 12;
    }
}

bool isRightBigger(std::string l, std::string r) {
    for (int i = 0; i < 5; ++i) {
        if (map(l[i]) < map(r[i])) return true;
        else if (map(l[i]) > map(r[i])) return false;
        else continue;
    }
    return false;
}

void insert(int idx, int type) {
    for (int i = 0; i < handIdxs[type].size(); ++i) {
        if (!isRightBigger(hands[handIdxs[type][i]], hands[idx])) {
            handIdxs[type].insert(handIdxs[type].begin() + i, idx);
            return;
        }
    }
    handIdxs[type].push_back(idx);
}

int classify(std::string hand) {
    std::array<int, 13> numOfCards{ 0 };
    for (int i = 0; i < 5; ++i)
        numOfCards[map(hand[i])]++;
    std::array<int, 6> numOfNums{ 0 };
    for (int i = 0; i < 13; ++i)
        numOfNums[numOfCards[i]]++;

    if (numOfNums[1] == 5) return 0;
    if (numOfNums[1] == 3 && numOfNums[2] == 1) return 1;
    if (numOfNums[1] == 1 && numOfNums[2] == 2) return 2;
    if (numOfNums[1] == 2 && numOfNums[3] == 1) return 3;
    if (numOfNums[2] == 1 && numOfNums[3] == 1) return 4;
    if (numOfNums[1] == 1 && numOfNums[4] == 1) return 5;
    if (numOfNums[5] == 1) return 6;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string hand;
        int bid;
        ss >> hand >> bid;
        hands.push_back(hand);
        bids.push_back(bid);
    }

    for (int i = 0; i < hands.size(); ++i) 
        insert(i, classify(hands[i]));

    int rank = 1;
    uint64_t res = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < handIdxs[i].size(); ++j) {
            res += rank * bids[handIdxs[i][j]];
            rank++;
        }
    }

    std::cout << res << std::endl;
}