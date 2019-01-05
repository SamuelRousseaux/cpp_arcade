//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include <algorithm>
#include <iostream>
#include <string.h>
#include "sdl.hpp"

Sdl::Sdl() : _running(true)
{
}

void Sdl::init_window()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
        _window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

int Sdl::is_open()
{
	return _running;
}

void Sdl::close_window()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
	TTF_Quit();
}

std::string Sdl::get_pseudo_user(std::string pseudo)
{
	if (_event.type == SDL_TEXTINPUT)
		pseudo += static_cast<char>(*_event.text.text);
	else if (_event.type == SDL_KEYDOWN)
		if (pseudo.size() > 0 &&
			_event.key.keysym.sym == SDLK_BACKSPACE)
			pseudo.pop_back();
	return pseudo;
}

Input Sdl::get_key_pressed()
{
	if (_event.type == SDL_KEYDOWN) {
		switch (_event.key.keysym.sym) {
		case SDLK_UP:
			return UP;
		case SDLK_DOWN:
			return DOWN;
		case SDLK_RIGHT:
			return RIGHT;
		case SDLK_LEFT:
			return LEFT;
		case SDLK_ESCAPE:
			return ESC;
		case SDLK_RETURN:
			return ENTER;
		default:
			return UNDEFINED;
		}
	}
	return UNDEFINED;
}

int Sdl::check_event()
{
	return (SDL_PollEvent(&_event));
}

int Sdl::check_close_window()
{
	if (_event.type == SDL_QUIT)
		return 1;
	return 0;
}

void Sdl::prepare_close_window()
{
	_running = false;
}

void Sdl::display_wd()
{
	SDL_RenderPresent(_renderer);
}

void Sdl::clear_wd()
{
	SDL_RenderClear(_renderer);
}

void Sdl::init_menu()
{
	_image = IMG_Load("./assets/sdl/background.png");
	_font = TTF_OpenFont("./fonts/sdl.ttf", 10);
	_clr_yellow = { 255, 223, 0, 255 };
	_clr_blue = { 18, 73, 128, 255 };
	_clr_lblue = { 64, 255, 255, 255 };
	_texture_img = SDL_CreateTextureFromSurface(_renderer, _image);
}

void Sdl::draw_title_arcade()
{
	SDL_RenderCopy(_renderer, _texture_img, NULL, NULL);

	_rect = { 350, 20, 310, 70 };
	_txt = TTF_RenderText_Solid(_font, "ARCADE", _clr_blue);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);

	_rect = { 350, 20, 300, 60 };
	_txt = TTF_RenderText_Solid(_font, "ARCADE", _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);
}

void Sdl::draw_user(const char *str, Menu_selec selec)
{
	if (selec == USER) {
		_rect = { 20, 250, 155, 35 };
		_txt = TTF_RenderText_Solid(_font, "User name:", _clr_blue);
		_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
		SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
		SDL_FreeSurface(_txt);
		SDL_DestroyTexture(_texture_txt);
	}
	_rect = { 20, 250, 150, 30 };
	_txt = TTF_RenderText_Solid(_font, "User name:", _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);

	_rect = { 700, 250, (int)strlen(str) * 15, 30 };
	_txt = TTF_RenderText_Solid(_font, str, _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);
}

void Sdl::draw_current_lib(const char *str, Menu_selec selec)
{
	if (selec == LIB) {
		_rect = { 20, 300, 155, 35 };
		_txt = TTF_RenderText_Solid(_font, "Current lib:", _clr_blue);
		_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
		SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
		SDL_FreeSurface(_txt);
		SDL_DestroyTexture(_texture_txt);
	}
	_rect = { 20, 300, 150, 30 };
	_txt = TTF_RenderText_Solid(_font, "Current lib:", _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);

	_rect = { 700, 300, (int)strlen(str) * 12, 30 };
	_txt = TTF_RenderText_Solid(_font, str, _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);
}

void Sdl::draw_current_game(const char *str, Menu_selec selec)
{
	if (selec == GAME) {
		_rect = { 20, 350, 155, 35 };
		_txt = TTF_RenderText_Solid(_font, "Current game:", _clr_blue);
		_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
		SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
		SDL_DestroyTexture(_texture_txt);
	}
	_rect = { 20, 350, 150, 30 };
	_txt = TTF_RenderText_Solid(_font, "Current game:", _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);

	_rect = { 700, 350, (int)strlen(str) * 12, 30 };
	_txt = TTF_RenderText_Solid(_font, str, _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);
}

