
cmake_minimum_required(VERSION 3.25)

project(proj_geocomp
    DESCRIPTION "Proyecto semestral de geometría compuracional"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE Release)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        "-Wall"
        "-Wextra"
        "-Wpedantic"
    )
endif()

find_package(CGAL REQUIRED)

add_executable(
    poli
    poli.cpp
)

target_link_libraries(
    poli
    CGAL::CGAL
)

