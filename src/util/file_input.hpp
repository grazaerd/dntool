#ifndef FILE_INPUT_HPP
#define FILE_INPUT_HPP

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class file_in {
public:
    file_in();
    
    uint64_t filesz() const;

    std::string file_data();

    void set_path(const char* path);

private:
    fs::path in;
    fs::recursive_directory_iterator recur_in;
    std::ifstream filestream;
};

#endif