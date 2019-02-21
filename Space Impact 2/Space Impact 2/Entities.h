#pragma once
#include <vector>
#include <list>
#define EL_it std::list<entity*>::iterator
#define REL_it std::list<entity*>::reverse_iterator

class window;

class entity
{
	friend class window;
	bool Alive;// = 1                 //---------------
	bool deleteFromHeap;              //
public:                               //
	bool Exist;                       //    States
	bool Hidden;// = 0                //---------------

	int Type;                         //---------------
	float x;                          //
	float y;                          //   Attributes
	float z; // for sorting           //---------------

	std::vector<std::string> Sprite;  //    Image

	

	virtual void animate();
	void die();                                   // die(): Set Alive to 0
	void hide();
	void hide(const bool&);                              
	void destroy();
	entity* collide(int, std::list<entity*>);     // switch parameters

	virtual ~entity();

protected:
	entity(window&, float, float, std::vector<std::string>); 
	entity(window&, float, float, const char*);

	 unsigned int FrameRate = 1;
	 window& Wnd;

};





//   #####################################
//
//                 Bullet
//
//   #####################################


