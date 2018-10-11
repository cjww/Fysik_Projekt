#pragma once
#include <SFML\Graphics.hpp>

class Ball : public sf::Drawable
{
private:
	sf::CircleShape ball;

public:
	Ball(sf::Vector2f pos, bool whiteBall = false);
	virtual ~Ball();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

