#include "Ball.h"

Ball::Ball(sf::Vector2f pos, bool whiteBall)
{
	ballRadius = 14.8f;
	ball.setRadius(ballRadius);
	if (whiteBall) {
		ball.setFillColor(sf::Color::White);
		BALL_MASS = 0.17f;
	}
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

	w_f = 0.0f;
	skidFriction = 0.2f;
	rollFriction = 0.01f;
	g = 9.82f;
	//realRadius = 0.028575f;
	realRadius = ballRadius / sfmlScaleFactor;

}


Ball::~Ball()
{
}

void Ball::update(float dt)
{
	//Fysik för bollen
	if (length(vel) / sfmlScaleFactor > 0.01f) 
	{
		w_f += ((5 * skidFriction * g * dt) / (realRadius * 2));

		if (length(vel) / sfmlScaleFactor < realRadius * w_f) 
		{
			std::cout << "Rullfas" << std::endl;
			//Rullfas
			//float wf = length(vel) / ballRadius;
			a = rollFriction * g * normalize(vel);

		}
		else
		{
			std::cout << "Glidfas" << std::endl;
			//Glidfas
			//vel = sf::Vector2f(vel.x - skidFriction * g * dt, vel.y - skidFriction * g * dt);
			a = skidFriction * g * normalize(vel);
		}
	}
	else
	{
		a = sf::Vector2f(0.f, 0.f);
		vel = sf::Vector2f(0.f, 0.f);
	}
	
	//TODO 
	//dot.setPosition(ball.getPosition() + sf::Vector2f(vel.x + ballRadius * sin(w_f), vel.y + ballRadius * cos(w_f)));
	//dot.setPosition(ball.getPosition() + sf::Vector2f(ballRadius * sin(w_f), ballRadius * cos(w_f)));

	vel = vel - a * sfmlScaleFactor * dt;
	ball.setPosition(ball.getPosition() + vel * dt);
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
	//target.draw(dot);

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
