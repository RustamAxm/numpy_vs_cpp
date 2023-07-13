//
// Created by rustam on 09.07.23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>

#include "log_duration.h"

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

std::vector<pocket_struct> & getDecodedFullCast(std::vector <char> & buffer) {

    for (size_t i = 0; i < buffer.size(); i++) {
        uint8_t tmp = buffer[i];

        if (tmp == 0xab) {
            auto decoded = reinterpret_cast<std::vector<pocket_struct> * > (&buffer);
            return *decoded;
        }
    }
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
    auto buffer = getBufferFromFile(file_name);


    {
        LOG_DURATION("simple impl");
        auto decoded_ = getDecoded(buffer);
    }

    {
        LOG_DURATION("simple full cast impl");
        auto decoded_ = getDecodedFullCast(buffer);
    }


    {
        LOG_DURATION("thread impl");
        size_t len_ = buffer.size() / 2;
        std::vector<char> hi_(buffer.begin(), buffer.begin() + len_);
        std::vector<char> lo_(buffer.begin() + len_, buffer.end());

        std::vector<pocket_struct> decode_1;
        std::vector<pocket_struct> decode_2;

        std::thread th_1 ([&] () {
            decode_1 = getDecoded(hi_);
        });

        std::thread th_2 ([&] () {
            decode_2 = getDecoded(lo_);
        });
        th_1.join();
        th_2.join();

        decode_1.insert(decode_1.end(), decode_2.begin(), decode_2.end());
    }


    {
        LOG_DURATION("async impl");
        size_t len_ = buffer.size() / 2;
        std::vector<char> hi_(buffer.begin(), buffer.begin() + len_);
        std::vector<char> lo_(buffer.begin() + len_, buffer.end());

        std::vector<pocket_struct> decode_1;
        std::vector<pocket_struct> decode_2;

        auto ft_1 = std::async(std::launch::async, [&hi_] { return getDecoded(hi_);});
        auto ft_2 = std::async(std::launch::async, [&lo_] { return getDecoded(lo_);});
        decode_1 = ft_1.get();
        decode_2 = ft_2.get();
        decode_1.insert(decode_1.end(), decode_2.begin(), decode_2.end());
    }

    return 0;
}
