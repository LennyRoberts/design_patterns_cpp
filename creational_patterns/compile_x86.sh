#!/bin/bash

echo "Compile Start..."
if [ -f "run_x86.sh" ]; then
    sudo rm ./run_x86.sh
fi

echo "g++ *.cpp -lpthread -lm -o run_x86.o ..."
g++ *.cpp -lpthread -lm -o run_x86.o

if [ -f "run_x86.o" ]; then
    echo "Compile Success with run_x86"
else
    echo "Compile Failed!!!"
fi

echo "Compile END!"