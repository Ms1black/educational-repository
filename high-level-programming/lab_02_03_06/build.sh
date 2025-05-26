#!/bin/bash

g++ -o BMSTU_music_app main.cpp Models/*/*.cpp -IModels -IInterfaces && ./BMSTU_music_app