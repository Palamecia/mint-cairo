cmake_minimum_required(VERSION 3.23)
project(mint-cairo)

find_package(mint REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED IMPORTED_TARGET cairo)

add_subdirectory(lib)
add_subdirectory(src)
