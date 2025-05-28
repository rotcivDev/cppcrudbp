cmake_minimum_required(VERSION 3.10)
project(cppcrudbp VERSION 1.0 LANGUAGES CXX)
# Definindo o padrão C++ para C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opções de compilador
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Configuração de build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Configuração do diretório de saída
include_directories(include)
file(GLOB MAIN "src/main.cpp")
file(GLOB SOURCES "src/**/*.cpp")
file(GLOB HEADERS "include/**/*.h")
add_executable(cppcrudbp ${MAIN} ${SOURCES})

# Para Debian instale pqxx com cmake
# https://github.com/jtv/libpqxx/blob/master/BUILDING-cmake.md
target_link_libraries(cppcrudbp PRIVATE pqxx pq)

