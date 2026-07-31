#include "dir.hpp"
#include "util.hpp"

#include <winerror.h>
#include <winscard.h>

Directory::Directory() {
    m_result = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&m_dialog));
}

std::string Directory::get_folder() {
    if (SUCCEEDED(m_result)) {
        m_dialog->SetOptions(FOS_PICKFOLDERS);
        
        m_result = m_dialog->Show(nullptr);

        if (SUCCEEDED(m_result)) {
            m_result = m_dialog->GetResult(&m_item);
            
            if (SUCCEEDED(m_result)) {
                m_result = m_item->GetDisplayName(SIGDN_FILESYSPATH, &m_path);
                
                if (SUCCEEDED(m_result)) {
                    m_ret_path = UTIL::wide_to_utf8(m_path);
                    CoTaskMemFree(m_path);
                }
                
                m_item->Release();
                
            }

        }
    }
    return m_ret_path;
}

std::string Directory::get_file() {
    if (SUCCEEDED(m_result)) {
        m_dialog->SetOptions(FOS_FILEMUSTEXIST | FOS_PATHMUSTEXIST);
        
        m_result = m_dialog->Show(nullptr);

        if (SUCCEEDED(m_result)) {
            m_result = m_dialog->GetResult(&m_item);
            
            if (SUCCEEDED(m_result)) {
                m_result = m_item->GetDisplayName(SIGDN_FILESYSPATH, &m_path);
                
                if (SUCCEEDED(m_result)) {
                    m_ret_path = UTIL::wide_to_utf8(m_path);
                    CoTaskMemFree(m_path);
                }
                
                m_item->Release();
                
            }

        }
    }
    return m_ret_path;
}