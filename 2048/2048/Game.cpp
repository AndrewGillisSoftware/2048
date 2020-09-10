#include "stdafx.h"
#include "Game.h"
#include <time.h>   

Game::Game()
{
	VIEW_HEIGHT = 512;
	//sets color theme

	//background Color
	theme[0] = Color(250, 248, 239);
	//back board Color
	theme[1] = Color(187, 173, 160);
	//empty tile color
	theme[2] = Color(205, 193, 180);
	//title text color
	theme[3] = Color(119, 110, 101);
	// 2 color 
	theme[4] = Color(238, 228, 218);
	// 4 color
	theme[5] = Color(236, 224, 200);
	// 8 color 
	theme[6] = Color(243, 176, 121);
	// 16 color 
	theme[7] = Color(246, 148, 99);
	// 32 color
	theme[8] = Color(245, 124, 95);
	// 64 color 
	theme[9] = Color(246, 93, 61);
	// 128 color
	theme[10] = Color(238, 207, 114);
	// 256 color 
	theme[11] = Color(237, 204, 97);
	// 512 color
	theme[12] = Color(236, 200, 80);
	// 1024 color
	theme[13] = Color(237, 197, 63);
	// 2048 color
	theme[14] = Color(251, 197, 45);
	// 4096 color
	theme[15] = Color(244, 102, 118);
	// 8192 color
	theme[16] = Color(243, 75, 92);
	// 16384 color
	theme[17] = Color(195, 58, 48);
	// 32768 color
	theme[18] = Color(111, 184, 217);
	// 65536 color
	theme[19] = Color(93, 160, 228);
	// 131072 color
	theme[20] = Color(0, 127, 194);

	score = 0;
	gameOver = false;
}


Game::~Game()
{
}

