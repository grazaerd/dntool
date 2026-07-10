#ifndef FILE_INPUT_HPP
#define FILE_INPUT_HPP

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class file_in {
public:
    file_in(const char* path);
    
    uint64_t filesz() const;

    std::string file_data();

    void set_path(const char* path);

    uint64_t file_count() const;
private:
    fs::path in;
    fs::recursive_directory_iterator recur_in{in};
    std::ifstream filestream;
    uint64_t count;
};

#endif