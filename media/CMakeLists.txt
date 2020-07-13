cmake_minimum_required(VERSION 2.8.0)
project(media)

set(MEDIA_SRCS
    media.cpp) 

add_library(media SHARED ${MEDIA_SRCS})
