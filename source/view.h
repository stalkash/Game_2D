#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

inline void setPlayerViewCoordinates(float x, float y)
{
	float tempX = x;
	float tempY = y;

	//TODO добавить ограничения по перемещению камеры
	//if (x < 320) tempX = 320;
	//if (y < 240) tempY = 240;
	if (y > 624) tempY = 624;

	view.setCenter(tempX, tempY);
}


///////////Перемещение камеры отдельно от персонажа/////////////

inline void viewmap(float time) //
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		setPlayerViewCoordinates(x + 0.1 * time, y);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		setPlayerViewCoordinates(x, y + 0.1 * time);
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		setPlayerViewCoordinates(x - 0.1 * time, y);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		setPlayerViewCoordinates(x, y - 0.1 * time);
	}
}

void viewByMouse(RenderWindow& window, float time)
{
	//TODO сделать перемещение вверх и вниз
	Vector2i localPos = Mouse::getPosition(window);

	if (localPos.x > window.getSize().x - 30)
	{
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		setPlayerViewCoordinates(x + 0.1 * time, y);
	}
	if (localPos.x < 30)
	{
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		setPlayerViewCoordinates(x - 0.1 * time, y);
	}
}
