cmake_minimum_required(VERSION 3.17)
project(lab3a)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

add_executable(lab3a_run ${SOURCE_FILES})

include_directories(lib)
add_subdirectory(lib)

target_link_libraries(lab3a_run lib)

add_subdirectory(google_tests)