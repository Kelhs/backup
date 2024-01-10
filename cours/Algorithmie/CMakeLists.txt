cmake_minimum_required(VERSION 3.0)
project(Algorithmie)

add_executable(main main.cpp affichage.cpp enveloppe.cpp point.cpp polygone.cpp)

# Configuration des options de compilation (par exemple, C++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Ajouter l'option de configuration -lSDL2 pour lier à la bibliothèque SDL2
target_link_libraries(main SDL2)