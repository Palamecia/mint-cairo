project(mint-cairo)

cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/share/cmake)

find_package(mint REQUIRED)

# include(install)

add_subdirectory(src)
