#include <algorithm>
#include "FileIO.hpp"

FileIO::FileIO(std::string path) {
    filename = path;
}

void FileIO::write(const std::vector<std::string>& input) {
    file.open(filename, std::ios::app);
    file.seekp(0, std::ios::end);
    for(auto it : input)
        file << " " + it;
    file.close();
}

void FileIO::sort(int mode){
    std::vector<std::pair<int, std::pair<std::string, std::string>>> ret;
    file.open(filename, std::ios::in);
    file.seekg(0, std::ios::beg);
    while(!file.eof() && file >> playerscore >> playertime >> playername){
        std::cout << playerscore << " " << playertime << " " << playername << std::endl;
        ret.emplace_back(playerscore, std::make_pair(playertime, playername));
    }
    file.close();

    std::sort(ret.begin(), ret.end(), [&](auto const& l, auto const& r){
        if(mode)
            return l.first > r.first;
        else
            return l.first < r.first;
    });

    file.open(filename, std::ios::out);
    for(auto it : ret)
        file << std::to_string(it.first) + " " +
                it.second.first + " " + it.second.second + "\n";
    file.close();
}

std::vector<std::pair<int, std::pair<std::string, std::string>>> FileIO::read() {
    std::vector<std::pair<int, std::pair<std::string, std::string>>> ret;
    file.open(filename, std::ios::in);
    while(!file.eof() && file >> playerscore >> playertime >> playername){
        ret.emplace_back(playerscore, std::make_pair(playertime, playername));
    }
    file.close();

    return ret;
}