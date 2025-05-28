cmake_minimum_required(VERSION 3.10)
project(cppcrudbp)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB MAIN "src/main.cpp")
file(GLOB SOURCES "src/**/*.cpp")
file(GLOB HEADERS "src/**/*.h")

add_executable(cppcrudbp ${MAIN} ${SOURCES})

target_link_libraries(cppcrudbp pqxx pq)

