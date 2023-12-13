#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>



int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    std::vector<std::string> image;
    std::vector<std::string> image_exp_col(140);
    std::vector<std::string> image_exp;

    std::string line;
    while (std::getline(file, line)) {
        image.push_back(line);
    }

    // expand coloumns
    for (int i = 0; i < image[0].size(); ++i) { // col
        bool hasGalaxy = false;
        for (int j = 0; j < image.size(); ++j) { // row
            image_exp_col[j].push_back(image[j][i]);
            if (image[j][i] == '#') hasGalaxy = true;
        }
        if (!hasGalaxy) {
            for (int j = 0; j < image.size(); ++j) { // row
                image_exp_col[j].push_back(image[j][i]);
            }
        }
    }

    // expand rows
    for (int i = 0; i < image_exp_col.size(); ++i) {
        bool hasGalaxy = false;
        image_exp.push_back(image_exp_col[i]);
        for (int j = 0; j < image_exp_col[i].size(); ++j) {
            if (image_exp_col[i][j] == '#') { hasGalaxy = true; break; }
        }
        if (!hasGalaxy) image_exp.push_back(image_exp_col[i]);
    }
    
    std::vector<std::pair<int, int>> galaxyCoords;
    for (int i = 0; i < image_exp.size(); ++i) {
        for (int j = 0; j < image_exp[i].size(); ++j) {
            if (image_exp[i][j] == '#') galaxyCoords.push_back({ i, j });
        }
    }

    uint64_t sum = 0;
    for (int i = 0; i < galaxyCoords.size(); ++i) {
        for (int j = i + 1; j < galaxyCoords.size(); ++j) {
            sum += (std::abs(galaxyCoords[i].first - galaxyCoords[j].first) + std::abs(galaxyCoords[i].second - galaxyCoords[j].second));
        }
    }

    std::cout << sum << std::endl;
}