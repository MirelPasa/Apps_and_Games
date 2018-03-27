#ifndef BRICK_H
#define BRICK_H
#include "Sprite.h"
using namespace std;

class Brick
{
public:
	enum Type
	{
		GrayBrick,
		BrownBrick,
		BlueBrick
	};
	Brick(HINSTANCE appInst,Type type,Vec2 p0);
	virtual~Brick(void);
	void draw(HDC hBackBufferDC, HDC hspriteHDC);
	Sprite* mBrick;
};
#endif
