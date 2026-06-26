
#include "../pak/pak_struct.hpp"

#include "libdeflate.h"
#include "compress.hpp"
#include "file_input.hpp"

compress::compress(int compress_level, const char* path) {
    inpath.set_path(path);
    compressor = libdeflate_alloc_compressor(compress_level);
    // zlib_bound = libdeflate_zlib_compress_bound(compressor, var.size());
}

compress::~compress() {
    
}
// WIP whole folder
bool compress::work(unsigned char** out, uint64_t* outsz, const char* path) {
    file_in dir(path);
    std::string var = dir.file_data();
    uint64_t sz = libdeflate_zlib_compress_bound(compressor, var.size());
    unsigned char* test = new unsigned char(sz);
    std::vector<unsigned char> outtest(sz);
    const uint8_t result = libdeflate_zlib_compress(compressor, var.data(), var.size(), test , sz);
    *out = test;
    *outsz = sz;
    //if (result != 0) {
    //    return false;
    //}
    
    return true;
}