cmake_minimum_required(VERSION 3.15)
project(ImWindow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(imgui "${CMAKE_CURRENT_SOURCE_DIR}/Externals/imgui")

add_subdirectory(${imgui})

file(GLOB IMWINDOW_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)
set(IMWINDOW_SOURCES2
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwStatusBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwToolBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwWindowManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwContainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwPlatformWindow.cpp
)

set(IMWINDOW_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwStatusBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwToolBar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwWindowManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwContainer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwMenu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindow/ImwPlatformWindow.h
)
set(JSON
    ${CMAKE_CURRENT_SOURCE_DIR}/Externals/UtilsCollection/JsonStthm/JsonStthm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Externals/UtilsCollection/JsonStthm/JsonStthm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Externals/UtilsCollection/JsonStthm/JsonStthmConfig.h
)
set(DX11
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindowDX11/ImwPlatformWindowDX11.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindowDX11/ImwWindowManagerDX11.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindowDX11/Win32MessageHelper.cpp
)

set(ImWindowEasyWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindowEasyWindow/ImwPlatformWindowEasyWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImWindowEasyWindow/ImwWindowManagerEasyWindow.cpp
)
set(EasyWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/Externals/EasyWindow/EasyWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Externals/EasyWindow/EasyWindowWin32.cpp
)
add_library(ImWindow STATIC ${IMWINDOW_SOURCES} ${IMWINDOW_SOURCES2} ${IMWINDOW_HEADERS} ${JSON} ${DX11} ${ImWindowEasyWindow} ${EasyWindow})

target_include_directories(ImWindow
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(ImWindow PRIVATE imgui)
