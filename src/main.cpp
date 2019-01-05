//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// main
//

#include <iostream>
#include "arcade.hpp"
#include "core.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << HELP;
		return (84);
	}
	Core arcade_core(argv[1]);
	if (arcade_core.closeLibs() == 84)
		return (84);
	return (0);
}