bool Game::newGame()
{
	RenderWindow window(VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "2048", Style::Fullscreen);
	View view(Vector2f(window.getSize().x / 2, window.getSize().y / 2), Vector2f(window.getSize()));

	FloatRect r;
	Vector2i lP;
	score = 0;
	gameOver = false;

	srand(time(NULL));

	setBoard(window);

	spawn();
	spawn();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			if (event.type == Event::Resized)
			{
				resizeView(window, view);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				lP = Mouse::getPosition(window);
				r = reset.getGlobalBounds();
				if (r.contains((Vector2f)lP))
				{
					return true;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) && !gameOver)
			{
				if (up())
				{
					if (!spawn())
					{
						gameOver = true;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) && !gameOver)
			{
				if (right())
				{
					if (!spawn())
					{
						gameOver = true;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && !gameOver)
			{
				if (down())
				{
					if (!spawn())
					{
						gameOver = true;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && !gameOver)
			{
				if (left())
				{
					if (!spawn())
					{
						gameOver = true;
					}
				}
			}
		}

		view.setCenter(window.getSize().x/2, window.getSize().y/2);
		window.setView(view);

		window.clear();
		display(&window);
		window.display();
	}
	return false;
}

bool Game::spawn()
{
	int cE = 0, value;
	Vector2i spawnLoc;
	//empty
	for (int i = 0; i < boardSizeX*boardSizeY; i++)
	{
		emptySqrs[i] = Vector2i(NULL, NULL);
	}

	//find all 0s
	for (int y = 0; y < boardSizeY; y++)
	{
		for (int x = 0; x < boardSizeX; x++)
		{
			if (board[x][y]->getValue() == 0)
			{
				emptySqrs[cE] = Vector2i(x, y);
				cE++;
			}
		}
	}
	if (cE == 0)
	{
		return false;
	}
	value = (rand() % 2 + 1) * 2;
	spawnLoc = emptySqrs[rand() % cE];
	board[spawnLoc.x][spawnLoc.y]->setValue(value);
	return true;
}

bool Game::up()
{
	bool r = false;
	//pull
	for (int i = 0; i < boardSizeY; i++)
	{
		for (int y = 0; y < boardSizeY - 1; y++)
		{
			for (int x = 0; x < boardSizeX; x++)
			{
				if (board[x][y]->getValue() == 0)
				{
					if (board[x][y + 1]->getValue() != 0)
					{
						board[x][y]->setValue(board[x][y + 1]->getValue());
						board[x][y + 1]->empty();
						r = true;
					}
				}
			}
		}
	}
	//combine
	for (int y = 0; y < boardSizeY - 1; y++)
	{
		for (int x = 0; x < boardSizeX; x++)
		{
			if (board[x][y]->getValue() != 0)
			{
				if (board[x][y + 1]->getValue() == board[x][y]->getValue())
				{
					board[x][y]->collide();
					score += board[x][y]->getValue();
					board[x][y + 1]->empty();
					r = true;
				}
			}
		}
	}
	//pull
	for (int i = 0; i < boardSizeY; i++)
	{
		for (int y = 0; y < boardSizeY - 1; y++)
		{
			for (int x = 0; x < boardSizeX; x++)
			{
				if (board[x][y]->getValue() == 0)
				{
					if (board[x][y + 1]->getValue() != 0)
					{
						board[x][y]->setValue(board[x][y + 1]->getValue());
						board[x][y + 1]->empty();
						r = true;
					}
				}
			}
		}
	}
	return r;
}

bool Game::right()
{
	bool r = false;
	//pull
	for (int i = boardSizeX; i > 0; i--)
	{
		for (int y = boardSizeY;  y > 0; y--)
		{
			for (int x = boardSizeX - 1; x > 0; x--)
			{
				if (board[x][y]->getValue() == 0)
				{
					if (board[x - 1][y]->getValue() != 0)
					{
						board[x][y]->setValue(board[x - 1][y]->getValue());
						board[x - 1][y]->empty();
						r = true;
					}
				}
			}
		}
	}
	//combine
	for (int y = boardSizeY; y >= 0; y--)
	{
		for (int x = boardSizeX - 1; x > 0; x--)
		{
			if (board[x][y]->getValue() != 0)
			{
				if (board[x - 1][y]->getValue() == board[x][y]->getValue())
				{
					board[x][y]->collide();
					score += board[x][y]->getValue();
					board[x - 1][y]->empty();
					r = true;
				}
			}
		}
	}
	//pull
	for (int i = boardSizeX; i > 0; i--)
	{
		for (int y = boardSizeY; y > 0; y--)
		{
			for (int x = boardSizeX - 1; x > 0; x--)
			{
				if (board[x][y]->getValue() == 0)
				{
					if (board[x - 1][y]->getValue() != 0)
					{
						board[x][y]->setValue(board[x - 1][y]->getValue());
						board[x - 1][y]->empty();
						r = true;
					}
				}
			}
		}
	}
	return r;
}

bool Game::down()
{
	bool r = false;
	//pull
	for (int i = boardSizeY; i > 0; i--)
	{
		for (int y = boardSizeY - 1; y > 0; y--)
		{
			for (int x = boardSizeX - 1; x >= 0; x--)
			{

				if (board[x][y]->getValue() == 0)
				{
					if (board[x][y - 1]->getValue() != 0)
					{
						board[x][y]->setValue(board[x][y - 1]->getValue());
						board[x][y - 1]->empty();
						r = true;
					}
				}
			}
		}
	}
	//combine
	for (int y = boardSizeY - 1; y > 0; y--)
	{
		for (int x = boardSizeX - 1; x >= 0; x--)
		{
			if (board[x][y]->getValue() != 0)
			{
				if (board[x][y - 1]->getValue() == board[x][y]->getValue())
				{
					board[x][y]->collide();
					score += board[x][y]->getValue();
					board[x][y - 1]->empty();
					r = true;
				}
			}
		}
	}
	//pull
	for (int i = boardSizeY; i > 0; i--)
	{
		for (int y = boardSizeY - 1; y > 0; y--)
		{
			for (int x = boardSizeX - 1; x >= 0; x--)
			{

				if (board[x][y]->getValue() == 0)
				{
					if (board[x][y - 1]->getValue() != 0)
					{
						board[x][y]->setValue(board[x][y - 1]->getValue());
						board[x][y - 1]->empty();
						r = true;
					}
				}
			}
		}
	}
	return r;
}

bool Game::left()
{
	bool r = false;
	//pull
	for (int i = 0; i < boardSizeX; i++)
	{
		for (int y = 0; y < boardSizeY; y++)
		{
			for (int x = 0; x < boardSizeX - 1; x++)
			{
				if (board[x][y]->getValue() == 0)
				{
					if (board[x + 1][y]->getValue() != 0)
					{
						board[x][y]->setValue(board[x + 1][y]->getValue());
						board[x + 1][y]->empty();
						r = true;
					}
				}
			}
		}
	}
	//combine
	for (int y = 0; y < boardSizeY; y++)
	{
		for (int x = 0; x < boardSizeX - 1; x++)
		{
			if (board[x][y]->getValue() != 0)
			{
				if (board[x + 1][y]->getValue() == board[x][y]->getValue())
				{
					board[x][y]->collide();
					score += board[x][y]->getValue();
					board[x + 1][y]->empty();
					r = true;
				}
			}
		}
	}
	//pull
	for (int i = 0; i < boardSizeX; i++)
	{
		for (int y = 0; y < boardSizeY; y++)
		{
			for (int x = 0; x < boardSizeX - 1; x++)
			{
				if (board[x][y]->getValue() == 0)
				{
					if (board[x + 1][y]->getValue() != 0)
					{
						board[x][y]->setValue(board[x + 1][y]->getValue());
						board[x + 1][y]->empty();
						r = true;
					}
				}
			}
		}
	}
	return r;
}

void Game::display(RenderWindow *window)
{
	window->draw(background);
	window->draw(title);
	window->draw(bBack);
	if (!gameOver)
	{
		for (int y = 0; y < boardSizeY; y++)
		{
			for (int x = 0; x < boardSizeX; x++)
			{
				board[x][y]->display(window);
			}
		}
		t_score.setString("Score: " + to_string(score));
		window->draw(t_score);
	}
	window->draw(reset);
	window->draw(t_reset);
}

void Game::setBoard(const RenderWindow & window)
{
	int tileSize = ((float)VIEW_HEIGHT / 3)/(float)boardSizeX*4, shiftY = 50;
	float space = tileSize/8;

	title.setFont(font);
	title.setString("2048");
	title.setCharacterSize(150);
	title.setFillColor(theme[3]);
	title.setStyle(Text::Bold);

	t_reset.setFont(font);
	t_reset.setString("New Game");
	t_reset.setCharacterSize(50);
	t_reset.setFillColor(theme[4]);
	t_reset.setStyle(Text::Bold);

	t_score.setFont(font);
	t_score.setCharacterSize(50);
	t_score.setFillColor(theme[3]);
	t_score.setStyle(Text::Bold);

	bBack.setSize(Vector2f((space * (boardSizeX + 2)) + (boardSizeX * tileSize), (space * (boardSizeY + 2)) + (boardSizeY * tileSize)));
	bBack.setFillColor(theme[1]);
	bBack.setPosition(window.getSize().x / 2 - bBack.getSize().x / 2, (window.getSize().y / 2 - bBack.getSize().y / 2)+shiftY);

	reset.setSize(Vector2f(300,80));
	reset.setFillColor(theme[3]);

	title.setPosition(bBack.getPosition().x, 0);
	t_score.setPosition(bBack.getPosition().x + 500, 10);
	reset.setPosition(t_score.getPosition().x, 90);
	t_reset.setPosition(reset.getPosition().x + 20, reset.getPosition().y + 5);

	background.setSize(Vector2f(window.getSize().x, window.getSize().y));
	background.setFillColor(theme[0]);

	float toCenterX = (window.getSize().x / 2 - (((boardSizeX / 2 * tileSize) + (boardSizeY / 2 * space)))) + space / 2;
	float toCenterY = ((window.getSize().y / 2 - (((boardSizeX / 2 * tileSize) + (boardSizeY / 2 * space)))) + space / 2) + shiftY;

	font.loadFromFile("ClearSans-Bold.ttf");
	for (int y = 0; y < boardSizeY; y++)
	{
		for (int x = 0; x < boardSizeX; x++)
		{
			board[x][y] = new Tile(Vector2f(tileSize, tileSize), font, theme, 0);
			board[x][y]->setPosition(Vector2f((x * (tileSize + space)) + (toCenterX), y * (tileSize + space) + (toCenterY)));
		}
	}
}

void Game::resizeView(const RenderWindow & window, View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT*aspectRatio, VIEW_HEIGHT);
}