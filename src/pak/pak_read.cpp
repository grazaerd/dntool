#include <fstream>
#include <string>
#include <vector>

#include "pak_struct.hpp"

namespace pak {
    
class reader_pak {
public:
	void open(std::string_view file) { pak.open(file, pak.binary | pak.in); }

	std::vector<pak::file_index_decomp> copy_data() {

		if (!pak.is_open()) {
			// Retrieve total count of files
			std::uint32_t total = 0u;
			pak.seekg(sizeof(header.filesignature) + sizeof(header.filecount));
			pak.read(std::bit_cast<char*>(&total), sizeof(total));

			std::uint32_t address = 0u;
			for (std::uint32_t i = 0; i != total;) {
				// Retrieve address of file index
				pak.seekg(sizeof(header.filesignature) + sizeof(header.filecount) + sizeof(header.fileindex));
				pak.read(std::bit_cast<char*>(&address), sizeof(address));
				if (address) {
					address += i * sizeof(pak::file_index_decomp);

					pak.seekg(address);

					pak.read(holder.filepath, sizeof(holder.filepath));

					pak.seekg(address + sizeof(holder.filepath) + sizeof(holder.rawsz));
					pak.read(std::bit_cast<char*>(&holder.rawsz), sizeof(holder.rawsz));

					pak.seekg(address + sizeof(holder.filepath) + sizeof(holder.rawsz) + sizeof(holder.decompsz));
					pak.read(std::bit_cast<char*>(&holder.decompsz), sizeof(holder.decompsz));

					pak.seekg(address + sizeof(holder.filepath) + sizeof(holder.rawsz) + sizeof(holder.decompsz) + sizeof(holder.compsz));
					pak.read(std::bit_cast<char*>(&holder.compsz), sizeof(holder.compsz));

					pak.seekg(address + sizeof(holder.filepath) + sizeof(holder.rawsz) + sizeof(holder.decompsz) + sizeof(holder.compsz) + sizeof(holder.offset));
					pak.read(std::bit_cast<char*>(&holder.offset), sizeof(holder.offset));

					vecindex.emplace_back(holder);
				}
				i++;
			}

			return vecindex;
		}

		return {};
	}

private:
    // Pak file index start
	pak::file_index_decomp holder;
	std::vector<std::string> vecpath;
	std::vector<pak::file_index_decomp> vecindex;
    pak::header header;
	std::fstream pak = {};
};

}