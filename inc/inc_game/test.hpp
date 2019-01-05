//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#ifndef TEST_HPP_
# define TEST_HPP_

#include "IGames.hpp"

class Test : public IGames
{
public:
	Test();
	void init_game();
	std::string get_asset_path();
	bool loop();
	std::vector<std::string> get_map();
	int get_score();
	void manage_key(Input);
	void quit();
private:
	std::vector<std::string>	_map;
	std::string	_asset_path;
	bool	_looping;
	int	_xpos;
	int	_ypos;
	int	_score;
};

#endif
