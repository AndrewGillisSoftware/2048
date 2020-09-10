#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

//Change Game.h as well
#define boardSizeX 4
#define boardSizeY 4

using namespace std;
using namespace sf;

class Tile : public RectangleShape
{
public:
	Tile();
	~Tile();
	
	Tile(Vector2f, Font, Color[], int);

	void display(RenderWindow*);
	void collide();
	void empty();

	Color getColor(int);
	int getValue();
	void setValue(int);

private:
	Vector2f size;
	Font font;
	Text t;
	Color color[20];
	int value;
};

