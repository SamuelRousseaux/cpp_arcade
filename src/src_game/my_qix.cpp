//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include "my_qix.hpp"
#include <fstream>
#include <ctime>
#include <cstdlib>

MyQix::MyQix()
{
	std::srand(std::time(0));
}

MyQix::~MyQix()
{
}

std::string MyQix::get_asset_path()
{
	return ("./assets/qix");
}

void MyQix::init_game()
{
	_score = 0;
	_vie = 3;
	_win = false;
	_lose = false;
	init_map();
	set_height();
	set_width();
	_player = std::pair<int, int> (_height - 1, _width / 2);
	for (int i = 0; i < 4; i++)
		_BadGuys.push_back(std::pair<int, int> (_height / 2 - i, _width / 2));
}

bool MyQix::loop()
{
	if (!check_win() && !check_lose())
		return true;
	return false;
}

bool MyQix::check_win()
{
	return (_score >= 75);
}

bool MyQix::check_lose()
{
	if (_vie <= 0)
		_lose = true;
	return _lose;
}


std::vector<std::string> MyQix::get_map()
{
	std::vector<std::string> map = _map;

	map[_player.first][_player.second] = 'P';
	for (unsigned int i = 0; i < _BadGuys.size(); i++)
		map[_BadGuys[i].first][_BadGuys[i].second] = 'E';
	return map;
}

int MyQix::get_score()
{
	return _score;
}

void MyQix::quit()
{
	return ;
}

void MyQix::manage_key(Input key)
{
	update_qix();
	move_player(key);
}

void MyQix::check_move(int x, int y)
{
	if ( (y >= 0 && y < _height) &&
	     (move_tentation(x, y, ' ') || move_tentation(x, y, '#'))) {
		move(x, y);
	}
}

void MyQix::move_player(Input Key_test)
{
	int key = Key_test;

	if (key == UP)
		return (check_move(_player.second, _player.first - 1));
	if (key == DOWN)
		return (check_move(_player.second, _player.first + 1));
	if (key == LEFT)
		return (check_move(_player.second - 1, _player.first));
	if (key == RIGHT)
		return (check_move(_player.second + 1, _player.first));
}

void MyQix::clear_trail()
{
	while (_trail.size() > 0)
		_trail.pop_back();
}

std::vector<std::string> MyQix::place_first_diff(int dir, int x, int y)
{
	std::vector<std::string> map = _map;

	for (unsigned int j = 0; j < _BadGuys.size(); j++)
		map[_BadGuys[j].first][_BadGuys[j].second] = 'E';
	if (dir == 0)
		map[y + 1][x] = '0';
	if (dir == 1)
		map[y - 1][x] = '0';
	if (dir == 2)
		map[y][x - 1] = '0';
	if (dir == 3)
		map[y][x + 1] = '0';
	return map;
}

bool MyQix::check_first_diff(int dir, int x, int y)
{
	if (dir == 0)
		return move_tentation(x, y + 1, ' ');
	if (dir == 1)
		return move_tentation(x , y - 1, ' ');
	if (dir == 2)
		return move_tentation(x - 1, y, ' ');
	if (dir == 3)
		return move_tentation(x + 1, y, ' ');
	return false;
}

std::pair<int, int> MyQix::getpos(std::vector<std::string> map)
{
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			if (map[y][x] == '0')
				return std::pair<int, int> (y, x);
		}
	}
	return std::pair<int, int> (0, 0);
}

//replissage

void MyQix::etend(std::pair<int, int> pos)
{
	if (_tmp[pos.first][pos.second] == ' ' && _fill) { //s'il peut placer le 0...
		_tmp[pos.first][pos.second] = 'O';
		etend(std::pair<int, int> (pos.first - 1, pos.second)); //diffuse dans les 4 directions
		etend(std::pair<int, int> (pos.first + 1, pos.second));
		etend(std::pair<int, int> (pos.first, pos.second + 1));
		etend(std::pair<int, int> (pos.first, pos.second - 1));
	} else if (_tmp[pos.first][pos.second] == 'E') { //sinon _fill à false (E c'est le qix
		_fill = false;
	}
}

