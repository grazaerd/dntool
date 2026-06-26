#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <cstdint>
#include <vector>

#include "file_input.hpp"
#include "libdeflate.h"
#include "../pak/pak_struct.hpp"

class compress {
public:
    // TODO: delete other function; rule of 5
    compress(int compress_level, const char* path);
    
    ~compress();
    
    bool work(unsigned char** out, uint64_t* outsz, const char* path) ;
    
private:
    libdeflate_compressor* compressor;
    std::vector<unsigned char*> compressedfile {};
    uint64_t zlib_bound;
    file_in inpath;
};

#endif