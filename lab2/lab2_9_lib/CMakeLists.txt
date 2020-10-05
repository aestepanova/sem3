project(lab2)

set(HEADER_FILES
        Lemniscate.h
        )

set(SOURCE_FILES
        Prog2.cpp
        )

add_library(lab2_9_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})