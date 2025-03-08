#pragma once
#include <istream>
#include <string>
#include <vector>

#include "./zip_define.h"

namespace zip {
    class ZipArchive {
    public:
        ZipArchive();

        ZipArchive(CompressionMethod method);

        ZipError load(const std::vector<uint8_t> &data);

        ZipError load(std::istream &stream);

        void pack(std::vector<uint8_t> &buffer);

        void putFile(const std::string &filename, const std::vector<uint8_t> &data);

        void putDir(const std::string& folder);

        void dump(const std::string &filename, std::vector<uint8_t> &buffer);

    private:
        std::vector<MemoryFile> _files;
        std::vector<MemoryDirectory> _dirs;
        std::vector<MemoryEndDirectory> _end;

        CompressionMethod _method ;

    };
}