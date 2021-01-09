project(lab4)

set(HEADER_FILES
        Guest.h
        Luxe.h
        Unary.h
        Multi.h
        Table.h
        Suite.h
        my_vec.h
        ../Table2.h
        )

set(SOURCE_FILES
        Luxe.cpp
        Unary.cpp
        Multi.cpp
        Suite.cpp)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})