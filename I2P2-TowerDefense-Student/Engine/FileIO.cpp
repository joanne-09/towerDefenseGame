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

void FileIO::read(int page) {
    in.open(filename);
    in >> playerscore >> playername;
    in.close();
}