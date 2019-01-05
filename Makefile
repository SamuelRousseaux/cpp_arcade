##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile
##

NAME	=	arcade

NCURSES	=	./lib/lib_arcade_ncurses.so

SDL	=	./lib/lib_arcade_sdl.so

SFML	=	./lib/lib_arcade_sfml.so

TEST	=	./games/lib_arcade_test.so

NIBBLER =	./games/lib_arcade_nibbler.so

QIX	=	./games/lib_arcade_qix.so

RM	=	rm -rf

CC	=	g++ -std=c++11

CXXFLAGS=	-W -Wall -Wextra -I./inc -I./inc/inc_game -I./inc/inc_lib \
		-lncurses -fPIC -shared -rdynamic -lsfml-graphics \
		-lsfml-window -lsfml-system -lSDL2 -lSDL2_image -lSDL2_ttf

LDFLAGS	=	-ldl

SRC	=	src/core.cpp	\
		src/main.cpp

OBJ	=	$(SRC:.cpp=.o)

SRC_NCURSES	=	src/src_lib/ncurses.cpp

OBJ_NCURSES	=	$(SRC_NCURSES:.cpp=.o)

SRC_SDL		=	src/src_lib/sdl.cpp

OBJ_SDL		=	$(SRC_SDL:.cpp=.o)

SRC_SFML	=	src/src_lib/sfml.cpp

OBJ_SFML	=	$(SRC_SFML:.cpp=.o)

SRC_TEST	=	src/src_game/test.cpp

SRC_NIBBLER	=	src/src_game/my_snake.cpp

SRC_QIX		=	src/src_game/my_qix.cpp

OBJ_TEST	=	$(SRC_TEST:.cpp=.o)

OBJ_NIBBLER	=	$(SRC_NIBBLER:.cpp=.o)

OBJ_QIX		=	$(SRC_QIX:.cpp=.o)

all:	core graphicals games

core:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) -lncurses

graphicals:	ncurses sfml sdl

ncurses:	$(OBJ_NCURSES)
	$(CC) $(OBJ_NCURSES) $(CXXFLAGS) -o $(NCURSES)

sdl:	$(OBJ_SDL)
	$(CC) $(OBJ_SDL) $(CXXFLAGS) -o $(SDL)

sfml:	$(OBJ_SFML)
	$(CC) $(OBJ_SFML) $(CXXFLAGS) -o $(SFML)

games:	nibbler qix

test:	$(OBJ_TEST)
	$(CC) $(OBJ_TEST) $(CXXFLAGS) -o $(TEST)

nibbler:	$(OBJ_NIBBLER)
	$(CC) $(OBJ_NIBBLER) $(CXXFLAGS) -o $(NIBBLER)

qix:	$(OBJ_QIX)
	$(CC) $(OBJ_QIX) $(CXXFLAGS) -o $(QIX)

clean:
	$(RM) $(OBJ) $(OBJ_NCURSES) $(OBJ_SDL) $(OBJ_SFML) $(OBJ_TEST) $(OBJ_NIBBLER) $(OBJ_QIX)

fclean:	clean
	$(RM) $(NAME) $(NCURSES) $(SDL) $(SFML) $(TEST) $(NIBBLER) $(QIX)

re:	fclean all

.PHONY:	re fclean clean all
