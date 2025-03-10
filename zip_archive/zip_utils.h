#pragma once
#include <vector>

namespace zip {

    template <typename T>
    class vector_snippet {
    public:
        using iterator = std::vector<T>::const_iterator;

        vector_snap(iterator begin, iterator end, size_t size) : _begin(begin), _pos(begin), _end(end), _size(size) {
        }

    private:
        iterator _begin;
        iterator _end;
        iterator _pos;
        size_t _size;
    };

}