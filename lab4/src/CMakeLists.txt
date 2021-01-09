project(lab4)

set(HEADER_FILES
        Guest.h
        Luxe.h
        Unary.h
        Multi.h
        Table.h
        Suite.h
        Vector.h
        Table2.h
        )

set(SOURCE_FILES
        Luxe.cpp
        Unary.cpp
        Multi.cpp
        Suite.cpp other_vector.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})