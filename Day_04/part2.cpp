#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <numeric> 

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "cant open!";
        return 0;
    }

    int sum = 0;
    std::array<int, 214> numOfCards;
    numOfCards.fill(1);
       
    std::string line;
    int cardIdx = 0;
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

        int matches = 0;
        for (int i = 0; i < 10; ++i)
            if (std::find(myNums.begin(), myNums.end(), winningNums[i]) != myNums.end())
                matches++;

        for (int i = cardIdx + 1; i < cardIdx + 1 + matches; ++i) {
            numOfCards[i] += numOfCards[cardIdx];
        }

        cardIdx++;
    }

    sum = std::accumulate(numOfCards.begin(), numOfCards.end(), sum);

    std::cout << sum << std::endl;
}