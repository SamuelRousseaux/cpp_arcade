//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include <curses.h>
#include <iostream>
#include <unistd.h>
#include "ncurses.hpp"

Ncurses::Ncurses() : _running(true), _event(true)
{
}

void Ncurses::init_window()
{
	initscr();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
}

int Ncurses::is_open()
{
	return _running;
}

void Ncurses::close_window()
{
	endwin();
}

std::string Ncurses::get_pseudo_user(std::string pseudo)
{
	if (_key_pressed >= 32 && _key_pressed <= 126)
		pseudo += _key_pressed;
	else if (_key_pressed == KEY_BACKSPACE && pseudo.size() > 0) {
		pseudo.pop_back();
		clear();
	}
	return pseudo;
}

Input Ncurses::get_key_pressed()
{
	_key_pressed = getch();

	switch (_key_pressed) {
	case KEY_UP:
		return UP;
	case KEY_DOWN:
		return DOWN;
	case KEY_RIGHT:
		return RIGHT;
	case KEY_LEFT:
		return LEFT;
	case 27:
		return ESC;
	case 10:
		return ENTER;
	default:
		return UNDEFINED;
	}
}

int Ncurses::check_event()
{
	_event = !_event;
	return (_event);
}

int Ncurses::check_close_window()
{
	return 0;
}

void Ncurses::prepare_close_window()
{
	_running = false;
	clear();
}

void Ncurses::display_wd()
{
	refresh();
}

void Ncurses::clear_wd()
{
	clear();
}

void Ncurses::init_menu()
{
}

void Ncurses::draw_title_arcade()
{
	mvprintw(0, (COLS / 2) - 3, "ARCADE");
}

void Ncurses::draw_user(const char *str, Menu_selec selec)
{
	mvprintw(2, 2, "  USER NAME :\t%s", str);
	if (selec == USER)
		mvprintw(2, 2, "*");
}

void Ncurses::draw_current_lib(const char *str, Menu_selec selec)
{
	mvprintw(3, 2, "  GRAPHICS  :\t%s", str);
	if (selec == LIB)
		mvprintw(3, 2, "*");
}

void Ncurses::draw_current_game(const char *str, Menu_selec selec)
{
	mvprintw(4, 2, "  GAME      :\t%s", str);
	if (selec == GAME)
		mvprintw(4, 2, "*");
}

void Ncurses::draw_play(Menu_selec selec)
{
	mvprintw(10, (COLS / 2) - 2, "  PLAY");
	if (selec == PLAY)
		mvprintw(10, (COLS / 2) - 2, "*");
}

void Ncurses::draw_highscore(std::string pseudo, int score)
{
	mvprintw(12, 2, "                                             \
                        ");
	mvprintw(12, 2, "HIGHSCORE: %s - %d", pseudo.c_str(), score);
}

void Ncurses::init_graphical(std::string path)
{
	static_cast<void>(path);
	_colors = { COLOR_BLACK, COLOR_WHITE, COLOR_BLUE, COLOR_BLUE,
		COLOR_RED, COLOR_MAGENTA, COLOR_CYAN, COLOR_YELLOW };

	start_color();
	clear();
	for (int i = 0 ; i < 10 ; i++)
		init_pair(i, _colors[i], _colors[i]);
}

int Ncurses::get_index(char chr)
{
	switch (chr) {
	case VOID:
		return 0;
	case WALL:
		return 1;
	case PLAYER:
		return 2;
	case PLAYER2:
		return 3;
	case ENEMY:
		return 4;
	case ENEMY2:
		return 5;
	case BONUS:
		return 6;
	case BONUS2:
		return 7;
	}
	return -1;
}

void Ncurses::draw_game(std::vector<std::string> gmap)
{
	int index;

	for (size_t y = 0 ; y < gmap.size() ; y++) {
		for (size_t x = 0 ; x < gmap[y].size() ; x++) {
			index = get_index(gmap[y][x]);
			if (index != -1) {
				attron(COLOR_PAIR(index));
				mvprintw(y + 2, x + 2, "%c", gmap[y][x]);
				attroff(COLOR_PAIR(index));
			}
		}
	}
	usleep(90000);
}

void Ncurses::draw_score(int score)
{
	mvprintw(0, 0, "SCORE:                  ");
	mvprintw(0, 0, "SCORE: %d", score);
}

Event Ncurses::get_event()
{
	switch (_key_pressed) {
	case 'a':
		return PREV_GAME;
	case 'z':
		return NEXT_GAME;
	case 'e':
		return PREV_LIB;
	case 'r':
		return NEXT_LIB;
	case 't':
		clear();
		return RESTART;
	case 'y':
		clear();
		return MENU;
	case 27:
		return EXIT;
	}
	return NO_EVENT;
}

extern "C" IGraphical *maker()
{
	return new Ncurses;
}
