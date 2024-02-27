project(mint-cairo)

cmake_minimum_required(VERSION 3.1)

find_package(mint REQUIRED)
find_package(cairo REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)
