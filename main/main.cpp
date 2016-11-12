#include <iostream> 
#include <list>

#include <SFML/Graphics.hpp>

#include "source/level.h"
#include "source/view.h"
#include "source/Player.h"
#include "source/Entity.h"

int main()
{
	using namespace sf;

	RenderWindow window(sf::VideoMode(800, 600), "Game");
	view.reset(sf::FloatRect(0, 0, 800, 600));
	window.setFramerateLimit(60);

	Level lvl;
	lvl.LoadFromFile("resources/levels/mymap2.tmx");

	Image im;
	im.loadFromFile("resources/images/charben.PNG");
	im.createMaskFromColor(Color(255, 255, 255));

	Texture p;
	p.loadFromImage(im);

	AnimationManager pAnim;
	pAnim.loadFromXML("resources/images/charben.xml", p);
	pAnim.animMap["jump"].loop = false;

	Object pObj = lvl.GetObject("Player");

	Player player(pAnim, lvl, "stlk", pObj.rect.left, pObj.rect.top, 100);


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
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		setPlayerViewCoordinates(player.x, player.y);
		window.setView(view);
		window.clear(Color(255, 255, 255));

		lvl.Draw(window);
		player.update(time);
		player.draw(window);

		window.display();
	}

	return 0;
}
