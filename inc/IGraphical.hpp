/*
** EPITECH PROJECT, 2018
** Igraphical.hpp
** File description:
** Interface graphical
*/

#ifndef _IGRAPHICAL_HPP_
#define _IGRAPHICAL_HPP_

#include <map>
#include <string>
#include <vector>

enum Menu_selec
{
	USER,
	LIB,
	GAME,
	PLAY
};

enum Input
{
	UNDEFINED = -1,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ENTER,
	ESC
};

enum Event
{
	NO_EVENT = -1,
	PREV_GAME,
	NEXT_GAME,
	PREV_LIB,
	NEXT_LIB,
	RESTART,
	MENU,
	EXIT
};

enum Env
{
	VOID = ' ',
	WALL = '#',
	PLAYER = 'P',
	PLAYER2 = 'p',
	ENEMY = 'e',
	ENEMY2 = 'E',
	BONUS = 'o',
	BONUS2 = 'O'
};

class IGraphical
{
public:
	virtual void init_window()=0;
	virtual int is_open()=0;

	virtual void close_window()=0;
	virtual Input get_key_pressed()=0;
	virtual int check_event()=0;
	virtual int check_close_window()=0;
	virtual void prepare_close_window()=0;

	virtual void display_wd()=0;
	virtual void clear_wd()=0;

	virtual void init_menu()=0;

	virtual void draw_title_arcade()=0;
	virtual void draw_user(const char *, Menu_selec)=0;
	virtual void draw_current_lib(const char *, Menu_selec)=0;
	virtual void draw_current_game(const char *, Menu_selec)=0;
	virtual void draw_play(Menu_selec)=0;
	virtual void draw_highscore(std::string, int)=0;

	virtual std::string get_pseudo_user(std::string)=0;
	// virtual void print_debug()=0;

	virtual void init_graphical(std::string)=0;
	virtual int get_index(char)=0;
	virtual void draw_game(std::vector<std::string>)=0;
	virtual void draw_score(int)=0; // score
	virtual Event get_event()=0;
};

typedef IGraphical  *maker_t();

#endif
