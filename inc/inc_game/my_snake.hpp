//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#ifndef MY_SNAKE_HPP_
# define MY_SNAKE_HPP_

#include <curses.h>
#include <list>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "IGames.hpp"

struct	pos_t
{
	int	x;
	int	y;
};

class	MySnake : public IGames
{
public:
	MySnake();
	~MySnake();
	void				add_element_at_back(int x, int y);
	void				add_element_at_front(int x, int y);
	int				get_score();
	int				getLoose();
	void				create_map();
	void				init_game();
	void				mov_forward();
	void				move_left();
	void				move_right();
	void				manage_key(Input);
	bool				loop();
	std::vector<std::string>	get_map();
	void				print_player();
        void				print_obj();
	std::string			get_asset_path();
	void				quit();
private:
	std::list<pos_t>        _snake;
	std::vector<std::string>_map;
	std::vector<std::string>_mapClear;
	int			_direction;
	int			_vit;
	int			_score;
	int			_loose;
};

#endif /* MY_SNAKE_HPP_ !*/
