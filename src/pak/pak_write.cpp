#include <array>
#include <filesystem>
#include <fstream>


#include "pak_struct.hpp"

namespace pak {
class pak_write {
public:

    bool is_exist() {
        if (!filepath.empty()) {
            if (std::filesystem::exists(filepath)) {
                return true;
            }
            return false;
        }
        return false;
    }

    void open(std::string_view file) { pak.open(file, pak.binary | pak.in); }

    // Full write
    bool write(/* filepath */) {
        if (!pak.is_open()) {
            // write header first
            pak.write(reinterpret_cast<const char*>(head.data()), head.size());
            
        }
        return false;
    }

    bool append() {
    // to add : append function

        return false;
    }
    
private:
	std::array<pak::header, sizeof(pak::header)> head;
    std::string filename = {};
    std::filesystem::path filepath = { filename };
	std::fstream pak = {};
};
    
}