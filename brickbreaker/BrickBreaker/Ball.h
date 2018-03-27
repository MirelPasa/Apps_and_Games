#ifndef BALL_H
#define BALL_H
#include "Sprite.h"
using namespace std;

class Ball
{
public:
	enum Type
	{
		YellowBall,
		BlueBall,
	};
	Ball(HINSTANCE appInst,Type type);
	virtual~Ball(void);
	void update(float dt);
	void draw(HDC hBackBufferDC, HDC hspriteHDC);
	Sprite* mBall;
	void ResetPosition(HINSTANCE mhAppInst,Type type);	
};
#endif
