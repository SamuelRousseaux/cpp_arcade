//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include "my_snake.hpp"

MySnake::MySnake()
{
}

MySnake::~MySnake()
{
}

std::string MySnake::get_asset_path()
{
	return ("./assets/nibbler");
}

void	MySnake::init_game()
{
	_direction = 0;
	_vit = 90000;
	_score = 0;
	_loose = false;
	_snake.clear();
	create_map();
	print_player();
	add_element_at_back(12, 12);
	add_element_at_back(12, 13);
	add_element_at_back(12, 14);
	add_element_at_back(12, 15);
}

void	MySnake::create_map()
{
	std::string bord = "######################################";
	std::string center = "#                                    #";
	int	i = 0;

	_map.clear();
	_map.push_back(bord);
	while (i != 30)
	{
		_map.push_back(center);
		i++;
	}
	_map.push_back(bord);
	_mapClear = _map;
}

std::vector<std::string>	MySnake::get_map()
{
	_map = _mapClear;
	print_player();
	print_obj();
	return _map;
}

void MySnake::add_element_at_back(int x, int y)
{
	pos_t	temp;

	temp.x = x;
	temp.y = y;
	_snake.push_back(temp);
}

void MySnake::add_element_at_front(int x, int y)
{
	pos_t	temp;

	temp.x = x;
	temp.y = y;
	_snake.push_front(temp);
}

void	MySnake::mov_forward()
{
	auto it = _snake.begin();
	if (_direction == 0)
		add_element_at_front(it->x + 1, it->y);
	else if (_direction == 1)
		add_element_at_front(it->x, it->y - 1);
	else if (_direction == 2)
		add_element_at_front(it->x - 1, it->y);
	else if (_direction == 3)
		add_element_at_front(it->x, it->y + 1);
	_snake.pop_back();
}

void MySnake::print_player()
{
	auto it = _snake.begin();
	_map[it->y][it->x] = 'P';
	it++;
	while (it != _snake.end())
	{
		_map[it->y][it->x] = 'p';
		it++;
	}
}

void MySnake::move_left()
{
	auto it = _snake.begin();
	if (_direction == 0)
	{
		add_element_at_front(it->x, it->y - 1);
		_direction = 1;
	}
	else if (_direction == 1)
	{
		add_element_at_front(it->x - 1, it->y);
		_direction = 2;
	}
	else if (_direction == 2)
	{
		add_element_at_front(it->x, it->y + 1);
		_direction = 3;
	}
	else if (_direction == 3)
	{
		add_element_at_front(it->x, it->y + 1);
		_direction = 0;
	}
	_snake.pop_back();
}

void MySnake::move_right()
{
	auto it = _snake.begin();
	if (_direction == 0)
	{
		add_element_at_front(it->x, it->y + 1);
		_direction = 3;
	}
	else if (_direction == 1)
	{
		add_element_at_front(it->x + 1, it->y);
		_direction = 0;
	}
	else if (_direction == 2)
	{
		add_element_at_front(it->x - 1, it->y);
		_direction = 1;
	}
	else if (_direction == 3)
	{
		add_element_at_front(it->x - 1, it->y);
		_direction = 2;

	}
	_snake.pop_back();
}

void MySnake::manage_key(Input input)
{
	if (input == LEFT)
		move_left();
	else if (input == RIGHT)
		move_right();
	else
		mov_forward();
}

bool	MySnake::loop()
{
	auto it = _snake.begin();

	int	x = (COLS / 2) - 18;
	int	y = (LINES / 2) - 15;

	if (it->x == 0 || it->x == (int)(_map[0].size() - 1)) {
		_loose = true;
		return false;
	}
	if (it->y == 0 || it->y == (int)(_map.size() - 1)) {
		_loose = true;
		return false;
	}
	x = it->x;
	y = it->y;
	it++;
	for (it = it;it != _snake.end(); it++)
		if (it->x == x && it->y == y) {
			_loose = true;
			return false;
		}
	return (true);
}

void	MySnake::print_obj()
{
	static int	i = 0;
	static pos_t    temp;
	auto it = _snake.begin();

	if (it->y == temp.y && it->x == temp.x && i == 1) {
		it = _snake.end();
		if (_direction == 0)
			add_element_at_back(it->x - 1, it->y);
		if (_direction == 1)
			add_element_at_back(it->x, it->y + 1);
		if (_direction == 2)
			add_element_at_back(it->x + 1, it->y);
		if (_direction == 3)
			add_element_at_back(it->x, it->y - 1);
		i = 0;
		_score += 20;
	}
	if (i == 0) {
		srand(time(NULL));
		temp.x = (rand() % (35 - 1)) + 1;
		temp.y = (rand() % (30 - 1)) + 1;
		i = 1;
	}
	_map[temp.y][temp.x] = 'o';
}

int	MySnake::get_score()
{
	return _score;
}

int	MySnake::getLoose()
{
	return _loose;
}

void	MySnake::quit()
{
}

extern "C" IGames *maker()
{
	return new MySnake();
}
