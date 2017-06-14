cmake_minimum_required(VERSION 3.7)
project(Game)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        game.h
        world.cpp
        world.h
        sector.cpp
        sector.h
        structs.h
        controller.cpp
        controller.h)
add_library(Game ${SOURCE_FILES})

target_link_libraries(Game Common GUI)
