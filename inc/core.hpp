//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#ifndef CORE_HPP_
# define CORE_HPP_

#include <iostream>
#include <vector>
#include "IGraphical.hpp"
#include "IGames.hpp"

# define CURRENT	0
# define NEXT		1
# define PREV		-1

class Core
{
public:
	Core(std::string lib_name);

	void setGame(int);
	void setLib(int);

	void switchLib(int);
	void switchIngame(int, int);
	void selectOption();
	void getEvent();
	void writeHighscore();
	void getHighscore();
	void drawMenu();
	void showMenu();

	void gameLoop();
	void selectEvent();
	void getGameEvent();

	void loadLib();
	void loadGame();
	int closeLibs();
	std::string getGameName();
	void fillVector(std::vector<std::string> &, std::string);
private:
	int _key;
	int _selection;
	IGraphical *_lib;
	IGames *_game;
	std::string _current_game;
	std::string _current_lib;
	std::string _pseudo;
	std::vector<std::string> _games;
	std::vector<std::string> _libs;
	void *dlib_lib;
	void *dlib_game;
	std::string _hs_name;
	int _hs_score;
};

#endif
