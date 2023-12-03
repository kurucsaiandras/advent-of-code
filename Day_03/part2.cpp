#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <unordered_map>

std::unordered_map<int, std::vector<int>> gears;

void saveToGears(int num, int row, int start, int end, const std::vector<std::string>& lines) {
    if (row != 0) {
        for (int i = std::max(0, start - 1); i < std::min(end + 1, (int)lines[row-1].length()); ++i) {
            if (lines[row - 1][i] == '*') gears[(row - 1) * lines[row - 1].length() + i].push_back(num);
        }
    }
    if (start != 0) {
        if (lines[row][start - 1] == '*') gears[(row) * lines[row].length() + start - 1].push_back(num);
    }
    if (end != lines[row].length()) {
        if (lines[row][end] == '*') gears[(row) * lines[row].length() + end].push_back(num);
    }
    if (row != lines.size() - 1) {
        for (int i = std::max(0, start - 1); i < std::min(end + 1, (int)lines[row+1].length()); ++i) {
            if (lines[row + 1][i] == '*') gears[(row + 1) * lines[row + 1].length() + i].push_back(num);
        }
    }
}

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }
    std::vector<std::string> lines;
    int sum = 0;
       
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    std::regex nums("[0-9]+");
    for (int i = 0; i < lines.size(); ++i) {
        std::smatch m;
        std::string substr = lines[i];
        int end = 0;
        while (std::regex_search(substr, m, nums)) {
            int num = stoi(m.str());
            substr = m.suffix();
            int start = m.position() + end;
            end = m.length() + start;
            saveToGears(num, i, start, end, lines);
        }
    }
    for (const auto& g : gears) {
        if (g.second.size() == 2) {
            sum += g.second[0] * g.second[1];
        }
    }

    std::cout << sum << std::endl;
}