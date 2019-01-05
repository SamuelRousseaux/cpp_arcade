//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#ifndef IGAMES_HPP_
# define IGAMES_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "IGraphical.hpp"

class IGames
{
public:
	virtual void init_game()=0;
	virtual std::string get_asset_path()=0;
	virtual bool loop()=0;
	virtual std::vector<std::string> get_map()=0;
	virtual int get_score()=0;
	virtual void manage_key(Input)=0;
	virtual void quit()=0;
};

typedef IGames	*maker_game_t();

#endif
