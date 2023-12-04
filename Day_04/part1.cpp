#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    int sum = 0;
       
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string card_str;
        std::string card_no;
        std::array<int, 10> winningNums;
        std::array<int, 25> myNums;
        ss >> card_str >> card_no;
        for (int i = 0; i < 10; ++i)
            ss >> winningNums[i];

        std::string sep; ss >> sep;

        for (int i = 0; i < 25; ++i)
            ss >> myNums[i];

        int points = 0;
        for (int i = 0; i < 10; ++i)
            if (std::find(myNums.begin(), myNums.end(), winningNums[i]) != myNums.end())
                points = (points == 0) ? 1 : points * 2;

        sum += points;
    }

    std::cout << sum << std::endl;
}