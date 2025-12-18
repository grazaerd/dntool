cmake_minimum_required(VERSION 3.15)
project(imgui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_SRC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

add_executable(imgui2 
        backends/imgui_impl_win32.cpp
        backends/imgui_impl_dx11.cpp
        examples/example_win32_directx11/main.cpp
        imgui.h
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp)

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

target_link_libraries(imgui2 PRIVATE dwmapi)
target_link_libraries(imgui2 PRIVATE d3d11)
target_link_libraries(imgui2 PRIVATE d3dcompiler)
