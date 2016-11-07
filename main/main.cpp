#include <iostream> 
#include <list>

#include <SFML/Graphics.hpp>

#include "source/level.h"
#include "source/view.h"


int main()
{
	using namespace sf;
	RenderWindow window(sf::VideoMode(800, 600), "Game");
	view.reset(sf::FloatRect(0, 0, 800, 600));
	window.setFramerateLimit(60);

	float time;
	Clock clock;

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.setView(view);
		window.clear();
		//window.draw();
		window.display();
	}

	return 0;
}