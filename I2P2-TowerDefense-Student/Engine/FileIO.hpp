#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
#include <iostream>
#include <fstream>
#include <vector>

class FileIO{
protected:
    std::ifstream in;
    std::ofstream out;
    std::string filename;

    std::string playername;
    int playerscore;
public:
    FileIO();
    void write(const std::vector<std::string>& input);
    void read(int page);
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_FILEIO_HPP
