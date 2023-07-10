//
// Created by rustam on 09.07.23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#pragma pack(1)
struct pocket_struct {
    pocket_struct() : header(0), timestamp(0), payload(0), crc(0) {}
    uint8_t header;
    uint64_t timestamp;
    uint64_t payload;
    uint32_t crc;
};

std::vector<char> getBufferFromFile(std::string & file_name) {
    std::ifstream myfile(file_name, std::ios_base::in | std::ios_base::binary | std::ios::ate);
    std::streampos size_;
    size_ = myfile.tellg();
    std::vector<char> buffer(size_);
    if (myfile.is_open()) {
        myfile.seekg(0, std::ios::beg);
        myfile.read(buffer.data(), size_);
    }
    myfile.close();
    return buffer;
}

std::vector<pocket_struct> getDecoded(std::vector <char> & buffer) {
    std::vector<pocket_struct> out_vector;

    for (size_t i = 0; i < buffer.size(); i++) {
        uint8_t tmp = buffer[i];

        if (tmp == 0xab) {
            auto decoded = reinterpret_cast<pocket_struct *> (buffer.data() + i);
            out_vector.push_back(*decoded);
            i += sizeof (pocket_struct) - 1;
        }
    }
    return out_vector;
}

std::ofstream & operator << (std::ofstream & file, const std::vector<pocket_struct> & decoded) {
    for (auto x : decoded) {
        file << unsigned (x.header) << " "
        << x.timestamp << " "
        << x.payload << " "
        << x.crc << std::endl;
    }
    return file;
}

int main() {
    std::string file_name = "../../out.bin";
    auto start = std::chrono::high_resolution_clock::now();

    auto buffer = getBufferFromFile(file_name);
    auto decoded_ = getDecoded(buffer);

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Duration: " << std::chrono::duration_cast <std::chrono::milliseconds> (stop - start).count()
    << " ms" << std::endl;

    std::ofstream out_file("../../out_cpp.txt");
    out_file << decoded_ ;
    out_file.close();

    return 0;
}
