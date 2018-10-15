#include "Table.h"


Table::Table()
{
	tableOuter.setSize(sf::Vector2f(1200, 600));
	tableOuter.setFillColor(sf::Color(140, 70, 20));
	tableOuter.setPosition(sf::Vector2f(0, 100));

	tableInner.setSize(sf::Vector2f(1100, 500));
	tableInner.setFillColor(sf::Color(30, 150, 50));
	tableInner.setPosition(sf::Vector2f(50, 150));

	for (int i = 0; i < 6; i++) 
	{
		holes[i].setPointCount(16);
		holes[i].setRadius(30);
		holes[i].setFillColor(sf::Color::Black);
		holes[i].setOrigin(holes[i].getRadius(), holes[i].getRadius());
	}
	holes[0].setPosition(sf::Vector2f(50, 150));
	holes[1].setPosition(sf::Vector2f(1150, 150));
	holes[2].setPosition(sf::Vector2f(50, 650));
	holes[3].setPosition(sf::Vector2f(1150, 650));
	holes[4].setPosition(sf::Vector2f(600, 150));
	holes[5].setPosition(sf::Vector2f(600, 650));

	ballRadius = 15;
	wallCheckRect.setPosition(tableInner.getPosition() + sf::Vector2f(ballRadius, ballRadius));
	wallCheckRect.setSize(tableInner.getSize() - (sf::Vector2f(ballRadius, ballRadius) * 2.f));

	balls.push_back(Ball(sf::Vector2f(150, 250)));
	balls.push_back(Ball(sf::Vector2f(110, 220)));

	balls[0].setVelocity(sf::Vector2f(-6.f, -4.f));
}


Table::~Table()
{
}

void Table::update(float dt)
{
	for (size_t i = 0; i < balls.size(); i++) 
	{
		balls[i].update(dt);
		
		//--Collision--
		//Ball vs Ball
		for (size_t j = i + 1; j < balls.size(); j++) 
		{
			sf::Vector2f pos_a = balls[i].getCircle().getPosition();
			sf::Vector2f pos_b = balls[j].getCircle().getPosition();
		
			float dist = distance(pos_a, pos_b);
			if (dist <= ballRadius * 2)
			{
				//True
				std::cout << "Ball collide" << std::endl;
				
			}
		}
		
		//Ball vs Hole
		for (unsigned int j = 0; j < 6; j++)
		{
			sf::Vector2f ballPos = balls[i].getCircle().getPosition();
			sf::Vector2f holePos = holes[j].getPosition();
			float holeRadius = holes[i].getRadius();

			float dist = distance(ballPos, holePos);
			if (dist <= holeRadius) 
			{
				//True
				std::cout << "Hole collide" << std::endl;
			}
		}

		//Ball vs Wall
		if (!wallCheckRect.getGlobalBounds().contains(balls[i].getCircle().getPosition())) {
			std::cout << "Wall collide" << std::endl;

		}
	}

}

void Table::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(tableOuter);
	target.draw(tableInner);

	for (unsigned int i = 0; i < 6; i++) 
	{
		target.draw(holes[i]);
	}
	

	for (size_t i = 0; i < balls.size(); i++) 
	{
		target.draw(balls[i]);
	}
	

}

float Table::distance(sf::Vector2f a, sf::Vector2f b) const
{
	return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

