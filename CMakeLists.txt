cmake_minimum_required(VERSION 3.20)
project(Playbox.1 CXX)

file(GLOB_RECURSE SOURCES
    src/*/*.cpp
    #src/*/*.hpp
    #include/*.hpp
)

add_executable(Playbox src/main.cpp ${SOURCES})

target_compile_options(Playbox PRIVATE
    -masm=intel
    -std=c++26
)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
link_directories(lib)

target_link_libraries(Playbox "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3.lib")