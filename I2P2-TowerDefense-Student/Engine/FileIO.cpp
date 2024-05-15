#include "FileIO.hpp"

FileIO::FileIO() {
    filename = "../Resource/scoreboard.txt";
}

void FileIO::write(const std::vector<std::string>& input) {
    out.open(filename, std::ios::app);
    for(auto it : input)
        out << " " + it;
    out.close();
}

std::vector<std::pair<std::pair<int, int>, std::string>> FileIO::read() {
    std::vector<std::pair<std::pair<int, int>, std::string>> ret;
    in.open(filename);
    while(!in.eof() && in >> playerscore >> playertime >> playername){
        std::cout << playerscore << " " << playertime << " " << playername << std::endl;
        ret.emplace_back(std::make_pair(playerscore, playertime), playername);
    }
    in.close();
    return ret;
}