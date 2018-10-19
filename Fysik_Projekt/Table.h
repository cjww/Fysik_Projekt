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

	sf::RectangleShape wallcheckRectangle;

	sf::CircleShape holes[6];

	int sfmlBallRadius;
	const float frictionBallvBall = 0.05f;
	std::vector<Ball> balls;

	sf::RenderWindow* window;

public:
	Table();
	virtual ~Table();

	void update(float dt);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void shootBall(sf::RenderWindow& window);

	void setup();

	void setWindow(sf::RenderWindow* window);
};

