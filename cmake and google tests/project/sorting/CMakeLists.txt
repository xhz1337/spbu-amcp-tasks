project(sort)

set(HEADERS
    source/generate.hpp
    source/io.hpp
    source/sortings.hpp
)

set(SOURCES
    main.cpp 
    source/generate.cpp
    source/io.cpp
    source/sortings.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES}) 

add_subdirectory(tests)