void Sdl::draw_play(Menu_selec selec)
{
	_rect = { 350, 600, 310, 70 };
	_txt = TTF_RenderText_Solid(_font, "PLAY", _clr_blue);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);

	_rect = { 350, 600, 300, 60 };
	if (selec == PLAY)
		_txt = TTF_RenderText_Solid(_font, "PLAY", _clr_lblue);
	else
		_txt = TTF_RenderText_Solid(_font, "PLAY", _clr_yellow);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);
}

void Sdl::draw_highscore(std::string pseudo, int score)
{
	std::string str = "HIGHSCORE: " + pseudo + " - " + std::to_string(score);
	_rect = { 20, 720, (int)strlen(str.c_str()) * 15, 30 };
	_txt = TTF_RenderText_Solid(_font, str.c_str(), _clr_blue);
	_texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
	SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
	SDL_FreeSurface(_txt);
	SDL_DestroyTexture(_texture_txt);
}

void Sdl::init_graphical(std::string path)
{
	FILE *dl;
	char inbuf[1024];
	std::string command = "ls " + path + "/sdl";

        dl = popen(command.c_str(), "r");
	while (fgets(inbuf, 1024, dl)) {
		std::string s = path + "/sdl/" + inbuf;
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		_textures.push_back(s);
	}
	_clr_white = { 255, 255, 255, 255 };
}

int Sdl::get_index(char chr)
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

void Sdl::draw_game(std::vector<std::string> gmap)
{
	SDL_Surface *srfc = nullptr;
	SDL_Texture *txtr = nullptr;
	SDL_Surface *tmp = IMG_Load(_textures[0].c_str());
	SDL_Texture *grass = SDL_CreateTextureFromSurface(_renderer, tmp);
	int index;
	int oldindex = -1;

	for (int y = 0 ; y < (int)gmap.size() ; y++) {
		for (int x = 0 ; x < (int)gmap[y].size() ; x++) {
			index = get_index(gmap[y][x]);
			if (index != -1) {
				if (index != oldindex) {
					if (srfc && txtr) {
						SDL_FreeSurface(srfc);
						SDL_DestroyTexture(txtr);
					}
					srfc = IMG_Load(_textures[index].c_str());
					txtr = SDL_CreateTextureFromSurface(_renderer, srfc);
				}
				_rect = { (x + 1) * 20, (y + 1) * 20, 20, 20 };
				SDL_RenderCopy(_renderer, grass, NULL, &_rect);
				SDL_RenderCopy(_renderer, txtr, NULL, &_rect);
				oldindex = index;
			}
		}
	}
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(grass);
	SDL_FreeSurface(srfc);
	SDL_DestroyTexture(txtr);
	SDL_Delay(50);
}

void Sdl::draw_score(int score)
{
	std::string tmp = "SCORE: " + std::to_string(score);
	const char *str = tmp.c_str();

	_rect = { 0, 0, (int)strlen(str) * 12, 20 };
        _txt = TTF_RenderText_Solid(_font, str, _clr_white);
        _texture_txt = SDL_CreateTextureFromSurface(_renderer, _txt);
        SDL_RenderCopy(_renderer, _texture_txt, NULL, &_rect);
        SDL_FreeSurface(_txt);
        SDL_DestroyTexture(_texture_txt);
}

Event Sdl::get_event()
{
	if (_event.type == SDL_KEYDOWN) {
                switch (_event.key.keysym.sym) {
		case SDLK_a:
			return PREV_GAME;
		case SDLK_z:
			return NEXT_GAME;
		case SDLK_e:
			return PREV_LIB;
		case SDLK_r:
			return NEXT_LIB;
		case SDLK_t:
			return RESTART;
		case SDLK_y:
			return MENU;
		case SDLK_ESCAPE:
			return EXIT;
		default:
			return NO_EVENT;
		}
	}
	return NO_EVENT;
}

extern "C" IGraphical *maker()
{
	return new Sdl;
}
