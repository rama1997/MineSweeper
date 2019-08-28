cmake_minimum_required(VERSION 3.13)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Minesweeper main.cpp game.h game.cpp mainMenu.h mainMenu.cpp Minesweeper.cpp Minesweeper.h)

find_package(SFML 2.5 COMPONENTS REQUIRED system window graphics network audio)
target_link_libraries(Minesweeper sfml-graphics sfml-audio sfml-system sfml-window sfml-graphics sfml-network)