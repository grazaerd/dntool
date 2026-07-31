#ifndef DIR_HPP
#define DIR_HPP

#include <string>
#include <shobjidl.h>
#include <winerror.h>

class Directory {
public:

    Directory();

    std::string get_folder();

    std::string get_file();

private:
    IFileOpenDialog* m_dialog = nullptr;
    IShellItem* m_item = nullptr;
    PWSTR m_path = nullptr;
    HRESULT m_result = E_FAIL;
    std::string m_ret_path = "";
};

#endif