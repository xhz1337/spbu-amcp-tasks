project(Long_numbers)

set(SOURCES
        long_number.cpp
)

set(HEADERS
        long_number.hpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES}) 