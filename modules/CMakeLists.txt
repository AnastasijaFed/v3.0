# Create a static library called studentlib
add_library(studentlib STATIC
        functions.cpp
        functions.h
        StudentClass.cpp
        StudentClass.h
        StudentList.cpp
        StudentList.h
        StudentDeque.cpp
        StudentDeque.h
        Human.cpp
        Human.h
        Vector.cpp
        Vector.h

)

target_include_directories(studentlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
