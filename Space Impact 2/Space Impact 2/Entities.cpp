#pragma once
#include "Entities.h"
#include "Display.h"

entity::entity(window&  wnd, float x, float y, std::vector<std::string> sprite) : Wnd(wnd), x(x), y(y), Sprite(sprite), Type(0)
{
	Wnd.addEntity(this);
	Alive = 1;
	Hidden = 0;
	deleteFromHeap = 0;
}

entity::entity(window & wnd, float x, float y, const char * line) : entity(wnd, x, y, std::vector<std::string>(1, line))
{
}

void entity::animate()
{

}

void entity::die()
{
	Alive = false;
}

void entity::hide()
{
	Hidden = true;
}

void entity::hide(const bool& s)
{
	Hidden = s;
}

void entity::destroy()
{
	Exist = false;
	deleteFromHeap = true;
}

entity* entity::collide(int type, std::list<entity*> eList)
{
	std::list<entity*>::iterator it = eList.begin();
	while (it != eList.end())
	{
		if ((**it).Type == type)
		{
			for (int i = 0; i < (int)Sprite.size(); i++)
			{
				if (round(y) + i > round((**it).y) - 1 && round(y) + i < round((**it).y) + (**it).Sprite.size())
				{
					const std::string& line = Sprite.at(i);
					for (int o = 0; o < (int)line.size(); o++)
					{
						if (round(x) + o > round((**it).x) - 1 && round(x) + o < round((**it).x) + (**it).Sprite.at(i).size())
						{
							return *it;
						}
					}

				}
			}
		}
		it++;
	}
	return nullptr;
}

entity::~entity()
{

}
