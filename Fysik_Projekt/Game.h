#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Table.h"

#include <Windows.h>

class Game
{
private:
	sf::Clock time;
	sf::RenderWindow * window;
	Table table;

public:
	Game();
	virtual ~Game();
};