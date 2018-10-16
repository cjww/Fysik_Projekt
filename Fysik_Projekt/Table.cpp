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

	float middleY = tableInner.getSize().y / 2 + tableInner.getPosition().y;
	// Set start positions for the balls
	// White ball
	balls.push_back(Ball(sf::Vector2f(250, middleY), true));
	
	// First balls position is stored in firstRedBall, to be used to calculate the other balls startpositions
	sf::Vector2f firstRedBall = (sf::Vector2f(tableInner.getSize().x + tableInner.getPosition().x - 250, middleY));
	balls.push_back(Ball(firstRedBall));

	// Second line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 1), firstRedBall.y - (ballRadius + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 1), firstRedBall.y + ballRadius + 0.01f)));

	
	// Third line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 2), firstRedBall.y - (ballRadius*2 + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 2), firstRedBall.y)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 2), firstRedBall.y + (ballRadius * 2 + 0.01f))));

	// Fourth line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y - (ballRadius + 0.02f) - ballRadius*2)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y - (ballRadius + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y + (ballRadius + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y + (ballRadius + 0.02f) + ballRadius*2)));

	// Fifth line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y - (ballRadius * 2 + 0.02f) - ballRadius*2)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y - (ballRadius * 2 + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y + (ballRadius * 2 + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y + (ballRadius * 2 + 0.02f) + ballRadius*2)));
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
				balls.erase(balls.begin() + i);
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

void Table::shootBall(sf::RenderWindow& window)
{
	sf::Vector2i mPos = sf::Mouse::getPosition(window);
	sf::Vector2f ballPos = balls[0].getCircle().getPosition();
	sf::Vector2f diff = sf::Vector2f(mPos.x - ballPos.x, mPos.y - ballPos.y);

	balls[0].setVelocity(diff);
}

