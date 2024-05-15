#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

class FileIO{
protected:
    std::ifstream in;
    std::ofstream out;
    std::string filename;

    std::string playername;
    int playerscore, playertime;
public:
    FileIO();
    void write(const std::vector<std::string>& input);
    std::vector<std::pair<std::pair<int, int>, std::string>> read();
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
