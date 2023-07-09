//
// Created by rustam on 09.07.23.
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#pragma pack(1)
struct pocket_struct {
    pocket_struct() : header(0), timestamp(0), payload(0), crc(0) {}
    uint8_t header;
    uint64_t timestamp;
    uint64_t payload;
    uint32_t crc;
};


int main() {
    std::string file_name = "../../out.bin";
    std::ifstream myfile(file_name, std::ios_base::in | std::ios_base::binary | std::ios::ate);

    std::streampos size_;
    if (myfile.is_open()) {
        std::cout << "start decode" << std::endl;
        size_ = myfile.tellg();
        myfile.seekg(0, std::ios::beg);
        std::cout << size_ << std::endl;
        std::vector<char> buffer(size_);
        myfile.read(buffer.data(), size_);

        myfile.close();
        std::ofstream out_file("../../out_cpp.txt");
        for (size_t i = 0; i < size_; i++) {
            uint8_t tmp = buffer[i];

            if (tmp == 0xab) {
                auto decoded = reinterpret_cast<pocket_struct * > (buffer.data() + i);
                out_file << " "
                << unsigned (decoded->header) << " "
                << decoded->timestamp << " "
                << decoded->payload << " "
                << decoded->crc << std::endl;
                i += sizeof (pocket_struct) - 1;
            }
        }
        out_file.close();

    }
    return 0;
}
