//
// EPITECH PROJECT, 2018
// *
// File description:
// *
//

#include <algorithm>
#include <cstdlib>
#include <dlfcn.h>
#include <ncurses.h>
#include <fstream>
#include "core.hpp"

Core::Core(std::string lib_name) :
	_selection(0), _current_lib(lib_name), _pseudo("name")
{
	dlib_lib = nullptr;
	dlib_game = nullptr;
	fillVector(_games, "games");
	_current_game = _games[0];
	fillVector(_libs, "lib");
	setLib(CURRENT);
	setGame(CURRENT);
	showMenu();
}

void Core::switchLib(int mode)
{
	if (_selection == LIB) {
		_lib->close_window();
		setLib(mode);
		showMenu();
	} else if (_selection == GAME)
		setGame(mode);
}

void Core::switchIngame(int opt, int mode)
{
	if (opt == PREV_GAME || opt == NEXT_GAME) {
		writeHighscore();
		_game->quit();
		setGame(mode);
		gameLoop();
	} else if (opt == PREV_LIB || opt == NEXT_LIB) {
		_lib->close_window();
		setLib(mode);
		_lib->init_window();
		_lib->init_menu();
		_lib->init_graphical(_game->get_asset_path());
	}
}

void Core::selectEvent()
{
	switch (_key) {
	case PREV_GAME:
		switchIngame(_key, PREV);
		break;
	case NEXT_GAME:
		switchIngame(_key, NEXT);
		break;
	case PREV_LIB:
		switchIngame(_key, PREV);
		break;
	case NEXT_LIB:
		switchIngame(_key, NEXT);
		break;
	case RESTART:
		gameLoop();
		break;
	case MENU:
		showMenu();
		break;
	case EXIT:
		_lib->prepare_close_window();
		break;
	default:
		break;
	}
}

void Core::getGameEvent()
{
	_lib->check_event();
	if (_lib->check_close_window())
		_lib->prepare_close_window();
	_key = _lib->get_key_pressed();
	_game->manage_key(static_cast<Input>(_key));
	_key = _lib->get_event();
	selectEvent();
}

void Core::gameLoop()
{
	_lib->clear_wd();
	_lib->display_wd();
	_game->init_game();
	_lib->init_graphical(_game->get_asset_path());
	while (_game->loop() && _lib->is_open()) {
		_lib->clear_wd();
		_lib->draw_game(_game->get_map());
		_lib->draw_score(_game->get_score());
		getGameEvent();
		_lib->display_wd();
	}
	_lib->clear_wd();
	_lib->display_wd();
	writeHighscore();
	_game->quit();
}

void Core::selectOption()
{
	int input = _lib->get_key_pressed();

	switch (input) {
	case UP:
		_selection = (_selection - 1 < 0) ? 3 : _selection - 1;
		break;
	case DOWN:
		_selection = (_selection + 1 > 3) ? 0 : _selection + 1;
		break;
	case RIGHT:
	        switchLib(NEXT);
		break;
	case LEFT:
	        switchLib(PREV);
		break;
	case ESC:
		_lib->prepare_close_window();
		break;
	case ENTER:
		if (_selection == PLAY)
			gameLoop();
		break;
	default:
		break;
	}
}

void Core::getEvent()
{
	while (_lib->check_event()) {
		if (_lib->check_close_window())
			_lib->prepare_close_window();
		selectOption();
		if (_selection == USER)
			_pseudo = _lib->get_pseudo_user(_pseudo);
	}
}

void Core::writeHighscore()
{
	int score = _game->get_score();
	std::string path = "./scores/" + getGameName();
	std::ofstream ofs(path, std::ofstream::out | std::ofstream::app);

	ofs << _pseudo << " " << score << "\n";
	ofs.close();
}

void Core::getHighscore()
{
	std::string path = "./scores/" + getGameName();
	std::ifstream ifs (path, std::ifstream::in);
	std::string line;
	std::string tmp;

	_hs_score = 0;
	_hs_name = "_";
	while (std::getline(ifs, line)) {
		if (line.size() > 1) {
			tmp = line.substr(line.find(" ") + 1, line.size());
			if (std::stoi(tmp) > _hs_score) {
				_hs_score = std::stoi(tmp);
				_hs_name = line.substr(0, line.find(" "));
			}
		}
	}
	ifs.close();
}

