cmake_minimum_required(VERSION 3.7)
project(StarTrader)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(BASE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/StarTrader)
set(BIN_OUTPUT_PATH ${BASE_OUTPUT_PATH}/bin)
set(LIBRARY_OUTPUT_PATH ${BASE_OUTPUT_PATH}/lib)
set(RESOURCES_OUTPUT_PATH ${BASE_OUTPUT_PATH}/data) # custom directory to copy resources to

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
set_target_properties(StarTrader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH})

add_dependencies(StarTrader CopyData)

add_custom_target(Release
        DEPENDS StarTrader
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMAND tar -czf startrader.tar.gz StarTrader
        )
set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_BINARY_DIR}/startrader.tar.gz")
