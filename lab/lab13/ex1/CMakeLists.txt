cmake_minimum_required(VERSION 3.28)
project(VectorModuleLab CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(vector_inst_lib)

target_sources(vector_inst_lib
    PUBLIC
        FILE_SET CXX_MODULES FILES vector_module.ixx
    PRIVATE
        vector_instantiations.cpp
)

add_executable(main_app main.cpp)
target_link_libraries(main_app PRIVATE vector_inst_lib)