#pragma once

#include <stdint.h>

constexpr auto SIG_CENTRAL_DIR = 0x02014b50;
constexpr auto SIG_END_CENTRAL_DIR = 0x06054b50;
constexpr auto SIG_FILEHEADER = 0x04034b50;

constexpr auto METHOD_STORE = 0;
constexpr auto METHOD_DEFLATE = 0x08;

namespace zip {

    enum class Signature : uint32_t {
        CentralDirectory = 0x02014b50,
        EndOfCentralDirectory = 0x06054b50,
        LocalFileHeader = 0x04034b50,
        DataDescriptor = 0x08074b50
    };

    enum class CompressMethod : uint16_t {
        Store = 0x00,
        Shrunk = 0x01,
        Factor1 = 0x02,
        Factor2 = 0x03,
        Factor3 = 0x04,
        Factor4 = 0x05,
        Implod = 0x06,
        Reserved0 = 0x07,
        Deflate = 0x08,
        Deflate64 = 0x09,
        Pkware = 0x0A,
        Reserved1 = 0x0B,
        Bzip2 = 0x0C
    };

    enum class ZipVersion : uint16_t {
        Store = 0x000A,
        Deflate = 0x0014,
        Zip64 = 0x002D
    };

    union ZipDate {
        struct {
            int8_t day_of_month : 5;
            int8_t month : 4;
            int8_t offset_1980 : 7;
        };
        uint16_t value;
    };


    union ZipTime {
        struct {
            int8_t half_second : 5;
            int8_t minute : 6;
            int8_t hour : 5;
        };
        uint16_t value;
    };

#pragma pack(push, 1)

    struct LocalFileHeader {
        Signature signature;
        ZipVersion unzip_version;
        uint16_t bitflags;
        CompressMethod compress_method;
        ZipTime modify_time;
        ZipDate modify_date;
        uint32_t crc32;
        uint32_t compressed_size;
        uint32_t origin_size;
        uint16_t filename_len;
        uint16_t extension_len;
        // uint8_t string[0];
    };

    struct CentralDirectoryRecord {
        Signature signature;
        ZipVersion zip_version;
        ZipVersion unzip_version;
        uint16_t bitflags;
        CompressMethod compress_method;
        ZipTime modify_time;
        ZipDate modify_date;
        uint32_t crc32;
        uint32_t compressed_size;
        uint32_t origin_size;
        uint16_t filename_len;
        uint16_t extension_len;
        uint16_t commit_len;
        uint16_t disk_index;
        uint16_t internal_props;
        uint16_t external_props;
        uint16_t offset_at;
        // uint8_t string[0];
    };

    struct EndOfCentralDirectoryRecord {
        Signature signature;
        uint16_t current_disk_index;
        uint16_t central_disk_index;
        uint16_t central_entries_disk_index;
        uint16_t central_entries_count;
        uint32_t central_size;
        uint32_t offset_at;
        uint16_t commit_len;
        // uint8_t string[0];
    };

    struct LocalFileDescriptor {
        Signature signature;
        uint32_t crc32;
        uint32_t compressed_size;
        uint32_t origin_size;
    };
#pragma pack(pop)
}