#pragma once
#include "Entities.h"
#include <list>
#include <string>
#include <iostream>
#include <cmath>

class window 
{
	int Width;
	int Height;
	typedef std::string frame;
	const frame BlankFrame;
	frame Screen;
	unsigned int FrameRate;

	window();

public:
	std::list<entity*> pEntityList;

	window(const int, const int);

	void setNextFrame();
	void refresh();

	void addEntity(entity*);
	EL_it& eraseEntity(EL_it&);

	int getWidth();
	int getHeight();
};