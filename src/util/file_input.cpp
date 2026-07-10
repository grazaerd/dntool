#include "file_input.hpp"

namespace fs = std::filesystem;

file_in::file_in(const char* path) : in(path) {
    if (!in.empty()) {
        for(auto const& dir_entry : recur_in) { // TODO: to verify
            if (!recur_in->is_directory()) {
                count++;
            }
        }
    }
}


uint64_t file_in::filesz() const {
    if (!in.empty()) {
        return fs::file_size(in);
    }
    return 0;
}

std::string file_in::file_data() {
    filestream.open(in, std::ios::in | std::ios::binary);
    
    const uint64_t sz = fs::file_size(in);

    std::string var(sz, '\0');

    filestream.read(var.data(), sz);

    filestream.close();

    return var;
}

void file_in::set_path(const char* path) {
    in = path;
}

uint64_t file_in::file_count() const {
    return count;
}