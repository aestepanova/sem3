cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

add_executable(lab2_run ${SOURCE_FILES})

include_directories(lab2_9_lib)
add_subdirectory(lab2_9_lib)

target_link_libraries(lab2_run lab2_9_lib)

add_subdirectory(google_tests)