#include "Table.h"


Table::Table()
{
	tableOuter.setSize(sf::Vector2f(1200, 600));
	tableOuter.setFillColor(sf::Color(140, 70, 20));
	tableOuter.setPosition(sf::Vector2f(0, 100));

	tableInner.setSize(sf::Vector2f(1100, 500));
	tableInner.setFillColor(sf::Color(30, 150, 50));
	tableInner.setPosition(sf::Vector2f(50, 150));

	for (int i = 0; i < 6; i++) {
		holes[i].setPointCount(16);
		holes[i].setRadius(25);
		holes[i].setFillColor(sf::Color::Black);
		holes[i].setOrigin(holes[i].getRadius(), holes[i].getRadius());
	}
	holes[0].setPosition(sf::Vector2f(50, 150));
	holes[1].setPosition(sf::Vector2f(1150, 150));
	holes[2].setPosition(sf::Vector2f(50, 650));
	holes[3].setPosition(sf::Vector2f(1150, 650));
	holes[4].setPosition(sf::Vector2f(600, 150));
	holes[5].setPosition(sf::Vector2f(600, 650));

	
}


Table::~Table()
{
}

void Table::update(float dt)
{

}

void Table::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(tableOuter);
	target.draw(tableInner);

	for (unsigned int i = 0; i < 6; i++) {
		target.draw(holes[i]);
	}
	

	for (size_t i = 0; i < balls.size(); i++) {
		target.draw(balls[i]);
	}
	

}

