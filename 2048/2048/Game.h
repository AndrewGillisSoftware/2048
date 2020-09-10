#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"

//Change tile.h as well
#define boardSizeX 20
#define boardSizeY 20

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();

	bool newGame();

	bool spawn();

	bool up();
	bool right();
	bool down();
	bool left();

	void display(RenderWindow *window);

	void setBoard(const RenderWindow &window);

	void resizeView(const RenderWindow &window, View &view);

private:
	Text title, t_score, t_direct, t_reset;
	Vector2i emptySqrs[boardSizeX*boardSizeY];
	int score;
	Font font;
	float VIEW_HEIGHT;
	Tile *board[boardSizeX][boardSizeY];
	RectangleShape bBack, background, reset;
	Color theme[20];
	bool gameOver;
};

