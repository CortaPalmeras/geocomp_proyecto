
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

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        v1.14.0
# )
# FetchContent_MakeAvailable(googletest)
# enable_testing()

find_package(CGAL REQUIRED)

add_library(
    triangulate
    triangulate.cpp
)

target_link_libraries(
    triangulate
    CGAL::CGAL
)

add_executable(
    poli
    poli.cpp
)

target_link_libraries(
    poli
    triangulate
    CGAL::CGAL
)

add_executable(
    mesh
    mesh.cpp
)

target_link_libraries(
    mesh
    CGAL::CGAL
)

