#include "Display.h"


window::window()
{
}

window::window(const int w, const int h) : Width(w), Height(h), BlankFrame(Width * Height, ' ')
{
}



void window::setNextFrame()
{
	try
	{
		EL_it it;
		//std::list<entity*>::reverse_iterator itend = pEntityList.rend();
		for (it = pEntityList.begin(); it != pEntityList.end();)
		{
			if ((**it).Exist)
			{
				(**it).animate();
				it++;
			}
			else
			{
				it = eraseEntity(it);
				//it--; // it is already the next element. For loop will increment it before checking condition. It will skip this element, we had to decrement it first.
			}
		}
	}
	catch (...)
	{
		
	}
}

void window::refresh()
{
	Screen = BlankFrame;
	
	//sort Entity List to another List, Don't modify Entity List. 
	EL_it it;
	for (it = pEntityList.begin(); it != pEntityList.end(); it++)
	{
		if (!(**it).Hidden)
		{
			int i = 0;
			for (std::string line : (**it).Sprite)
			{
				int x = round((**it).x);
				int y = round((**it).y) + i++;
				 //        v Left Bounds           v Right Bounds
				if (x * -1 < (int)line.size() && x < Width && y > -1 && y < Height)
				//check if object line appears in screen
				{
					size_t l = line.size();
					if (x < 0)
						line = line.substr(x*-1, line.npos);
					else if ((x + (int)l) > Width)
						line = line.substr(0, Width - x);
					Screen.replace(y * Width + (x > 0 ? x : 0), line.size(), line);
				// filter and process special chars and opaque
				// Replace the replace fn
				}
			}
		}
	}
	static int pos;
	pos = 0;
	for (int i = 1; i < Height; i++)
	{
		pos += Width;
		Screen.insert(pos, 1, '\n');
		pos++;
	}
	system("CLS");
	std::cout << Screen;

	setNextFrame();
}

void window::addEntity(entity* e)
{
	pEntityList.push_back(e);
}


EL_it& window::eraseEntity(EL_it& it)
{
	entity*& e = (*it);
	if (e->deleteFromHeap)
		delete e;
	it = pEntityList.erase(it);

	e = nullptr;
	return it;
}

int window::getWidth()
{
	return Width;
}

int window::getHeight()
{
	return Height;
}
