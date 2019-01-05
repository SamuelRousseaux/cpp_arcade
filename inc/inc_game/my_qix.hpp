//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#ifndef QIX_HPP_
# define QIX_HPP_

#include "IGames.hpp"
#include <utility>
#include <vector>

class MyQix : public IGames
{
public:
	MyQix();
	~MyQix();
	void init_game();
	bool loop();
	std::string get_asset_path();
	std::vector<std::string> get_map();
	int get_score();
	void manage_key(Input);
	void quit();
private:
	void update_qix();
	void kill_trail();
	bool qix_dir(int, char);
	void to_dir(int);
	void move_qix(int, int);
	void etend(std::pair<int, int>);
	std::pair<int, int> getpos(std::vector<std::string>);
	std::vector<std::string> place_first_diff(int, int, int);
	bool check_first_diff(int, int, int);
	void clear_trail();
	void full();
	void init_map();
	void set_height();
	void set_width();
	bool check_win();
	bool check_lose();
	void check_move(int, int);
	void move_player(Input);
	void set_map(int, int);
	bool move_tentation(int, int, char);
	void move(int, int);
	void count_score();
	bool _fill;
	int _score;
	int _vie;
	std::vector<std::string> _map;
	std::vector<std::string> _tmp;
	std::pair<int, int> _player;
	std::vector<std::pair<int, int>> _BadGuys;
	std::pair<int, int> _start_trail;
	std::vector<std::pair<int, int>> _trail;
	int _height;
	int _width;
	bool _win;
	bool _lose;
};

#endif /* !QIX_HPP_ */
