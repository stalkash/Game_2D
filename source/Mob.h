#pragma once

#include "source/Entity.h"
#include "source/level.h"


class Mob : public Entity
{
public:
	bool isAngry; //����� �� ��� �������� �� ������
	bool isSeeHero; // ����� �� ����� ����

	Mob(AnimationManager& anim, Level& lvl, std::string name, float X, float Y, int HP)
		: Entity(anim, lvl, name, X, Y, HP)
	{
		isAngry = false;
		isSeeHero = true;
		//�������� ��� �������, ����� ������������ ������������ ����� �������
		objects = lvl.GetAllObjects();
	}

	~Mob()
	{
	}

	void checkCollision(float Dx, float Dy)
	{
		bool CollisionWithGround = false;
		for (auto object : objects)
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
					CollisionWithGround = true;
					
				}
				else if(!CollisionWithGround)
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

	void behavior()
	{/*������� ����� ������������� ��������� ���� � ����������� �� ��� ����: ������������, ����� � �.�.*/
		
	}

	void update(float time) override
	{
	}
};
