project(menu)

set(HEADERS
    source/menu.hpp
    source/menu_functions.hpp
    source/menu_items.hpp
)

set(SOURCES
    main.cpp 
    source/menu_functions.cpp
    source/menu_items.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})