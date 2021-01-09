cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

add_executable(lab4_run ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(lab4_run src)

add_subdirectory(google_tests)