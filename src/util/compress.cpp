
#include "../pak/pak_struct.hpp"

#include "libdeflate.h"
#include "compress.hpp"
#include "file_input.hpp"

compress::compress(int compress_level) {
    compressor = libdeflate_alloc_compressor(compress_level);
}

// WIP whole folder
bool compress::work(unsigned char** out, uint64_t* outsz, file_in& path) {
    const std::string var = path.file_data();
    const uint64_t sz = libdeflate_zlib_compress_bound(compressor, var.size());
    in_memory.resize(sz);
    std::vector<unsigned char> outtest(sz);
    const uint8_t result = libdeflate_zlib_compress(compressor, var.data(), var.size(), *in_memory.data() , sz);
    *out = *in_memory.data();
    *outsz = sz;
    // if (result != 0) {
    //    return false;
    // }
    
    return true;
}