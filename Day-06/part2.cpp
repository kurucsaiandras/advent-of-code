#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <numeric> 

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }
       
    std::string times_str;
    std::string dists_str;
    std::array<int, 4> times;
    std::array<int, 4> dists;
    std::getline(file, times_str);
    std::getline(file, dists_str);
    std::stringstream ss_1(times_str);
    std::stringstream ss_2(dists_str);
    ss_1 >> times_str >> times[0] >> times[1] >> times[2] >> times[3];
    ss_2 >> dists_str >> dists[0] >> dists[1] >> dists[2] >> dists[3];

    times_str = std::to_string(times[0]) + std::to_string(times[1]) + std::to_string(times[2]) + std::to_string(times[3]);
    dists_str = std::to_string(dists[0]) + std::to_string(dists[1]) + std::to_string(dists[2]) + std::to_string(dists[3]);

    uint64_t time = std::stoull(times_str);
    uint64_t dist = std::stoull(dists_str);
    
    int numOfWins = 0;
    for (uint64_t j = 0; j < time; j++) {
        if ((time - j) * j > dist) numOfWins++;
    }

    std::cout << numOfWins << std::endl;
}