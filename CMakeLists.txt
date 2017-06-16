cmake_minimum_required(VERSION 3.7)
project(StarTrader)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)
set(RESOURCES_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/data) # custom directory to copy resources to

option(BUILD_TESTS "Build the test projects" OFF)

add_subdirectory(game)
add_subdirectory(common)
add_subdirectory(gui)
add_subdirectory(data)
if (BUILD_TESTS)
    enable_testing()
    SET(CTEST_OUTPUT_ON_FAILURE ON)
    add_subdirectory(test/common)
endif (BUILD_TESTS)

set(SOURCE_FILES main.cpp)

add_executable(StarTrader ${SOURCE_FILES})
target_link_libraries(StarTrader Common Game)

add_dependencies(StarTrader CopyData)

#TODO: add packager custom target
