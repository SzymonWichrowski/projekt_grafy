cmake_minimum_required(VERSION 3.25)
project(projekt_grafy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(projekt_grafy main.cpp menu/Menu.cpp menu/Menu.h grafy/GrafLista.cpp grafy/GrafLista.h grafy/GrafMacierz.cpp grafy/GrafMacierz.h narzedzia/UnionFind.cpp narzedzia/UnionFind.h narzedzia/PomiarCzasu.cpp narzedzia/PomiarCzasu.h)
