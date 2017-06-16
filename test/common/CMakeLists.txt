cmake_minimum_required(VERSION 3.7)
project(Common_Test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        json.cpp)

add_executable(Common_Test ${SOURCE_FILES})
target_link_libraries(Common_Test Common)

add_test(NAME Test_Common
        COMMAND Common_Test)
