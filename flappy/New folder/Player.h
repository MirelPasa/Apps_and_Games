#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
using namespace std;

class Player
{
public:
	enum Direction
	{
		Left,
		Right
	};
	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//------------------------------------------------------------------------
	Player(HINSTANCE mhAppInst);
	virtual ~Player();
	void update(float dt);
	void draw ( HDC hBackBufferDC, HDC hSpriteDC );
	void Flap();	
	void Score();
	Sprite* mpSprite;
	int mScore;
	
private:
	
};
#endif // _CPLAYER_H_