#include "Game.h"

Game::Game()
{

	window = new sf::RenderWindow(sf::VideoMode(1200, 700), "Physics Game Lab");

	tableTex.loadFromFile("../Resources/Table.png");
	tableSprite.setTexture(tableTex);
	tableSprite.scale(sf::Vector2f(10.0f, 10.0f));

	while (window->isOpen()) {
		sf::Event e;
		while (window->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window->close();
				break;

			}
		}

		//Update
		

		window->clear();

		//Draw

		window->draw(tableSprite);
		window->display();
	}
}


Game::~Game()
{
	delete this->window;
}
