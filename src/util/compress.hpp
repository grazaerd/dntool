#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <cstdint>
#include <vector>

#include "file_input.hpp"
#include "libdeflate.h"

class compress {
public:
    compress(int compress_level);
    
    bool work(unsigned char** out, uint64_t* outsz,  file_in& path) ;
    
private:
    libdeflate_compressor* compressor;
    std::vector<unsigned char*> compressedfile {};
    uint64_t zlib_bound;
};

#endif