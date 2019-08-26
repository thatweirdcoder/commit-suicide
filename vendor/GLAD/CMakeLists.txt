cmake_minimum_required(VERSION 3.14)
project(glad)

add_library(glad src/glad.c)

target_include_directories(glad PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
