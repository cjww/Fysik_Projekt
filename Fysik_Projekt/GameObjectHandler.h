#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"

class GameObjectHandler : sf::Drawable
{
private:
	std::vector<GameObject> gameObjects;
public:
	GameObjectHandler();
	virtual ~GameObjectHandler();

	void update(float dt);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

