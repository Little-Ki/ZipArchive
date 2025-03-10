#pragma once

#include <vector>

namespace zip {

    std::vector<uint8_t> lzss_compress(const std::vector<uint8_t> src, size_t window_size = 256);

    std::vector<uint8_t> lzss_decompress(const std::vector<uint8_t> src, size_t window_size = 256);

}