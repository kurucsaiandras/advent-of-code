#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <regex>
#include <unordered_map>

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

    std::unordered_map<std::string, std::pair<void*, void*>> map;
    while (std::getline(file, line)) {
        std::regex pattern("\\b([A-Z]{3})\\b");
        std::sregex_iterator iter(line.begin(), line.end(), pattern);
        std::string currentNode = (*iter++)[1].str();
        std::string leftNode = (*iter++)[1].str();
        std::string rightNode = (*iter++)[1].str();
        
        map[currentNode].first = &map[leftNode];
        map[currentNode].second = &map[rightNode];
    }
    
    void* p = &map["AAA"];
    uint64_t steps = 0;
    while (p != &map["ZZZ"]) {
        std::pair<void*, void*>* _p = (std::pair<void*, void*>*)p;
        if (instructions[steps % instructions.size()] == 'L') p = _p->first;
        else if (instructions[steps % instructions.size()] == 'R') p = _p->second;
        steps++;
    }

    std::cout << steps << std::endl;
}