cmake_minimum_required(VERSION 3.1)
project(glad)

add_library(glad)
target_sources(glad PRIVATE src/glad.c src/glad_wgl.c)
target_include_directories(glad PUBLIC include)