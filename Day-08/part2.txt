#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <numeric>

uint64_t lcm(std::vector<int> nums) {
    uint64_t lcm = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        lcm = std::lcm(lcm, nums[i]);
    }
    return lcm;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    std::string instructions;
    std::getline(file, instructions);

    std::string line;
    std::getline(file, line); // skip empty line

    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    std::vector<std::string> paths;
    while (std::getline(file, line)) {
        std::regex pattern("\\b([A-Z]{3})\\b");
        std::sregex_iterator iter(line.begin(), line.end(), pattern);
        std::string currentNode = (*iter++)[1].str();
        std::string leftNode = (*iter++)[1].str();
        std::string rightNode = (*iter++)[1].str();
        
        map[currentNode].first = leftNode;
        map[currentNode].second = rightNode;

        if (currentNode[2] == 'A') paths.push_back(currentNode);
    }
    
    std::vector<int> cycles;
    
    for (int i = 0; i < paths.size(); ++i) {
        std::string p = paths[i];
        uint64_t steps = 0;
        while (p[2] != 'Z') {
            if (instructions[steps % instructions.size()] == 'L') p = map[p].first;
            else if (instructions[steps % instructions.size()] == 'R') p = map[p].second;
            steps++;
        }
        cycles.push_back(steps / instructions.size());
        if (steps % instructions.size()) std::cout << "ERROR" << std::endl;
    }
    
    uint64_t allSteps = lcm(cycles) * instructions.size();
    std::cout << allSteps << std::endl;
}