void Core::drawMenu()
{
	Menu_selec selec = static_cast<Menu_selec>(_selection);
	_lib->draw_title_arcade();
	_lib->draw_user(_pseudo.c_str(), selec);
	_lib->draw_current_lib(_current_lib.c_str(), selec);
	_lib->draw_current_game(_current_game.c_str(), selec);
	_lib->draw_play(selec);
	getHighscore();
	_lib->draw_highscore(_hs_name, _hs_score);
}

void Core::showMenu()
{
	_lib->init_window();
	_lib->init_menu();

	while (_lib->is_open()) {
		drawMenu();
		getEvent();
		_lib->display_wd();
	}
	_lib->close_window();
}

void Core::setGame(int mode)
{
        auto it = std::find(_games.begin(), _games.end(), _current_game);
	if (it != _libs.end()) {
		if (mode == NEXT)
		        it = (it + 1 == _games.end()) ? _games.begin() : it + 1;
		else if (mode == PREV)
		        it = (it == _games.begin()) ? _games.end() - 1 : it - 1;
		_current_game = *it;
		loadGame();
	} else {
		std::cerr << "ERROR: no \"" << _current_game << "\" found\n";
		std::exit(84);
	}
}

void Core::setLib(int mode)
{
	auto it = std::find(_libs.begin(), _libs.end(), _current_lib);
	if (it != _libs.end()) {
		if (mode == NEXT)
		        it = (it + 1 == _libs.end()) ? _libs.begin() : it + 1;
		else if (mode == PREV)
		        it = (it == _libs.begin()) ? _libs.end() - 1 : it - 1;
		_current_lib = *it;
		loadLib();
	} else {
		std::cerr << "ERROR: no \"" << _current_lib << "\" found\n";
		std::exit(84);
	}
}

void Core::loadLib()
{
	std::string name = "./" + _current_lib;

	if (dlib_lib != nullptr)
		if (dlclose(dlib_lib) != 0) {
			std::cout << "Error while closing lib" << std::endl;
			std::exit(84);
		}
	dlib_lib = dlopen(name.c_str(), RTLD_NOW);
	if (dlib_lib == nullptr) {
		std::cout << dlerror() << std::endl;
		std::exit(84);
	}
	maker_t *lib_maker = (maker_t *)dlsym(dlib_lib, "maker");
	if (dlerror() != nullptr) {
		std::cout << "Error while making lib" << std::endl;
		std::exit(84);
	}
	_lib = lib_maker();
}

void Core::loadGame()
{
	std::string name =  "./" + _current_game;

	getGameName();
	if (dlib_game != nullptr)
		if (dlclose(dlib_game) != 0) {
			std::cerr << "Error while closing game" << std::endl;
			std::exit(84);
		}
	dlib_game = dlopen(name.c_str(), RTLD_NOW);
	if (dlib_game == nullptr) {
		std::cerr << dlerror() << std::endl;
		std::exit(84);
	}
	maker_game_t *game_maker = (maker_game_t *)dlsym(dlib_game, "maker");
	if (dlerror() != nullptr) {
		std::cerr << "Error while making game" << std::endl;
		std::exit(84);
	}
	_game = game_maker();
}

int Core::closeLibs()
{
	if (dlib_lib != nullptr)
		if (dlclose(dlib_lib) != 0)
			return 84;
	if (dlib_game != nullptr)
		if (dlclose(dlib_game) != 0)
			return 84;
	return 0;
}

std::string Core::getGameName()
{
	std::string name;

	name = _current_game.substr(17, _current_game.length() - 20);
	return name;
}

void Core::fillVector(std::vector<std::string> &vector, std::string path)
{
	FILE *dl;
	char inbuf[1024];
	std::string command = "find " + path + " -name \"*.so\"";

	dl = popen(command.c_str(), "r");
	while (fgets(inbuf, 1024, dl)) {
		std::string s = inbuf;
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		vector.push_back(s);
	}
}
