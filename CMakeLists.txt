cmake_minimum_required(VERSION 3.30)
project(3d_treasure_game)

set(CMAKE_CXX_STANDARD 11)

add_executable(3d_treasure_game src/main.cpp
        src/game/Board.cpp
        src/game/Board.h
        src/game/Game.cpp
        src/game/Game.h
        src/structures/OrthogonalList.h
        src/structures/RandomList.h
        src/utils/CellContent.h)
