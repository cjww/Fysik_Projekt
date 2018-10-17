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
	//Fysik f�r bollen
	float slideCof = 0.2f;
	float g = 9.82f;
	if (false) 
	{
		//float wf = getVelocityLength() / ballRadius;

	}
	else
	{
		//Glidfas
		w_f += (5 * slideCof * g) / (ballRadius * 2);
	
	}
	
	
	dot.setPosition(ball.getPosition() + sf::Vector2f(vel.x * time + ballRadius * sin(w_f * time), vel.y * time + ballRadius * cos(w_f * time)));
	//time?
	ball.setPosition(ball.getPosition() + vel * dt);
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

float Ball::getVelocityLength() const
{
	return sqrt(pow(vel.x, 2) + pow(vel.y, 2));
}

void Ball::setVelocity(sf::Vector2f vel)
{
	this->vel = vel;
}

void Ball::setPosition(sf::Vector2f pos) {
	ball.setPosition(pos);
}
