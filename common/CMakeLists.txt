cmake_minimum_required(VERSION 3.7)
project(Common)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        common.h
        log/log.cpp
        log/log.h
        commandline/commandline.cpp
        commandline/commandline.h
        commandline/commandlineoptions.cpp
        commandline/commandlineoptions.h
        commandline/commandlineexeptions.cpp
        commandline/commandlineexeptions.h
        json/json.cpp
        json/json.h
        json/jsonvalue.h
        json/jsoniterable.h
        json/jsonobject.cpp
        json/jsonobject.h
        json/jsonarray.cpp
        json/jsonarray.h
        json/jsonnull.cpp
        json/jsonnull.h
        json/jsonstring.cpp
        json/jsonstring.h
        json/jsonboolean.cpp
        json/jsonboolean.h
        json/jsonnumber.cpp
        json/jsonnumber.h
        json/jsonparseexception.h
        json/jsonparsestream.cpp
        json/jsonparsestream.h
        configuration/configuration.cpp
        configuration/configuration.h
        resource/resource.cpp
        resource/resource.h)

add_library(Common ${SOURCE_FILES})
