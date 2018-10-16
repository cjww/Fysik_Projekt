#include "Ball.h"

Ball::Ball(sf::Vector2f pos, bool whiteBall)
{
	ball.setRadius(15);
	if (whiteBall)
		ball.setFillColor(sf::Color::White);
	else
		ball.setFillColor(sf::Color::Red);
	ball.setOutlineColor(sf::Color::Transparent);
	ball.setPointCount(16);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(pos);

	mousePressed = false;
}


Ball::~Ball()
{
}

void Ball::update(float dt)
{
	//Fysik för bollen
	ball.setPosition(ball.getPosition() + vel * dt);
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ball);
}

sf::CircleShape Ball::getCircle() const
{
	return ball;
}

sf::Vector2f Ball::getVelocity() const
{
	return this->vel;
}

void Ball::setVelocity(sf::Vector2f vel)
{
	this->vel = vel;
}
