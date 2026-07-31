#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdlib>
#include <string>
#include <stringapiset.h>

#if defined(__GNUC__) || defined(__clang__)
#define likely(x) __builtin_expect(bool(x),1)
#define unlikely(x) __builtin_expect(bool(x),0)
#define force_inline inline __attribute__((always_inline))
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#define force_inline inline
#endif

namespace UTIL {

    inline std::string wide_to_utf8(const wchar_t* str)
    {
        if (!str)
            return {};
    
        int size = WideCharToMultiByte(
            CP_UTF8,
            0,
            str,
            -1,
            nullptr,
            0,
            nullptr,
            nullptr
        );
    
        if (size <= 0)
            return {};
    
        std::string result(size - 1, '\0');
    
        WideCharToMultiByte(
            CP_UTF8,
            0,
            str,
            -1,
            result.data(),
            size,
            nullptr,
            nullptr
        );
    
        return result;
    }



    
}

#endif