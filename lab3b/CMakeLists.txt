cmake_minimum_required(VERSION 3.17)
project(lab3b)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

add_executable(lab3b_run ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(lab3b_run src)

add_subdirectory(google_tests)