# cpp\_arcade


## Project
Epitech 2nd year project.

Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of
player scores.

To be able to deal with the elements of your gaming plateform at run-time, your graphic libraries and your games must be implemented as dynamic libraries, loaded at runtime.

Each GUI available for the program must be used as a shared library that will be loaded and used dynamically by the main program.



## Prerequisites
To compile and run the project, you will need to install some things :

* SDL2
 * dev
 * image-dev
 * ttf-dev
* Ncurses
* SFML (C++)



## How to use it
To use this program, you first need to compile it using the Makefile :
    
    make re && make clean

Then, just launch it :

    ./arcade [graphic_lib_name.so]

Or use the -h for some informations.
    
    ./arcade -h



## changelog
* 01/05/19 : added files

## contributors
* william.tessari@epitech.eu
* alexandre1.tahery@epitech.eu
