//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include "IGraphical.hpp"

class Ncurses : public IGraphical
{
public:
	Ncurses();
        void init_window();
        int is_open();
        void close_window();
        Input get_key_pressed();

        int check_event();
        int check_close_window();
        void prepare_close_window();
        void display_wd();
        void clear_wd();

        void init_menu();
        void draw_title_arcade();
        void draw_user(const char *, Menu_selec);
        void draw_current_lib(const char *, Menu_selec);
        void draw_current_game(const char *, Menu_selec);
	void draw_play(Menu_selec);
	void draw_highscore(std::string, int);

	void init_graphical(std::string);
	int get_index(char);
	void draw_game(std::vector<std::string>);
	void draw_score(int);
	Event get_event();

	std::string get_pseudo_user(std::string);

private:
	std::vector<char> _colors;
	int	_key_pressed;
	bool	_running;
	bool	_event;
};
