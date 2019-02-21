#include "KeyListener.h"


keyer::keyer() : Listener(&keyer::listen, this)
{

}

void keyer::listen()
{
	while (on)
	{
		_getch();
		for (char i = 0/*32space*/; i < 256/*127Last CH*/; i++)
		{
			if (GetAsyncKeyState(i) & 0x0001)
			{
				keyDown = i;
				break;
			}
		}
	}
}

char keyer::lastKey()
{
	r = keyDown;
	keyDown = 0;
	return r;
}

keyer::~keyer()
{
	on = false;
	Listener.join();
}
