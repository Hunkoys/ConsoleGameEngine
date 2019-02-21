#pragma once
#include <Windows.h>
#include <conio.h>
#include <thread>

class keyer
{
private:
	bool on = true;
	char r;
public:
	void listen();

	std::thread Listener;
	char keyDown;

	keyer();


	char lastKey();

	~keyer();
};