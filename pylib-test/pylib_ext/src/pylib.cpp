#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#pragma pack(1)
struct pocket_struct {
    pocket_struct() : header(0), timestamp(0), payload(0), crc(0) {}
    uint8_t header;
    uint64_t timestamp;
    uint64_t payload;
    uint32_t crc;
};

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

namespace py = pybind11;

PYBIND11_MODULE(pylib_ext, m) {

    m.def("getDecoded", &getDecoded, R"pbdoc(
        Give deser data
    )pbdoc");

}