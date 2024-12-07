cmake_minimum_required(VERSION 3.30)
project(2024)

set(CMAKE_CXX_STANDARD 23)

find_package(CURL REQUIRED)

include_directories(core)
include_directories(util)

file(GLOB SOURCES "day*/day*.cpp" "core/*.cpp" "util/*.cpp")
file(GLOB HEADERS "day*/day*.h" "core/*.h" "util/*.h")

add_executable(2024
        main.cpp
        ${SOURCES}
)

target_link_libraries(2024 CURL::libcurl)
