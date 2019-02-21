#include "Display.h"
#include "KeyListener.h"


float g_Gravity = 4.f;

struct cannonball : public entity
{
	cannonball(window & wnd, const float& x, const float& y, const float& agl) : entity(wnd, x, y, { "@" }), Angle(agl)
	{
		Type = 2;
	}

	float cos(const float& a)
	{
		// 1 - 0 = 1
		// 1 - 1 = 0 
		//a 0 / 90 = 0
		//a 90 / 90 = 1
		return (float)(1 - (a / 90));
	}

	float sin(const float& a)
	{
		//0 r 1
		//1 r 0
		return -(float)(a / 90);
	}

	float Angle;
	float Speed = 2.f;
	float xSpeed = Speed * cos(Angle);
	float ySpeed = Speed * sin(Angle);

	void animate() override
	{
		x += xSpeed;
		y += ySpeed += 0.02;
	}
};

struct player : public entity
{
	player(window & wnd, const float& x, const float& y) : entity(wnd, x, y, {"0","   ___","  <   ]==#==[-]"," /##o##\\", "(-)(-)(-)" })
	{
		Type = 1;
	}


	float angle = 20.f;
	
	void animate() override
	{
		Sprite.at(0).assign(std::to_string((int)angle));
	}

};


int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);   //       Color of
	SetConsoleTextAttribute(hConsole, 12);               //    Console's text
														 // =========================

	srand((unsigned int)time(0));                                      //     Set up "True" random

	keyer ctrl;

	//keyer WeaponCtrl;
	window Pane(200, 40/*, FR */);

	player Gunner(Pane, 20, 35);

	bool Quit = false;

	while (!Quit)
	{
		switch (ctrl.lastKey())
		{
			case /*VK::W*/ 'W':
				if (Gunner.angle < 90)
					Gunner.angle++;
				break;
			case /*VK::S*/ 'S':
				if (Gunner.angle > 0)
					Gunner.angle--;
				break;
			case /*VK::A*/ 'A':
				break;
			case /*VK::D*/ 'D':
				break;
			case 'K':
				new cannonball(Pane, Gunner.x + 15, Gunner.y + 2, Gunner.angle);
				break;
			case 'G':
				break;
			case 'H':
				break;
			default:
				break;
		}

		Pane.refresh();
		Sleep(5);
	}
	return 0;
}