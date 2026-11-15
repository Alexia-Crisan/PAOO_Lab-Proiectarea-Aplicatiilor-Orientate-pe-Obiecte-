cmake_minimum_required(VERSION 3.14)
project(ResourceManagement LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(resource_demo src/main.cpp)

target_include_directories(resource_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)