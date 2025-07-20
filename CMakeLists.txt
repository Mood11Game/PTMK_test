cmake_minimum_required(VERSION 3.10)

project(PTMK_TEST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(
    ${PQXX_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

link_directories(${PQXX_LIBRARY_DIRS})

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(PTMK_TEST ${SOURCES})

target_link_libraries(PTMK_TEST ${PQXX_LIBRARIES})
