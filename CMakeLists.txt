cmake_minimum_required(VERSION 3.25)
project(NumCompute LANGUAGES CXX)

set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_library(NumCompute STATIC
        NumCompute.cpp)
add_library(AGU::NumCompute ALIAS NumCompute)

add_subdirectory(Differential)
add_subdirectory(Optimizer)
add_subdirectory(Core)
add_subdirectory(Samples)

# ヘッダーファイルのパスを指定
target_include_directories(NumCompute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(NumCompute PUBLIC AGU::NumCompute::Differential AGU::NumCompute::Optimizer AGU::NumCompute::Core)

set_target_properties(NumCompute
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
