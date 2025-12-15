#include <string>
#include <windows.h>
#include "../ImWindow/Externals/imgui/imgui.h"
#include "../ImWindow/ImWindow/ImwWindow.h"
#include "../ImWindow/ImWindow/ImwWindowManager.h"
#include "../ImWindow/ImWindowDX11/ImwWindowManagerDX11.h"
#include "pak/pak.hpp"
#include <vector>

#include <fstream>
#include <bit>

using namespace ImWindow;

class reader_pak {
public:
	void open(std::string file) { pak.open(file, pak.binary | pak.in); }

	std::vector<pak::file_index_decomp> copy_data() {

		if (pak.is_open()) {
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
	std::fstream pak {};
};

class MyImwWindow : public ImwWindow, ImwMenu {
public:
	MyImwWindow(const char* pTitle = "MyImwWindow")
		: ImwWindow(ImWindow::E_WINDOW_MODE_ALONE)
		, ImwMenu(0, false)
	{
		SetTitle(pTitle);
		m_pText[0] = 0;

		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = mfile;
		ofn.nMaxFile = sizeof(mfile);
		ofn.lpstrFilter = "Dragon Nest Pak File (.pak)\0*.pak\0";
		ofn.lpstrInitialDir = "C:\\";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY;
	}
	virtual void OnGui()
	{
		static std::string var;
		static std::size_t var2;
		static std::vector<std::string> var3;
		static std::vector<pak::file_index_decomp> var4;
		if (ImGui::Button("Open file")) {
			// TODO: error handling
			if (GetOpenFileNameA(&ofn)) {
				pak.open(mfile);
				var4 = pak.copy_data();
			}
		}
		ImGui::Text("File Path: %s", mfile);
		ImGui::TextUnformatted("List of files: ");
		for (pak::file_index_decomp& s : var4) {
			ImGui::TextUnformatted(s.filepath);
			ImGui::Text("%08x", s.rawsz);
			ImGui::Text("%08x", s.decompsz);
			ImGui::Text("%08x", s.compsz);
			ImGui::Text("%08x", s.offset);
		}
		// ImGui::Text("%zu",var2);
		// ImGui::InputText("Input", m_pText, 512);

		// ImGui::ShowMetricsWindow();
	}

	virtual void OnMenu()
	{

	}
	reader_pak pak;
	OPENFILENAMEA ofn {};
	char mfile[260] {};
	char m_pText[512] {};
};

int main() {
	ImwWindowManagerDX11 oMgr2(true);

	oMgr2.Init();

	ImWindow::ImwWindowManager& oMgr = *ImWindow::ImwWindowManager::GetInstance();

	oMgr.SetMainTitle("DnTools WIP");

    ImwWindow* pWindow1 = new MyImwWindow();


    oMgr.Dock(pWindow1);

	while (oMgr2.Run(false) && oMgr2.Run(true)) {
		Sleep(16);
	}

	ImGui::Shutdown();

    return 0;
}
