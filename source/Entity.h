#pragma once
#include "source/Animation.h"
#include <vector>
#include "source/level.h"


class Entity
{
public:
	std::string name;
	std::vector<Object> objects;

	float dx, dy; //speed
	float x, y;
	float w, h; // width, height

	int health, MAX_HEALTH;

	bool isLife;
	bool onGround;
	bool isHit; //Для анимации при получении урона.

	AnimationManager animation;

	enum
	{
		STAY,
		SIT,
		WALK,
		JUMP,
		FALL,
		CLIMB
	} state;

	enum
	{
		LEFT,
		RIGHT
	} direction;

	Entity(AnimationManager& anim, Level& lvl, std::string name, float X, float Y, int HP)
	{
		x = X;
		y = Y;

		w = anim.getW();
		h = anim.getH();

		dx = 0;
		dy = 0;

		health = HP;
		MAX_HEALTH = HP;

		animation = anim;

		isLife = true;
		onGround = false;
		isHit = false;

		state = STAY;
	}

	virtual ~Entity()
	{
	};

	virtual void update(float time) = 0;

	void draw(RenderWindow& window)
	{
		animation.draw(window, x, y + h);
	}

	FloatRect getRect() const
	{
		return FloatRect(x, y, w, h);
	}
};
