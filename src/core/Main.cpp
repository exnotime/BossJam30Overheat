#include <SFML/Graphics.hpp>
#include "Game.h"
#include "../input/GlobalMouse.h"
int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280, 720), "Test window");
	sf::Event event;
	Game game1;
	game1.Initialize(window);

	sf::Clock gametimer;
	
	while (window.isOpen()){
		while (window.pollEvent(event)){ 
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}
		//update input
		g_Mouse.Update(window);
		//update game
		game1.Update(gametimer);
		//render game
		window.clear();
		game1.Draw(&window);
		window.display();
	}
	return 0;
}