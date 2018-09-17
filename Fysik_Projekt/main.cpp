#include <iostream>

#include <SFML\Graphics.hpp>

int main(){

	sf::RenderWindow window(sf::VideoMode(600, 400), "Physics Game Lab");

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;

			}
		}

		window.clear();

		sf::Font font;
		font.loadFromFile("../Minecraft.ttf");
		sf::Text text;
		text.setString("Hello World\nHello Again");
		text.setFont(font);
		
	
		window.draw(text);

		window.display();
	}

	return 0;
}