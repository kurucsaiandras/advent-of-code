#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

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
    
    int res = 1;
    for (int i = 0; i < 4; ++i) {
        int numOfWins = 0;
        for (int j = 0; j < times[i]; j++) {
            if ((times[i] - j) * j > dists[i]) numOfWins++;
        }
        res *= numOfWins;
    }
    std::cout << res << std::endl;
}