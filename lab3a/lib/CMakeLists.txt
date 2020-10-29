project(lab3a)

set(HEADER_FILES
        bigNumber.h
        )

set(SOURCE_FILES
        Prog3.cpp
        )

add_library(lib STATIC ${SOURCE_FILES} ${HEADER_FILES})