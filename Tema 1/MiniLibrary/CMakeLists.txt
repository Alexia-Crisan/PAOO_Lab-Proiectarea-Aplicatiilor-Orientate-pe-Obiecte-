cmake_minimum_required(VERSION 3.16)

project(MiniLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MiniLibrary
    src/main.cpp
    src/Book/Book.cpp
    src/Member/Member.cpp
    src/BookCollection/BookCollection.cpp
    src/Loan/Loan.cpp
    src/Library/Library.cpp
)

target_include_directories(MiniLibrary PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
