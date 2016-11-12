#pragma once

#include "source/Entity.h"

class Character : public Entity
{
public:
	//TODO сделать инвентарь

	Character(AnimationManager& anim, Level &lvl, std::string name, float x, float y, int HP)
		: Entity(anim, lvl, name, x, y, HP)
	{
	}

	~Character()
	{
		
	}
};
