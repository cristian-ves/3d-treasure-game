#!/bin/bash
g++ src/Main.cpp src/game/Board.cpp src/game/Game.cpp -o Main

# condition to check if last exit status is 0 -> executer succesfully 
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running the program..."
    ./Main
else
    echo "Compilation failed!"
fi

# get permission of execution (only once )
#chmod +x execute.sh