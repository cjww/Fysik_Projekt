#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "GameObjectHandler.h"

class Game
{
private:
	sf::RenderWindow * window;

	GameObjectHandler objHandler;

	sf::Texture tableTex;
	sf::Sprite tableSprite;

public:
	Game();
	virtual ~Game();
};
