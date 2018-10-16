#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

#include <math.h>
#include <iostream>

class Table : public sf::Drawable
{
private:
	sf::RectangleShape tableOuter;
	sf::RectangleShape tableInner;

	sf::RectangleShape wallCheckRect;

	sf::CircleShape holes[6];

	int ballRadius;
	std::vector<Ball> balls;


public:
	Table();
	virtual ~Table();

	void update(float dt);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	float distance(sf::Vector2f a, sf::Vector2f b) const;

	void shootBall(sf::RenderWindow& window);

};

