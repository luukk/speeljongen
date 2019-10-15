#include "files.h"
#include <iostream>
#include <fstream>

std::vector<uint8_t> read_bytes(const std::string& filename) {
    using std::ifstream;
    using std::ios;

    ifstream stream(filename.c_str(), ios::binary|ios::ate);

    if (!stream.good()) {
        std::cout << "Cannot read from file: " << filename.c_str();
    }

    ifstream::pos_type position = stream.tellg();
    size_t file_size = static_cast<size_t>(position);

    std::vector<char> file_contents(file_size);

    stream.seekg(0, ios::beg);
    stream.read(&file_contents[0], position);
    stream.close();

    auto data = std::vector<uint8_t>(file_contents.begin(), file_contents.end());

    return data;
}
