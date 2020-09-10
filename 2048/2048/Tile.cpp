#include "stdafx.h"
#include "Tile.h"



Tile::Tile()
{
}


Tile::~Tile()
{
}

Tile::Tile(Vector2f s, Font f, Color c[], int v)
{
	size = s;
	font = f;
	for (int i = 0; i < 20; i++)
	{
		color[i] = c[i];
	}
	value = v;

	setSize(size);
	setFillColor(color[2]);

	t.setFont(font);
	t.setString(to_string(value));
	t.setCharacterSize(getSize().x/2);
	t.setFillColor(color[3]);
	t.setStyle(Text::Bold);
	
}

void Tile::display(RenderWindow *window)
{
	if (value == 0)
	{
		setFillColor(color[2]);
		window->draw(*this);
	}
	else
	{
		setFillColor(getColor(value));
		t.setPosition(getPosition().x + getSize().x/3, getPosition().y + getSize().y/5);
		window->draw(*this);
		window->draw(t);
	}
}

void Tile::collide()
{
	value += value;

	if (value > 4)
	{
		t.setFillColor(color[4]);
	}
	else
	{
		t.setFillColor(color[3]);
	}
	t.setString(to_string(value));
}

void Tile::empty()
{
	value = 0;
}

//4 - 20
Color Tile::getColor(int v)
{
	switch (v)
	{
	case 2:
		return color[4];
		break;
	case 4:
		return color[5];
		break;
	case 8:
		return color[6];
		break;
	case 16:
		return color[7];
		break;
	case 32:
		return color[8];
		break;
	case 64:
		return color[9];
		break;
	case 128:
		return color[10];
		break;
	case 256:
		return color[11];
		break;
	case 512:
		return color[12];
		break;
	case 1024:
		return color[13];
		break;
	case 2048:
		return color[14];
		break;
	case 4096:
		return color[15];
		break;
	case 8192:
		return color[16];
		break;
	case 16384:
		return color[17];
		break;
	case 32768:
		return color[18];
		break;
	case 65536:
		return color[19];
		break;
	case 131072:
		return color[20];
		break;
	}

}

int Tile::getValue()
{
	return value;
}

void Tile::setValue(int v)
{
	value = v;
	t.setString(to_string(value));
	if (value > 4)
	{
		t.setFillColor(color[4]);
	}
	else
	{
		t.setFillColor(color[3]);
	}
}
