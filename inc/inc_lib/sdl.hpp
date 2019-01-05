//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "IGraphical.hpp"

class Sdl : public IGraphical
{
public:
	Sdl();
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

	std::string get_pseudo_user(std::string pseudo);

private:
	SDL_Window	*_window;
	SDL_Rect	_rect;
	SDL_Renderer	*_renderer;
	SDL_Event	_event;
	SDL_Surface	*_image;
	SDL_Surface	*_txt;
	SDL_Color	_clr_yellow;
	SDL_Color	_clr_blue;
	SDL_Color	_clr_lblue;
	SDL_Color	_clr_white;
	TTF_Font	*_font;
	SDL_Texture	*_texture_img;
	SDL_Texture	*_texture_txt;
	std::vector<std::string> _textures;
	int	_key_pressed;
	bool	_running;
};
