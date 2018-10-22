#include "Ball.h"

Ball::Ball(sf::Vector2f pos, bool whiteBall)
{
	sfmlBallRadius = BALL_RADIUS;
	ball.setRadius(sfmlBallRadius);
	if (whiteBall) {
		ball.setFillColor(sf::Color::White);
		mass = 0.17f;
	}
	else
	{
		ball.setFillColor(sf::Color::Red);
		mass = 0.16f;
	}
	ball.setOutlineColor(sf::Color::Transparent);
	ball.setPointCount(16);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(pos);

	mousePressed = false;
	
	dotRadius = 3;
	dot.setRadius(dotRadius);
	dot.setPointCount(6);
	dot.setOrigin(dot.getRadius(), dot.getRadius());
	dot.setPosition(ball.getPosition());
	dot.setFillColor(sf::Color::Blue);

	w_f = 0.0f;
	skidFriction = 0.2f;
	rollFriction = 0.015f;
	g = 9.82f;
	realBallRadius = sfmlBallRadius / sfmlScaleFactor;
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	//Fysik för bollen
	if (length(vel) / sfmlScaleFactor > 0.01f) 
	{

		if (length(vel) / sfmlScaleFactor < realBallRadius * w_f) 
		{
			//Rullfas
			//std::cout << "Rullfas" << std::endl;
			w_f = length(vel);
			a = rollFriction * g * normalize(vel);
		}
		else
		{
			//Glidfas
			//std::cout << "Glidfas" << std::endl;
			w_f += ((5 * skidFriction * g * dt  / (realBallRadius * 2)));
			a = skidFriction * g * normalize(vel);
		}
	}
	else
	{
		a = sf::Vector2f(0.f, 0.f);
		vel = sf::Vector2f(0.f, 0.f);
		w_f = 0.0f;
	}
	
	vel = vel - a * sfmlScaleFactor * dt;
	ball.setPosition(ball.getPosition() + vel * dt);
	dot.setPosition(ball.getPosition() + normalize(vel) * cos(w_f * length(vel) / sfmlScaleFactor) * (sfmlBallRadius - dotRadius * 2));
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Vertex velLine[] =
	{
		sf::Vertex(ball.getPosition()),
		sf::Vertex(ball.getPosition() + vel)
	};
	target.draw(velLine, 2, sf::Lines);

	target.draw(ball);
	
	// Gör så att värdet inom cos är inom 0-180 då punkten endast ska synas när den är "över" bollen.
	float cosValue = w_f * length(vel) / sfmlScaleFactor;
	while (cosValue > (PI * 2))
	{
		cosValue -= (PI * 2);
	}
	if (cosValue >= 0 && cosValue <= PI)
	{
		target.draw(dot);
	}

	sf::Font font;
	font.loadFromFile("../Resources/VCR.ttf");
	sf::Text text;
	text.setFont(font);
	text.setPosition(ball.getPosition() + sf::Vector2f(-20, -35));
	text.setString(std::to_string((int)length(vel) / sfmlScaleFactor));
	text.setCharacterSize(20);
	target.draw(text);
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

float Ball::getMass() const
{
	return mass;
}