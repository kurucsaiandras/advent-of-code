#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <numeric> 

struct Map {
    uint64_t dest;
    uint64_t source;
    uint64_t length;
};

uint64_t mapForward(const std::vector<Map>& maps, uint64_t src) {
    for (const auto& m : maps) {
        if (src >= m.source && src < m.source + m.length) {
            return src - m.source + m.dest;
        }
    }
    return src;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }
       
    std::string line;
    std::getline(file, line);
    std::string seed_str;
    std::stringstream ss(line);
    ss >> seed_str;
    std::array<uint64_t, 20> seeds;
    for (int i = 0; i < 20; ++i) {
        ss >> seeds[i];
    }

    std::vector<std::vector<Map>> allMaps;
    while (std::getline(file, line)) {
        if (line.length() == 0) {
            std::stringstream ss(line);
            std::getline(file, line); // skip head line
            std::vector<Map> map = {};
            allMaps.push_back(map);
        }
        else {
            Map m;
            std::stringstream ss(line);
            ss >> m.dest >> m.source >> m.length;
            allMaps.back().push_back(m);
        }
    }

    uint64_t minLoc = std::numeric_limits<uint64_t>::max();
    for (int i = 0; i < 20; i+=2) {
        for (uint64_t seed = seeds[i]; seed < seeds[i] + seeds[i + 1]; seed++) {
            uint64_t loc = seed;
            for (int j = 0; j < allMaps.size(); j++) {
                loc = mapForward(allMaps[j], loc);
            }
            minLoc = std::min(minLoc, loc);
            long double percent = static_cast<long double>(seed - seeds[i]) / static_cast<long double>(seeds[i + 1]);
            if (seed % 1000000 == 0) {
                std::cout << percent << std::endl;
            }
        }
        std::cout << "Interval processed." << std::endl;
    }

    std::cout << minLoc << std::endl;
}