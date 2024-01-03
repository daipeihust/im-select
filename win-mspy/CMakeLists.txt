cmake_minimum_required(VERSION 3.10)

project(im-select-mspy)


set(CMAKE_CXX_STANDARD 17)

add_executable(im-select-mspy main.cc)
target_compile_options(im-select-mspy PRIVATE "/utf-8")
target_link_libraries(im-select-mspy comsuppw.lib)

