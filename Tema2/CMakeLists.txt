cmake_minimum_required(VERSION 3.14)
project(EffectiveCppMiniProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(effective_cpp_demo src/main.cpp)

target_include_directories(effective_cpp_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)