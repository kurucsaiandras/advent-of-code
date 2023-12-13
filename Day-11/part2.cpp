#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

uint64_t getActualDist(int coord_1, int coord_2, const std::vector<int>& big_nums) {
    int start, end;
    if (coord_1 < coord_2) {
        start = coord_1;
        end = coord_2;
    }
    else {
        start = coord_2;
        end = coord_1;
    }
    int numOfBigs = 0;
    for (int i = 0; i < big_nums.size(); ++i) {
        if (big_nums[i] > start && big_nums[i] < end) numOfBigs++;
    }
    return end - start + numOfBigs * 999999;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    std::vector<std::string> image;
    std::vector<int> big_cols;
    std::vector<int> big_rows;

    std::string line;
    while (std::getline(file, line)) {
        image.push_back(line);
    }

    // find big coloumns
    for (int i = 0; i < image[0].size(); ++i) { // col
        bool hasGalaxy = false;
        for (int j = 0; j < image.size(); ++j) { // row
            if (image[j][i] == '#') { hasGalaxy = true; break; }
        }
        if (!hasGalaxy) big_cols.push_back(i);
    }

    // find big rows
    for (int i = 0; i < image.size(); ++i) {
        bool hasGalaxy = false;
        for (int j = 0; j < image[i].size(); ++j) {
            if (image[i][j] == '#') { hasGalaxy = true; break; }
        }
        if (!hasGalaxy) big_rows.push_back(i);
    }
    
    std::vector<std::pair<int, int>> galaxyCoords;
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[i].size(); ++j) {
            if (image[i][j] == '#') galaxyCoords.push_back({ i, j });
        }
    }

    uint64_t sum = 0;
    for (int i = 0; i < galaxyCoords.size(); ++i) {
        for (int j = i + 1; j < galaxyCoords.size(); ++j) {
            uint64_t vertical, horizontal;
            sum += (getActualDist(galaxyCoords[i].first, galaxyCoords[j].first, big_rows) + getActualDist(galaxyCoords[i].second, galaxyCoords[j].second, big_cols));
        }
    }

    std::cout << sum << std::endl;
}