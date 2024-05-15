#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

class FileIO{
protected:
    std::fstream file;
    std::string filename;
    int preRegScore, preRegTime;

    std::string playername, playertime;
    int playerscore;
public:
    FileIO();
    void write(const std::vector<std::string>& input);
    void sort();
    std::vector<std::pair<int, std::pair<std::string, std::string>>> read();
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
