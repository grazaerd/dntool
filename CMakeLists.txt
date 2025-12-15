cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

project(dntools)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(dntools src/main.cpp)

set(imwindow "${CMAKE_CURRENT_SOURCE_DIR}/lib/ImWindow")

add_subdirectory(${imwindow})

target_include_directories(dntools SYSTEM PRIVATE ${imwindow})

target_link_libraries(dntools PRIVATE ImWindow)
target_link_libraries(dntools PRIVATE d3d11)
target_link_libraries(dntools PRIVATE dxgi)
target_link_libraries(dntools PRIVATE d3dcompiler)
