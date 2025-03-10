#pragma once
#include <stdint.h>
#include <string>
#include <vector>

constexpr auto SIG_CENTRAL_DIR = 0x02014b50;
constexpr auto SIG_END_CENTRAL_DIR = 0x06054b50;
constexpr auto SIG_FILEHEADER = 0x04034b50;

constexpr auto METHOD_STORE = 0;
constexpr auto METHOD_DEFLATE = 0x08;

namespace zip {

    enum class ZipError {
        Success,
        InvalidSize
    };

    enum class Signature : uint32_t {
        CentralDirectory = 0x02014b50,
        EndOfCentralDirectory = 0x06054b50,
        LocalFileHeader = 0x04034b50,
        DataDescriptor = 0x08074b50
    };

    enum class CompressionMethod : uint16_t {
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
        Bzip2 = 0x0C,
        LZMA = 0x0E,
        CMPSC = 0x10,
        IBMTERSE = 0x12,
        LZ77 = 0x13,
        ZSTD = 0x5D,
        MP3 = 0x5E,
        XZ = 0x5f,
        JPEG = 0x60,
        WavPack = 0x61,
        PPMd = 0x62,
        AE_x = 0x63
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

    union GeneralPurposeBitFlags {
        struct {
            bool encrypted : 1;
            uint8_t compression_options : 2;
            bool crc_and_sizes_in_cd_and_data_descriptor : 1;
            bool enhanced_deflating : 1;
            bool patched_data : 1;
            bool strong_encryption : 1;
            uint8_t unused : 4;
            bool utf8 : 1;
            bool reserved_0 : 1;
            bool central_directory_encrypted : 1;
            bool reserved_1 : 2;
        };
        uint16_t value;
    };

    struct LocalFileHeader {
        Signature signature;
        ZipVersion version;
        GeneralPurposeBitFlags bitflags;
        CompressionMethod compression_method;
        ZipTime modify_time;
        ZipDate modify_date;
        uint32_t crc32;
        uint32_t compressed_size;
        uint32_t uncompressed_size;
        uint16_t filename_length;
        uint16_t extension_length;
    };

    struct CentralDirectoryFileHeader {
        Signature signature;
        ZipVersion version_made;
        ZipVersion version_extract;
        GeneralPurposeBitFlags bitflags;
        CompressionMethod compression_method;
        ZipTime modify_time;
        ZipDate modify_date;
        uint32_t crc32;
        uint32_t compressed_size;
        uint32_t uncompressed_size;
        uint16_t filename_length;
        uint16_t extension_length;
        uint16_t commit_length;
        uint16_t disk_number;
        uint16_t internal_attributes;
        uint16_t external_attributes;
        uint16_t file_offset;
    };

    struct EndOfCentralDirectoryRecord {
        Signature signature;
        uint16_t disk_number;
        uint16_t directory_disk_number;
        uint16_t directory_entries;
        uint16_t directory_total_entires;
        uint32_t directory_size;
        uint32_t directory_offset;
        uint16_t commit_length;
    };

    struct LocalFileDescriptor {
        Signature signature;
        uint32_t crc32;
        uint32_t compressed_size;
        uint32_t origin_size;
    };

    struct MemoryFile {
        CentralDirectoryFileHeader header;
        LocalFileHeader header;
        LocalFileDescriptor desc;
        std::string filename;
        std::string extension;
        std::vector<uint8_t> data;
    };

    struct MemoryDirectory {
        CentralDirectoryFileHeader header;
        std::string filename;
        std::string extension;
        std::string description;

        MemoryFile file;
    };

    struct MemoryEndDirectory {
        EndOfCentralDirectoryRecord header;
    };

}