#ifndef PLAYER2_H
#define PLAYER2_H
#include "Sprite.h"
#include "Rect.h"
using namespace std;

class Player2
{
public:
	enum Type
	{
		AI,
		HumanPlayer2
	};
	enum Direction
	{
		Left,
		Right
	};
	Player2(HINSTANCE appInst,Type type);
	virtual~Player2(void);
	void update(float dt);
	void draw(HDC hBackBufferDC, HDC hspriteHDC);
	void ResetPosition(HINSTANCE mhAppInst,Type type);
	void move(Direction dir);
	void kill();
	void ResetLives();
	Sprite* mPaddle;
	Rect mPlayer2Bounds;
	bool GameOver();

private:
    int mLives;
};
#endif

