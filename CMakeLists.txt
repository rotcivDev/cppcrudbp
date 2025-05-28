cmake_minimum_required(VERSION 3.10)
project(cppcrudbp)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB MAIN "src/main.cpp")
file(GLOB SOURCES "src/**/*.cpp")
file(GLOB HEADERS "src/**/*.h")

add_executable(cppcrudbp ${MAIN} ${SOURCES})

# Para Debian instale pqxx com cmake
# https://github.com/jtv/libpqxx/blob/master/BUILDING-cmake.md
target_link_libraries(cppcrudbp PRIVATE pqxx pq)

