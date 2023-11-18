#!/bin/bash
g++  bouncingball.cpp -o bb.exe -lsfml-graphics -lsfml-window -lsfml-system
#g++ bouncingball.o -o bb -lsfml-graphics -lsfml-window -lsfml-system
#rm ./bouncingball.o
./bb
