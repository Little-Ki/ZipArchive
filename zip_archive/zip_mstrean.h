#pragma once

#include <istream>
#include <ostream>
#include <streambuf>

namespace zip {
    struct IMemoryBuf : std::streambuf {
        IMemoryBuf(const char *base, size_t size) {
            char *p(const_cast<char *>(base));
            this->setg(p, p, p + size);
        }
    };

    struct IMemoryStream : virtual IMemoryBuf, std::istream {
        IMemoryStream(const char *mem, size_t size) : IMemoryBuf(mem, size),
                                                      std::istream(static_cast<std::streambuf *>(this)) {
        }
    };

    struct OMemoryBuf : std::streambuf {
        OMemoryBuf(char *base, size_t size) {
            this->setp(base, base + size);
        }
    };

    struct OMemoryStream : virtual OMemoryBuf, std::ostream {
        OMemoryStream(char *mem, size_t size) : OMemoryBuf(mem, size),
                                                std::ostream(static_cast<std::streambuf *>(this)) {
        }
    };
}