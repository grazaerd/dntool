cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

project(dntools)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(dntools src/main.cpp
            src/util/compress.cpp
            src/util/file_input.cpp)

set(imwindow "${CMAKE_CURRENT_SOURCE_DIR}/lib/ImWindow")
set(libdeflate "${CMAKE_CURRENT_SOURCE_DIR}/lib/libdeflate")

add_subdirectory(${imwindow})
add_subdirectory(${libdeflate})

target_include_directories(dntools PRIVATE ${imwindow})
target_include_directories(dntools PRIVATE ${libdeflate})

target_link_libraries(dntools PRIVATE ImWindow)
target_link_libraries(dntools PRIVATE d3d11)
target_link_libraries(dntools PRIVATE dxgi)
target_link_libraries(dntools PRIVATE d3dcompiler)
target_link_libraries(dntools PRIVATE libdeflate_static)
