#pragma once

#include "TinyXML/tinyxml.h"
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying; // loop показывает зациклена ли анимаци€. Ќапример, анимаци€ взрыва или прыжка должна проигратьс€ один раз и остановитьс€
	Sprite sprite;

	Animation()
	{
		currentFrame = 0;
		isPlaying = true;
		flip = false;
		loop = true;
	}

	void tick(float time)
	{
		if (!isPlaying) return;

		currentFrame += speed * time;

		if (currentFrame > frames.size())
		{
			currentFrame -= frames.size();
			if (!loop)
			{
				isPlaying = false;
				return;
			}
		}

		int i = currentFrame;
		sprite.setTextureRect(frames[i]);
		if (flip) sprite.setTextureRect(frames_flip[i]);
	}
};


class AnimationManager
{
public:
	std::string currentAnim;
	std::map<std::string, Animation> animMap;

	AnimationManager()
	{
	}

	~AnimationManager()
	{
		animMap.clear();
	}


	void create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true)
	{
		Animation a;
		a.speed = speed;
		a.loop = Loop;
		a.sprite.setTexture(texture);
		a.sprite.setOrigin(0, h);

		for (int i = 0; i < count; i++)
		{
			a.frames.push_back(IntRect(x + i * step, y, w, h));
			a.frames_flip.push_back(IntRect(x + i * step + w, y, -w, h));
		}
		animMap[name] = a;
		currentAnim = name;
	}


	void loadFromXML(std::string fileName, Texture& t)
	{
		TiXmlDocument animFile(fileName.c_str());

		animFile.LoadFile();

		TiXmlElement* head;
		head = animFile.FirstChildElement("sprites");

		TiXmlElement* animElement;
		animElement = head->FirstChildElement("animation");
		while (animElement)
		{
			Animation anim;
			currentAnim = animElement->Attribute("title");
			int delay = atoi(animElement->Attribute("delay"));
			anim.speed = 1.0 / delay;
			anim.sprite.setTexture(t);

			TiXmlElement* cut;
			cut = animElement->FirstChildElement("cut");
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));


				anim.frames.push_back(IntRect(x, y, w, h));

				anim.frames_flip.push_back(IntRect(x + w, y, -w, h));
				cut = cut->NextSiblingElement("cut");
			}

			anim.sprite.setOrigin(0, anim.frames[0].height);

			animMap[currentAnim] = anim;

			animElement = animElement->NextSiblingElement("animation");
		}
	}

	void set(std::string name)
	{
		currentAnim = name;
		animMap[currentAnim].flip = false;
	}

	void draw(RenderWindow& window, int x = 0, int y = 0)
	{
		animMap[currentAnim].sprite.setPosition(x, y);
		window.draw(animMap[currentAnim].sprite);
	}

	void flip()
	{
		animMap[currentAnim].flip = true;
	}

	void tick(float time)
	{
		animMap[currentAnim].tick(time);
	}

	void pause()
	{
		animMap[currentAnim].isPlaying = false;
	}

	void play()
	{
		animMap[currentAnim].isPlaying = true;
	}

	void play(std::string name)
	{
		animMap[name].isPlaying = true;
	}

	bool isPlaying()
	{
		return animMap[currentAnim].isPlaying;
	}

	float getH()
	{
		return animMap[currentAnim].frames[0].height;
	}

	float getW()
	{
		return animMap[currentAnim].frames[0].width;
	}
};
