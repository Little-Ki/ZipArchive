#pragma once
#include <string>
#include <vector>

namespace zip {
    class ZipArchive {
    public:
        ZipArchive();

        bool load(const std::vector<uint8_t> &data);

        void pack(std::vector<uint8_t> &buffer);

        void push(const std::string &filename, const std::vector<uint8_t> &data);

        void dump(const std::string &filename, std::vector<uint8_t>& buffer);
        
    };
}