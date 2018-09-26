#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
private:
	sf::Sprite sprite;


public:
	GameObject();
	virtual ~GameObject();
};

