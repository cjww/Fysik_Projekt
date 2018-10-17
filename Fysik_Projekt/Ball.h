#pragma once
#include <SFML\Graphics.hpp>

#include <math.h>
#include <iostream>

#include "VectorMath.h"

class Ball : public sf::Drawable
{
private:
	sf::CircleShape ball;
	sf::CircleShape dot;

	sf::Vector2f vel;
	float ballRadius;

	bool mousePressed;

	float time;

	float w_f;
public:
	float BALL_MASS = 0.17f;
	float E_WALL = 0.6f; //0.6 - 0.9
	float E_BALL = 0.93f;

	Ball(sf::Vector2f pos, bool whiteBall = false);
	virtual ~Ball();

	void update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::CircleShape getCircle() const;

	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f vel);

	void setPosition(sf::Vector2f pos);
};

