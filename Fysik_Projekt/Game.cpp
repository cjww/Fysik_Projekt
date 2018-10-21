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

		// Updatera fysik för objekt
		table.update(time.restart().asSeconds());


		// Rensa skärmen
		window->clear();

		sf::Font font;
		font.loadFromFile("../Resources/VCR.ttf");
		
		sf::Text ballsLeft;
		ballsLeft.setFont(font);
		ballsLeft.setString(std::to_string(table.getNrOfBallsLeft() - 1) + " left");
		ballsLeft.setCharacterSize(40);
		ballsLeft.setOrigin(ballsLeft.getGlobalBounds().width / 2, 0);
		ballsLeft.setPosition(sf::Vector2f(1200 / 4, 30));
		window->draw(ballsLeft);
		
		sf::Text shots;
		shots.setFont(font);
		shots.setString(std::to_string(table.getNrOfShots()) + " shots");
		shots.setCharacterSize(40);
		shots.setOrigin(shots.getGlobalBounds().width / 2, 0);
		shots.setPosition(sf::Vector2f(1200 * 3 / 4, 30));
		window->draw(shots);

		// Rita ut saker
		window->draw(table);

		window->display();
	}
}

Game::~Game()
{
	delete this->window;
}