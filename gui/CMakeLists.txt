cmake_minimum_required(VERSION 3.7)
project(GUI)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED image ttf mixer gfx)

set(SOURCE_FILES gui.h gui.cpp window.h eventmanager.cpp eventmanager.h sdlwindow.cpp sdlwindow.h keymap.cpp keymap.h scene.cpp scene.h)
add_library(GUI ${SOURCE_FILES})

target_link_libraries(GUI ${SDL2_LIBRARIES})
include_directories(${SDL2_INCLUDE_DIR})
