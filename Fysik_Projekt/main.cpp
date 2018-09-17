#include <iostream>

#include <SFML\Graphics.hpp>

int main(){

	sf::RenderWindow window(sf::VideoMode(600, 400), "Physics Game Lab");

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				exit(0);
				break;

			}
		}

		window.clear();


		window.display();
	}

	return 0;
}