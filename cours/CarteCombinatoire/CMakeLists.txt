cmake_minimum_required(VERSION 3.0)
project(CarteCombinatoire)

add_executable(CarteCombinatoire main.cpp affichage.cpp carte.cpp point.cpp triangulation.cpp)

# Configuration des options de compilation (par exemple, C++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SDL2_INCLUDE_DIR "C:/Users/Kelvin Idesheim/x86_64-w64-mingw32/include")
set(SDL2_LIB_DIR "C:/Users/Kelvin Idesheim/x86_64-w64-mingw32/lib")

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

# Ajouter l'option de configuration -lSDL2 pour lier à la bibliothèque SDL2
target_link_libraries(CarteCombinatoire "${SDL2_LIB_DIR}/libSDL2main.a" "${SDL2_LIB_DIR}/libSDL2.a" imm32 version winmm setupapi )