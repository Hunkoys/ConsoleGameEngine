#include "Display.h"
#include "KeyListener.h"

const int
PLAYER = 1,
BULLET = 2,
UPGRADE_BOX = 3,
ENEMY = 4;

enum bullet_type { none, normal, heavy, penetrate, scatter };

// ######################################  hp_bar  ######################################
struct hp_bar : public entity
{
	hp_bar(window & wnd, float x, float y, std::vector<std::string> sprite) : entity(wnd, x, y, sprite) {
		Type = 0;
	}
	//- - - - - - - - - - - - - - End of Constructors - - - - - - - - - - - - - - 


};
// **************************************  hp_bar  **************************************


// ######################################  Enemy  ######################################
struct enemy : public entity
{
	float speed = 1.0f;
	int hp = 5;
	hp_bar* bar;
	enemy(window & wnd, float x, float y, std::vector<std::string> sprite) : entity(wnd, x, y, sprite), bar(new hp_bar(wnd, x + 1, y - 1, { "=====" })) {
		Type = ENEMY;
	}
	//- - - - - - - - - - - - - - End of Constructors - - - - - - - - - - - - - - 

	void tick_hp(int dmg)
	{
		hp -= dmg;
		if (hp < 1)
		{   
			dmg += hp;
			hp = 0;
			destroy();
			bar->Exist = false;
		}
		bar->Sprite.at(0).replace(hp, dmg, " ");
	}

	void animate() override
	{
		x -= speed;
		bar->x = x + 1;

		if (x < -5)
		{
			destroy();
		}
	}
};
// **************************************  Enemy  **************************************


// ######################################  Bullets  ######################################
struct bullet : public entity
{
	bullet(window & wnd, float x, float y, std::vector<std::string> sprite, const int& dmg) : entity(wnd, x, y, sprite), Damage(dmg) {
		Type = BULLET;
	}
	//- - - - - - - - - - - - - - End of Constructors - - - - - - - - - - - - - - 

	float velocity = 3.0f;
	const int& Damage;

	void animate() override
	{
		enemy* e1 = (enemy*)collide(ENEMY, Wnd.pEntityList);
		if (e1 != nullptr)
		{
			e1->tick_hp(Damage);
			destroy();
		}
		if (roundf(x) > Wnd.getWidth())
		{
			destroy();
		}
		x += velocity;
	}
};
// **************************************  Bullets  **************************************


// ######################################  P l a y e r  ######################################
struct player : public entity
{
	player(window& wnd, float x, float y, std::vector<std::string> sprite) : entity(wnd, x, y, sprite) {	
		Type = PLAYER;
	}
	//- - - - - - - - - - - - - - End of Constructors - - - - - - - - - - - - - - 


	int Firerate = 5;
	int Damage = 1;
	bullet_type Bullet = normal;
	const char* BulletSprite = "-";

	void animate() override
	{
		static unsigned int i = 0;
		if (!(i++ % Firerate))
		{
			switch (Bullet)
			{
				case none:
					break;
				case normal:
					new bullet(Wnd, x + 2, y, { BulletSprite }, Damage);
					new bullet(Wnd, x + 2, y + 2, { BulletSprite }, Damage);
				default:
					break;
			}
		}
		/*if (collide(ENEMY, Wnd.pEntityList) != nullptr)
			std::cout << "Collide";
		else
			std::cout << "No";*/
	}

	void upgrade_cannon()
	{
		BulletSprite = "=>";
		Damage = 2;
	}
};
// **************************************  P l a y e r  **************************************


// ######################################  Upgrade Box  ######################################
struct upgrade_box : public entity
{
	upgrade_box(window & wnd) : entity(wnd, (float)wnd.getWidth(), 15.0f, { "+---+", "| H |", "+---+" }) {
		Type = UPGRADE_BOX;
	}
	//- - - - - - - - - - - - - - End of Constructors - - - - - - - - - - - - - - 

	const char* pantext[3] = { " H ", "  H", "H  " };
	int fr = 0;
	int interv = 0;

	void animate() override
	{
		if (round(x) + Sprite.at(0).size() < 0)
			destroy();

		x -= 1;

		if (interv++ % 2)
			Sprite.at(1).replace(1, 3, pantext[fr++ % 3]);

		player* P1 = (player*)collide(PLAYER, Wnd.pEntityList);
		if (P1 != nullptr)
		{
			destroy();
			P1->upgrade_cannon();
		}
	}
};
// **************************************  Upgrade Box  **************************************

int maino()
{
	                                                     // =========================
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);   //       Color of
	SetConsoleTextAttribute(hConsole, 12);               //    Console's text
	                                                     // =========================

	srand((unsigned int)time(0));                                      //     Set up "True" random

	keyer FlightCtrl;

	//keyer WeaponCtrl;
	window Pane(100, 20/*, FR */);
	

	player* Player1o = new player(Pane, 5.0, 5.0, { "#\\", "<|>>", "#/" });
	player& Player1 = *Player1o;
	float SpacoMS = 1.f;


	bool Quit = false;

	while (!Quit)
	{
		switch (FlightCtrl.lastKey())
		{
			case /*VK::W*/ 'W' :
				Player1.y -= SpacoMS;
				break;
			case /*VK::S*/ 'S' :
				Player1.y += SpacoMS;
				break;
			case /*VK::A*/ 'A' :
				Player1.x -= SpacoMS;
				break;
			case /*VK::D*/ 'D' :
				Player1.x += SpacoMS;
				break;
			case 'K' :/*
				new missile(Pane, Spaco.x + 2, Spaco.y, ")[-]>", -1);
				new missile(Pane, Spaco.x + 2, Spaco.y + 2, ")[-]>", 1);*/
				break;
			case 'G' :
				new upgrade_box(Pane);
				new enemy(Pane, Pane.getWidth() - 60, 10, { "  /{ >" , "(| @[" , "  \\{ > " });

				break;
			case 'H' :
				break;
			default :
				break;
		}


		if ((rand() % 100) > 85 )
		{
			new enemy(Pane, Pane.getWidth(), (rand() % (Pane.getHeight() - 4)) + 1, { "  /{ >" , "(| @[" , "  \\{ > " });
		}
		/*
		if ((rand() % 100) > 97)
		{
			new upgradebox(Pane, Pane.getWidth(), (rand() % (Pane.getHeight() - 4)) + 1, { "======" , "||  ||" , "||  ||", "======" });
		}
		*/

		Pane.refresh();
		Sleep(10);
	}
	return 0;
}