cmake_minimum_required(VERSION 3.30)
project(2024)

set(CMAKE_CXX_STANDARD 23)

find_package(CURL REQUIRED)

include_directories(util)

add_executable(2024
        main.cpp
        day01/day01.cpp
        day02/day02.cpp
        util/format.cpp
        util/input.cpp
        util/loader.cpp
        util/timed.cpp
        day01/day01.h
        day02/day02.h
)

target_link_libraries(2024 CURL::libcurl)
