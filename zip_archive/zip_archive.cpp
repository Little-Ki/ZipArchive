#include "zip_archive.h"

namespace zip {

    ZipArchive::ZipArchive() {
    }

    ZipError ZipArchive::load(const std::vector<uint8_t> &data) {
        
        return ZipError::Success;
    }

    ZipError ZipArchive::load(std::istream &in) {
        std::vector<uint8_t> buffer;

        const auto prev_pos = in.tellg();
        in.seekg(0, in.end);
        const auto file_size = in.tellg();
        in.seekg(prev_pos, in.beg);

        buffer.resize(file_size);

        return load(buffer);
    }

    void ZipArchive::pack(std::vector<uint8_t> &buffer) {
    }
}