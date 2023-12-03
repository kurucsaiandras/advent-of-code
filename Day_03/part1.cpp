#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

bool isValidNum(int row, int start, int end, const std::vector<std::string>& lines) {
    if (row != 0) {
        for (int i = std::max(0, start - 1); i < std::min(end + 1, (int)lines[row-1].length()); ++i) {
            if (lines[row - 1][i] != '.') return true;
        }
    }
    if (start != 0) {
        if (lines[row][start - 1] != '.') return true;
    }
    if (end != lines[row].length()) {
        if (lines[row][end] != '.') return true;
    }
    if (row != lines.size() - 1) {
        for (int i = std::max(0, start - 1); i < std::min(end + 1, (int)lines[row+1].length()); ++i) {
            if (lines[row + 1][i] != '.') return true;
        }
    }
    return false;
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
            if (isValidNum(i, start, end, lines)) {
                sum += num;
                std::cout << num << std::endl;
            }
        }
    }

    std::cout << sum << std::endl;
}