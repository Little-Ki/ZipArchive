#include "zip_lzss.h"

namespace zip {

    std::vector<uint8_t> lzss_compress(const std::vector<uint8_t> src, size_t window_size) {
        std::vector<uint8_t> buf(src.size() + window_size);
        std::vector<uint8_t> out(src.size() + 1024);

        std::copy(src.begin(), src.end(), buf.begin() + window_size);

        auto win = buf.data();
        auto lpd = buf.data() + window_size;
        int pos = 0, total = 0;

        return out;
    }

    std::vector<uint8_t> lzss_decompress(const std::vector<uint8_t> src, size_t window_size) {
        return std::vector<uint8_t>();
    }
}