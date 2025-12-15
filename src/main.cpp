#include <windows.h>
#include "../ImWindow/Externals/imgui/imgui.h"
#include "../ImWindow/ImWindow/ImwWindow.h"
#include "../ImWindow/ImWindow/ImwWindowManager.h"
#include "../ImWindow/ImWindowDX11/ImwWindowManagerDX11.h"
using namespace ImWindow;
class MyImwWindow : public ImwWindow, ImwMenu
{
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
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY;
	}
	virtual void OnGui()
	{
		if (ImGui::Button("Open file")) {
			// TODO: error handling
			GetOpenFileNameA(&ofn);
		}
		ImGui::TextUnformatted(mfile);
		// ImGui::InputText("Input", m_pText, 512);

		// ImGui::ShowMetricsWindow();
	}

	virtual void OnMenu()
	{
		if (ImGui::BeginMenu("MyImwWindow"))
		{
		    ImGui::InputText("Input", m_pText, sizeof(m_pText));
			ImGui::EndMenu();
		}
	}

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

	while (oMgr2.Run(false) && oMgr2.Run(true)) Sleep(16);

	ImGui::Shutdown();
    return 0;
}
