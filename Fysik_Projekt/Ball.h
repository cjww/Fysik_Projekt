#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>
class Ball : public sf::Drawable
{
private:
	sf::CircleShape ball;

	sf::Vector2f vel;

	bool mousePressed;

public:
	Ball(sf::Vector2f pos, bool whiteBall = false);
	virtual ~Ball();

	void update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::CircleShape getCircle() const;

	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f vel);
};

