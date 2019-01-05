//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include <iostream>
#include "sfml.hpp"

Sfml::Sfml() : _running(true)
{
}

void Sfml::init_window()
{
	_window.create(sf::VideoMode(1024, 770), "Arcade SFML");
}

int Sfml::is_open()
{
	return _running;
}

void Sfml::close_window()
{
	_window.close();
}

std::string Sfml::get_pseudo_user(std::string pseudo)
{
	if (_event.type == sf::Event::TextEntered) {
		if (_event.text.unicode >= 32 && _event.text.unicode <= 126)
			pseudo += static_cast<char>(_event.text.unicode);
		else if (_event.text.unicode == 8 && pseudo.size() > 0)
			pseudo.pop_back();
	}
	return pseudo;
}

Input Sfml::get_key_pressed()
{
	if (_event.type == sf::Event::KeyPressed) {
		switch (_event.key.code) {
		case sf::Keyboard::Up:
			return UP;
		case sf::Keyboard::Down:
			return DOWN;
		case sf::Keyboard::Right:
			return RIGHT;
		case sf::Keyboard::Left:
			return LEFT;
		case sf::Keyboard::Escape:
			return ESC;
		case sf::Keyboard::Return:
			return ENTER;
		default:
			return UNDEFINED;
		}
	}
	return UNDEFINED;
}

int Sfml::check_event()
{
	return (_window.pollEvent(_event));
}

int Sfml::check_close_window()
{
	if (_event.type == sf::Event::Closed) {
		return 1;
	}
	return 0;
}

void Sfml::prepare_close_window()
{
	_running = false;
}

void Sfml::display_wd()
{
	_window.display();
}

void Sfml::clear_wd()
{
	_window.clear();
}

void Sfml::init_menu()
{
	_font.loadFromFile("./fonts/sfml.ttf");
	_txt.setFont(_font);
	_texture.loadFromFile("./assets/sfml/background.png");
	_sprite.setTexture(_texture);
}

void Sfml::draw_title_arcade()
{
	_txt.setCharacterSize(60);
	_txt.setString("ARCADE");
	_txt.setFillColor(sf::Color(255, 179, 0, 255));
	_txt.setOutlineColor(sf::Color(215, 0, 215, 255));
	_txt.setOutlineThickness(3);
	_txt.setPosition(350, 20);
	_window.draw(_sprite);
	_window.draw(_txt);
}

void Sfml::draw_user(const char *str, Menu_selec selec)
{
	_txt.setCharacterSize(30);
	_txt.setString("User name:");
	_txt.setFillColor(sf::Color::White);
	_txt.setPosition(20, 250);
	if (selec == USER)
		_txt.setOutlineThickness(3);
	else
		_txt.setOutlineThickness(0);
	_window.draw(_txt);
	_txt.setOutlineThickness(0);
	_txt.setCharacterSize(15);
	_txt.setString(str);
	_txt.setPosition(700, 250);
	_window.draw(_txt);
}

void Sfml::draw_current_lib(const char *str, Menu_selec selec)
{
	_txt.setCharacterSize(30);
	_txt.setString("Current lib:");
	_txt.setPosition(20, 300);
	if (selec == LIB)
		_txt.setOutlineThickness(3);
	else
		_txt.setOutlineThickness(0);
	_window.draw(_txt);
	_txt.setOutlineThickness(0);
	_txt.setCharacterSize(15);
	_txt.setString(str);
	_txt.setPosition(700, 300);
	_window.draw(_txt);
}

void Sfml::draw_current_game(const char *str, Menu_selec selec)
{
	_txt.setCharacterSize(30);
	_txt.setString("Current game:");
	_txt.setPosition(20, 350);
	if (selec == GAME)
		_txt.setOutlineThickness(3);
	else
		_txt.setOutlineThickness(0);
	_window.draw(_txt);
	_txt.setOutlineThickness(0);
	_txt.setCharacterSize(15);
	_txt.setString(str);
	_txt.setPosition(700, 350);
	_window.draw(_txt);
}

void Sfml::draw_play(Menu_selec selec)
{
	_txt.setCharacterSize(60);
	_txt.setString("PLAY");
	_txt.setOutlineThickness(3);
	if (selec != PLAY) {
		_txt.setFillColor(sf::Color(255, 179, 0, 255));
		_txt.setOutlineColor(sf::Color(215, 0, 215, 255));
	} else {
		_txt.setFillColor(sf::Color(0, 0, 153, 255));
		_txt.setOutlineColor(sf::Color(255, 204, 255, 255));
	}
	_txt.setPosition(400, 600);
	_window.draw(_txt);
}

void Sfml::draw_highscore(std::string pseudo, int score)
{
	_txt.setCharacterSize(30);
	_txt.setString("HIGHSCORE: " + pseudo + " - " + std::to_string(score));
	_txt.setOutlineThickness(0);
	_txt.setFillColor(sf::Color(255, 255, 255, 255));
	_txt.setPosition(10, 720);
	_window.draw(_txt);
}

void Sfml::init_graphical(std::string path)
{
	FILE *dl;
	char inbuf[1024];
	std::string command = "ls " + path + "/sfml";
	sf::Texture tmp_texture;

	dl = popen(command.c_str(), "r");
	while (fgets(inbuf, 1024, dl)) {
		std::string s = path + "/sfml/" + inbuf;
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		tmp_texture.loadFromFile(s);
		_textures.push_back(tmp_texture);
	}
}

int Sfml::get_index(char chr)
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

void Sfml::draw_game(std::vector<std::string> gmap)
{
	sf::Sprite spr;
	sf::Texture txtr;
	sf::Texture tmp = _textures[0];
	sf::Sprite grass;
	int index;
	int oldindex = -1;

	clear_wd();
	grass.setTexture(tmp);
	grass.setScale(0.15, 0.15);
	for (size_t y = 0 ; y < gmap.size() ; y++) {
		for (size_t x = 0 ; x < gmap[y].size() ; x++) {
			index = get_index(gmap[y][x]);
			if (index != -1) {
				if (index != oldindex) {
					txtr = _textures[index];
					spr.setTexture(txtr);
				}
				spr.setScale(0.15, 0.15);
				spr.setPosition((x + 1) * 19.2, (y + 1) * 19.2);
				grass.setPosition((x + 1) * 19.2, (y + 1) * 19.2);
				_window.draw(grass);
				_window.draw(spr);
				oldindex = index;
			}
		}
	}
	sf::sleep(sf::milliseconds(70));
}

void Sfml::draw_score(int score)
{
	_txt.setCharacterSize(10);
	_txt.setString("SCORE: " + std::to_string(score));
	_txt.setFillColor(sf::Color(255, 255, 255, 255));
	_txt.setOutlineThickness(0);
	_txt.setPosition(0, 0);
	_window.draw(_txt);
}

Event Sfml::get_event()
{
	if (_event.type == sf::Event::KeyPressed) {
		switch (_event.key.code) {
		case sf::Keyboard::A:
			return PREV_GAME;
		case sf::Keyboard::Z:
			return NEXT_GAME;
		case sf::Keyboard::E:
			return PREV_LIB;
		case sf::Keyboard::R:
			return NEXT_LIB;
		case sf::Keyboard::T:
			return RESTART;
		case sf::Keyboard::Y:
			return MENU;
		case sf::Keyboard::Escape:
			return EXIT;
		default:
			return NO_EVENT;
		}
	}
	return NO_EVENT;
}

extern "C" IGraphical *maker()
{
	return new Sfml;
}
