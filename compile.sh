#!/bin/bash
g++ -c bouncingball.cpp
g++ bouncingball.o -o bb -lsfml-graphics -lsfml-window -lsfml-system
rm ./bouncingball.o
./bb