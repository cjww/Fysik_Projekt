#include "Game.h"

Game::Game()
{

	window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Physics Game Lab");
	table.setWindow(window);

	while (window->isOpen()) {
		sf::Event e;
		while (window->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonReleased:
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					table.shootBall(*window);
				}

				break;
			}
		}

		//Update
		
		table.update(time.restart().asSeconds());

		window->clear();

		//Draw

		window->draw(table);

		window->display();
	}
}


Game::~Game()
{
	delete this->window;
}
