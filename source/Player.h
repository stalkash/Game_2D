#pragma once

#include "source/Entity.h"

class Player: public Entity
{
public:
	bool isShoot;

	Player(AnimationManager& anim, Level& lvl, std::string name, float x, float y, int HP)
		: Entity(anim, lvl, name, x, y, HP)
	{
		isShoot = false;
		objects = lvl.GetAllObjects();
	}

	~Player()
	{
	}

	void handleInput()
	{
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			state = WALK;
			dx = 0.15;
			direction = LEFT;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::A)))
		{
			state = WALK;
			dx = -0.15;
			direction = RIGHT;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::S)))
		{
			state = SIT;
		}
		else if (onGround)
		{
			state = STAY;
			dx = 0;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Space) && onGround))
		{
			state = JUMP;
			animation.play("jump");
			dy = -0.4;
			onGround = false;
		}
	}

	void animate(float time)
	{
		switch (state)
		{
		case WALK:
			if (direction == LEFT && onGround)
			{
				animation.set("walk");
			}
			else if (onGround)
			{
				animation.set("walk");
				animation.flip();
			}
			else if (direction == LEFT)
			{
				animation.play();
			}
			else
			{
				animation.play();
				animation.flip();
			}
			break;
		case STAY:
			if (direction == LEFT)
			{
				animation.set("stay");
			}
			else
			{
				animation.set("stay");
				animation.flip();
			}
			break;
		case JUMP:
			animation.set("jump");
			break;
		case SIT:
			animation.set("sit");
			break;
		}

		animation.tick(time);
	}

	void checkCollision(float Dx, float Dy)
	{
		for (auto object: objects)
		{
			if (getRect().intersects(object.rect))
			{
				if (object.name == "solid")
				{
					if (Dx > 0)
						x = object.rect.left - w;
					if (Dx < 0)
						x = object.rect.left + object.rect.width;
					if (Dy > 0)
					{
						y = object.rect.top - h;
						dy = 0;
						onGround = true;
					}
					if (Dy < 0)
					{
						y = object.rect.top + object.rect.height;
						dy = 0;
					}
				}
				else
					onGround = false;
				if (object.name == "Enemy")
				{
					if (Dx > 0)
						x = object.rect.left - w;
					if (Dx < 0)
						x = object.rect.left + object.rect.width;
					if (Dy > 0)
					{
						y = object.rect.top - h;
						dy = 0;
					}
					if (Dy < 0)
					{
						y = object.rect.top + object.rect.height;
						dy = 0;
					}
				}
			}
		}
	}

	void update(float time) override
	{
		handleInput();
		animate(time);

		x += dx * time;
		checkCollision(dx, 0);

		y += dy * time;
		checkCollision(0, dy);

		if (health <= 0)
			isLife = false;

		dy = dy + 0.0015 * time;
	}
};
