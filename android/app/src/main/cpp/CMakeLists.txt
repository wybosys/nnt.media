cmake_minimum_required(VERSION 2.8.0)

add_subdirectory(../../../../../media media)

add_library(native-lib SHARED
    native-lib.cpp)

find_library(log-lib log)

target_link_libraries(native-lib
    ${log-lib})
