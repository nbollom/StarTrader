cmake_minimum_required(VERSION 3.7)
project(Common)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        common.h
        log.cpp
        log.h
        commandline.cpp
        commandline.h
        commandlineoptions.cpp
        commandlineoptions.h
        commandlineexeptions.cpp
        commandlineexeptions.h
        json.cpp
        json.h
        jsonvalue.h
        jsoniterable.h
        jsonobject.cpp
        jsonobject.h
        jsonarray.cpp
        jsonarray.h
        jsonnull.cpp
        jsonnull.h
        jsonstring.cpp
        jsonstring.h
        jsonboolean.cpp
        jsonboolean.h
        jsonnumber.cpp
        jsonnumber.h)

add_library(Common ${SOURCE_FILES})
