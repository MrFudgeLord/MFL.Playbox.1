cmake_minimum_required(VERSION 3.20)
project(MFL.Playbox.1 CXX)

file(GLOB_RECURSE SOURCES
    src/*/*.cpp
    #src/*/*.hpp
    #include/*.hpp
)

add_executable(Playbox src/main.cpp ${SOURCES})

target_compile_options(Playbox PRIVATE
    -masm=intel
    -march=alderlake
    -Wno-c++17-extensions
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set_target_properties(Playbox PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

include_directories(include)
link_directories(lib)

target_link_libraries(Playbox D:/source/repos/MFL.Playbox.1/lib/SDL3.lib)