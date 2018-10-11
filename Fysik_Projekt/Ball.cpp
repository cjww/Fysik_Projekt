#include "Ball.h"

Ball::Ball(sf::Vector2f pos, bool whiteBall)
{
	ball.setRadius(20);
	if (whiteBall)
		ball.setFillColor(sf::Color::White);
	else
		ball.setFillColor(sf::Color::Red);
	ball.setPointCount(16);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(pos);
}


Ball::~Ball()
{
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ball);
}
