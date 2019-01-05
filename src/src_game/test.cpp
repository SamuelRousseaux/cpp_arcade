//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include "test.hpp"

Test::Test() :  _asset_path("./assets/test")
{
}

void Test::init_game()
{
	_map = { { "########" },
		 { "#      #" },
		 { "#  P   #" },
		 { "#      #" },
		 { "########" }};
	_looping = true;
	_xpos = 3;
	_ypos = 2;
	_score = 0;
}

std::string Test::get_asset_path()
{
	return _asset_path;
}

bool Test::loop()
{
	return _looping;
}

std::vector<std::string> Test::get_map()
{
	return _map;
}

int Test::get_score()
{
	return _score;
}

void Test::manage_key(Input input)
{
	switch (input) {
	case UP:
		if (_map[_ypos-1][_xpos] != '#') {
			_map[_ypos][_xpos] = ' ';
			_ypos--;
			_map[_ypos][_xpos] = 'P';
		}
		break;
	case DOWN:
		if (_map[_ypos+1][_xpos] != '#') {
			_map[_ypos][_xpos] = ' ';
			_ypos++;
			_map[_ypos][_xpos] = 'P';
		}
		break;
	case RIGHT:
		if (_map[_ypos][_xpos+1] != '#') {
			_map[_ypos][_xpos] = ' ';
			_xpos++;
			_map[_ypos][_xpos] = 'P';
		}
		break;
	case LEFT:
		if (_map[_ypos][_xpos-1] != '#') {
			_map[_ypos][_xpos] = ' ';
			_xpos--;
			_map[_ypos][_xpos] = 'P';
		}
		break;
	case ENTER:
		_score++;
		break;
	default:
		break;
	}
}

void Test::quit()
{
}

extern "C" IGames *maker()
{
	return new Test;
}
