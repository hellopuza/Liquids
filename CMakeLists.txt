cmake_minimum_required(VERSION 3.22)

project(Liquids)

if (NUMBERS)
    add_definitions(-DNUMBERS)
endif()

if (SHOW_TUBES)
    add_definitions(-DSHOW_TUBES)
endif()

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

set_target_properties(main PROPERTIES
    CXX_STANDARD          20
    CXX_STANDARD_REQUIRED ON
)

add_executable(gen generator.cpp)
target_include_directories(gen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

set_target_properties(gen PROPERTIES
    CXX_STANDARD          20
    CXX_STANDARD_REQUIRED ON
)