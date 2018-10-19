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
		holes[i].setRadius(35);
		holes[i].setFillColor(sf::Color::Black);
		holes[i].setOrigin(holes[i].getRadius(), holes[i].getRadius());
	}
	holes[0].setPosition(sf::Vector2f(50, 150));
	holes[1].setPosition(sf::Vector2f(1150, 150));
	holes[2].setPosition(sf::Vector2f(50, 650));
	holes[3].setPosition(sf::Vector2f(1150, 650));
	holes[4].setPosition(sf::Vector2f(600, 150));
	holes[5].setPosition(sf::Vector2f(600, 650));

	ballRadius = 14.8f;
	wallCheckRect.setPosition(tableInner.getPosition() + sf::Vector2f(ballRadius, ballRadius));
	wallCheckRect.setSize(tableInner.getSize() - (sf::Vector2f(ballRadius, ballRadius) * 2.f));

	setup();
}


Table::~Table()
{
}

void Table::update(float dt)
{
	for (size_t i = 0; i < balls.size(); i++) 
	{
		
		//--Collision--
		//Ball vs Ball
		for (size_t j = i + 1; j < balls.size(); j++)
		{
			//if (j == i) continue;
			sf::Vector2f pos_a = balls[i].getCircle().getPosition();
			sf::Vector2f pos_b = balls[j].getCircle().getPosition();

			float dist = distance(pos_a, pos_b);
			if (dist <= ballRadius * 2)
			{
				
				//True
				sf::Vector2f e_p = normalize(pos_a - pos_b);
				//float magicNumber = balls[i].getVelocity().x * e_p.y - balls[i].getVelocity().y * e_p.x;
				float magicNumber = abs(balls[i].getVelocity().x * e_p.y - balls[i].getVelocity().y * e_p.x);
				//float magicNumber = abs(balls[i].getVelocity().y * e_p.x - balls[i].getVelocity().x * e_p.y);

				sf::Vector2f e_n;

				float v1_p = dotProduct(balls[i].getVelocity(), e_p);
				float v2_p = dotProduct(balls[j].getVelocity(), e_p);
				float m1 = balls[i].BALL_MASS;
				float m2 = balls[j].BALL_MASS;
				float e = balls[i].E_BALL;
				float u1_p = (((m1 - e * m2) * v1_p) / (m1 + m2)) + (((1 + e) * m2 * v2_p) / (m1 + m2));
				float u2_p = (((1 + e) * m1 * v1_p) / (m1 + m2)) + (((m2 - m1 * e) * v2_p) / (m1 + m2));
				

				sf::Vector2f u1 = balls[i].getVelocity() + (u1_p - v1_p) * e_p;
				sf::Vector2f u2 = balls[j].getVelocity() + (u2_p - v2_p) * e_p;
				if (magicNumber > 0.1f)
				{
					e_n = normalize(sf::Vector2f(-magicNumber * e_p.y, magicNumber * e_p.x) / magicNumber);

					u1 = balls[i].getVelocity() + (u1_p - v1_p) * (e_p + (e_n));
					u2 = balls[j].getVelocity() + (u2_p - v2_p) * (e_p + (e_n));
				}

				/*
				std::cout << "v1_p: " << v1_p << std::endl;
				std::cout << "v2_p: " << v2_p << std::endl;
				std::cout << "m1: "	<< m1 << std::endl;
				std::cout << "m2: "	<< m2 << std::endl;
				std::cout << "e: " << e << std::endl;
				std::cout << "u1_p: " << u1_p << std::endl;
				std::cout << "u2_p: "<< u2_p << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
				*/
				std::cout << magicNumber << std::endl;

				/*
				if (length(balls[i].getVelocity()) < 0.01f) 
				{
					balls[j].setPosition(balls[i].getCircle().getPosition() - e_p * ((float)ballRadius * 2));
				}
				else if (length(balls[j].getVelocity()) < 0.01f) 
				{
					balls[i].setPosition(balls[j].getCircle().getPosition() + e_p * ((float)ballRadius * 2));
				}
				else {

				}
				*/
					balls[j].setPosition(balls[i].getCircle().getPosition() - e_p * ((float)ballRadius * 2));

				balls[i].setVelocity(u1);
				balls[j].setVelocity(u2);

			}
		}
		
		//Ball vs Hole
		sf::Vector2f ballPos = balls[i].getCircle().getPosition();
		for (unsigned int j = 0; j < 6; j++)
		{
			sf::Vector2f holePos = holes[j].getPosition();
			float holeRadius = holes[j].getRadius();

			float dist = distance(ballPos, holePos);
			if (dist <= holeRadius) 
			{
				//True
				std::cout << "Hole collide" << std::endl;
				if (balls[i].getCircle().getFillColor() == sf::Color::White)
				{
					setup();
				}
				else
				{
					balls.erase(balls.begin() + i);
					return;
				}

				if (balls.empty()) 
				{
					setup();
				}
				
			}
		}

		//Ball vs Wall
		if (!wallCheckRect.getGlobalBounds().contains(balls[i].getCircle().getPosition())) {
			std::cout << "Wall collide" << std::endl;
			if(balls[i].getCircle().getPosition().x > wallCheckRect.getPosition().x + wallCheckRect.getSize().x)
			{
				std::cout << "Right wall" << std::endl;
				balls[i].setVelocity(sf::Vector2f(
					-balls[i].getVelocity().x * balls[i].E_WALL,
					balls[i].getVelocity().y * balls[i].E_WALL));
				
				balls[i].setPosition(sf::Vector2f(
					wallCheckRect.getPosition().x + wallCheckRect.getSize().x - 0.01f,
					balls[i].getCircle().getPosition().y
				));
			}
			else if (balls[i].getCircle().getPosition().x < wallCheckRect.getPosition().x)
			{
				std::cout << "Left wall" << std::endl;
				balls[i].setVelocity(sf::Vector2f(
					-balls[i].getVelocity().x * balls[i].E_WALL,
					balls[i].getVelocity().y * balls[i].E_WALL));
				
				balls[i].setPosition(sf::Vector2f(
					wallCheckRect.getPosition().x + 0.01f,
					balls[i].getCircle().getPosition().y
				));
			}
			else if (balls[i].getCircle().getPosition().y < wallCheckRect.getPosition().y)
			{
				std::cout << "Top wall" << std::endl;
				balls[i].setVelocity(sf::Vector2f(
					balls[i].getVelocity().x * balls[i].E_WALL,
					-balls[i].getVelocity().y * balls[i].E_WALL));
				
				balls[i].setPosition(sf::Vector2f(
					balls[i].getCircle().getPosition().x,
					wallCheckRect.getPosition().y + 0.01f
				));
			}
			else if (balls[i].getCircle().getPosition().y > wallCheckRect.getPosition().y + wallCheckRect.getSize().y)
			{
				std::cout << "Bottom wall" << std::endl;
				balls[i].setVelocity(sf::Vector2f(
					balls[i].getVelocity().x * balls[i].E_WALL,
					-balls[i].getVelocity().y * balls[i].E_WALL));
				
				balls[i].setPosition(sf::Vector2f(
					balls[i].getCircle().getPosition().x,
					wallCheckRect.getPosition().y + wallCheckRect.getSize().y - 0.01f
				));
			}
		
		}
		balls[i].update(dt);
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
	
	//Aim
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vertex line[] =
		{
			sf::Vertex(balls[0].getCircle().getPosition()),
			sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(*window))

		};

		target.draw(line, 2, sf::Lines);

	}
	for (size_t i = 0; i < balls.size(); i++) 
	{
		target.draw(balls[i]);
	}
	

}

