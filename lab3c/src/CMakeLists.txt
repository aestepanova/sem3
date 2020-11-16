project(lab3c)

set(HEADER_FILES
        bigNum.h
        )

set(SOURCE_FILES
        bigNum.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})