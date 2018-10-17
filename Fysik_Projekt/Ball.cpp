#include "Ball.h"

Ball::Ball(sf::Vector2f pos, bool whiteBall)
{
	ballRadius = 15;
	ball.setRadius(ballRadius);
	if (whiteBall)
		ball.setFillColor(sf::Color::White);
	else
		ball.setFillColor(sf::Color::Red);
	ball.setOutlineColor(sf::Color::Transparent);
	ball.setPointCount(16);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(pos);

	mousePressed = false;
	
	dot.setRadius(3);
	dot.setPointCount(5);
	dot.setOrigin(dot.getRadius(), dot.getRadius());
	dot.setPosition(ball.getPosition());
	dot.setFillColor(sf::Color::Blue);

	w_f = 0;
}


Ball::~Ball()
{
}

void Ball::update(float dt)
{
	time += dt;
	//Fysik för bollen
	if (length(vel) > 0.01f) 
	{
		float slideCof = 0.2f;
		float g = 9.82f;
		if (false) 
		{
			//float wf = length(vel) / ballRadius;

		}
		else
		{
			//Glidfas
			w_f += ((5 * slideCof * g) / (ballRadius * 2) * dt);
	
		}
	}
	
	//TODO 
	dot.setPosition(ball.getPosition() + sf::Vector2f(vel.x + ballRadius * sin(w_f), vel.y + ballRadius * cos(w_f)));
	//time?

	ball.setPosition(ball.getPosition() + vel * dt);
	
	//temp
	//vel *= 0.9995f;
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ball);
	target.draw(dot);
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

void Ball::setPosition(sf::Vector2f pos) {
	ball.setPosition(pos);
}
