project(lab3a)

set(HEADER_FILES
        bigNumber.h
        )

set(SOURCE_FILES
        Prog3.cpp
        Prog3a_char.cpp bigNum_char.h)

add_library(lib STATIC ${SOURCE_FILES} ${HEADER_FILES})