#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Table : public sf::Drawable
{
private:
	sf::RectangleShape tableOuter;
	sf::RectangleShape tableInner;

	sf::CircleShape holes[6];

	std::vector<Ball> balls;


public:
	Table();
	virtual ~Table();

	void update(float dt);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

