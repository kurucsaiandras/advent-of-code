#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <numeric>

int64_t getPrevVal(const std::vector<int64_t>& v) {
    std::vector<int64_t> diffs;
    for (int i = 0; i < v.size() - 1; ++i) {
        diffs.push_back(v[i + 1] - v[i]);
    }
    if (std::all_of(diffs.begin(), diffs.end(), [](int i) { return i == 0; })) {
        return v[0];
    }
    else {
        return v[0] - getPrevVal(diffs);
    }
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    std::string line;
    int64_t sum = 0;
    std::vector<int64_t> datas(21);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        for (int i = 0; i < 21; ++i) {
            ss >> datas[i];
        }
        int val = getPrevVal(datas);
        sum += val;
    }
    std::cout << sum << std::endl;
}