float Table::distance(sf::Vector2f a, sf::Vector2f b) const
{
	sf::Vector2f diff = a - b;
	return sqrt(pow(diff.x, 2) + pow(diff.y, 2));
}

void Table::shootBall(sf::RenderWindow& window)
{
	sf::Vector2i mPos = sf::Mouse::getPosition(window);
	sf::Vector2f ballPos = balls[0].getCircle().getPosition();
	sf::Vector2f diff = sf::Vector2f(mPos.x - ballPos.x, mPos.y - ballPos.y);

	balls[0].setVelocity(diff);
}

void Table::setup()
{
	balls.clear();

	float middleY = tableInner.getSize().y / 2 + tableInner.getPosition().y;
	// Set start positions for the balls
	// White ball
	balls.push_back(Ball(sf::Vector2f(250, middleY), true));

	// First balls position is stored in firstRedBall, to be used to calculate the other balls startpositions
	sf::Vector2f firstRedBall = (sf::Vector2f(tableInner.getSize().x + tableInner.getPosition().x - 250, middleY));
	balls.push_back(Ball(firstRedBall));

	// Second line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 1), firstRedBall.y - (ballRadius + 0.01f))));
	/*
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 1), firstRedBall.y + ballRadius + 0.01f)));


	// Third line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 2), firstRedBall.y - (ballRadius * 2 + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 2), firstRedBall.y)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 2), firstRedBall.y + (ballRadius * 2 + 0.01f))));

	// Fourth line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y - (ballRadius + 0.02f) - ballRadius * 2)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y - (ballRadius + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y + (ballRadius + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 3 + 0.01f), firstRedBall.y + (ballRadius + 0.02f) + ballRadius * 2)));

	// Fifth line of balls
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y - (ballRadius * 2 + 0.02f) - ballRadius * 2)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y - (ballRadius * 2 + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y)));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y + (ballRadius * 2 + 0.01f))));
	balls.push_back(Ball(sf::Vector2f(firstRedBall.x + (sqrt(3) * ballRadius * 4 + 0.02f), firstRedBall.y + (ballRadius * 2 + 0.02f) + ballRadius * 2)));
	*/

}

void Table::setWindow(sf::RenderWindow * window)
{
	this->window = window;
}

