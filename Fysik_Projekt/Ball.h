#pragma once
#include <SFML\Graphics.hpp>

#include <math.h>
#include <iostream>
#include <string>

#include "functions.h"

class Ball : public sf::Drawable
{
private:
	sf::CircleShape ball;
	sf::CircleShape dot;

	sf::Vector2f vel;
	sf::Vector2f a;

	float rollFriction;
	float skidFriction;
	float mass;
	float w_f;
	float g;

	float sfmlBallRadius;
	float realBallRadius;
	float dotRadius;

	bool mousePressed;

public:
	Ball(sf::Vector2f pos, bool whiteBall = false);
	virtual ~Ball();

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::CircleShape getCircle() const;
	sf::Vector2f getVelocity() const;
	float getMass() const;

	void setVelocity(sf::Vector2f vel);
	void setPosition(sf::Vector2f pos);
};