void MyQix::full()
{
	std::pair<int, int> pos;

	for (unsigned int n = 0; n < _trail.size(); n++) {
		std::pair<int, int> node = _trail[n]; //index sur le chemin du player
		_map[node.first][node.second] = '#';//remplace le chemin par des murs
		for (int i = 0; i < 4; i++) {
			if (check_first_diff(i, _trail[n].second, _trail[n].first)) {
				_fill = true;
				_tmp = place_first_diff(i, _trail[n].second, _trail[n].first);
				pos = getpos(_tmp); // get la position du 0
				_tmp[pos.first][pos.second] = ' ';
				etend(pos);
				if (_fill) {
					for (unsigned int j = 0; j < _BadGuys.size(); j++) 
						_tmp[_BadGuys[j].first][_BadGuys[j].second] = ' ';
					_map = _tmp; // je re set ma map
					break;
				}
			}
		}
	}
}

void MyQix::count_score()
{
	float score = 0;

	for (int y = 1; y < _height - 1; y++) {
		for (int x = 1; x < _width - 1; x++) {
			if (_map[y][x] != ' ')
				score++;
		}
	}
	_score = score / ((_width - 2) * (_height - 2)) * 100;
}

void MyQix::move(int x, int y)
{
	if (move_tentation(_player.second, _player.first, '#') &&
	    move_tentation(x, y, ' '))
		_start_trail = std::pair<int, int> (_player.first, _player.second);
	if (move_tentation(_player.second, _player.first, ' ')) {
		_map[_player.first][_player.second] = 'o';
		_trail.push_back(std::pair<int, int>(_player.first, _player.second));
	}
	if (move_tentation(_player.second, _player.first, 'o') &&
	    move_tentation(x, y, '#')) {
		if (_trail.size() <= 1)
			return;
		full();
		clear_trail();
		count_score();
	}
	_player = std::pair<int, int> (y, x);
}

bool MyQix::move_tentation(int x, int y, char c)
{
	std::vector<std::string> map = _map;

	for (unsigned int j = 0; j < _BadGuys.size(); j++)
		map[_BadGuys[j].first][_BadGuys[j].second] = 'E';
	if (map[y][x] == c)
		return true;
	return false;
}

void MyQix::kill_trail()
{
	for (unsigned int i = 0; i < _trail.size(); i++)
		_map[_trail[i].first][_trail[i].second] = ' ';
	_trail.clear();
	_player = _start_trail;
	_vie--;
}

void MyQix::update_qix()
{
	int rand_dir = std::rand() % 4;

	while (!qix_dir(rand_dir, ' ')) {
		rand_dir = std::rand() % 4;
	}
	for (int i = 0; i < 4; i++) {
		if (qix_dir(i, 'o'))
			kill_trail();

	}
	to_dir(rand_dir);
}

bool MyQix::qix_dir(int dir, char to_check)
{
	std::vector<std::string> map = _map;

	for (unsigned int i = 0; i < _BadGuys.size(); i++)
		map[_BadGuys[i].first][_BadGuys[i].second] = 'E';
	if (dir == 0)
		return (map[_BadGuys[0].first + 1][_BadGuys[0].second] == to_check);
	if (dir == 1)
		return (map[_BadGuys[0].first - 1][_BadGuys[0].second] == to_check);
	if (dir == 2)
		return (map[_BadGuys[0].first][_BadGuys[0].second + 1] == to_check);
	if (dir == 3)
		return (map[_BadGuys[0].first][_BadGuys[0].second - 1] == to_check);
	return false;
}

void MyQix::to_dir(int dir)
{
	if (dir == 0)
		move_qix(_BadGuys[0].first + 1, _BadGuys[0].second);
	if (dir == 1)
		move_qix(_BadGuys[0].first - 1, _BadGuys[0].second);
	if (dir == 2)
		move_qix(_BadGuys[0].first, _BadGuys[0].second + 1);
	if (dir == 3)
		move_qix(_BadGuys[0].first, _BadGuys[0].second - 1);
}

void MyQix::move_qix(int y, int x)
{
	for (int i = _BadGuys.size(); i != 0; --i)
		_BadGuys[i] = _BadGuys[i - 1];
	_BadGuys[0] = std::pair<int, int> (y, x);
}

void MyQix::init_map()
{
	std::string bord = "######################################";
	std::string center = "#                                    #";
	int     i = 0;
	
	_map.push_back(bord);
	while (i != 30)
	{
		_map.push_back(center);
		i++;
	}
	_map.push_back(bord);
}

void MyQix::set_height()
{
	_height = _map.size();
}

void MyQix::set_width()
{
	_width = _map[0].size();
}

extern "C" IGames *maker()
{
	return new MyQix();
}
