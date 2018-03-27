#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
#include "Rect.h"
using namespace std;

class Player
{
public:
	enum PlayerType
	{
		Player1,
		TeamMate
	};
	enum Direction
	{
		Left,
		Right
	};
	Player(HINSTANCE mhAppInst,PlayerType player);
	virtual ~Player(void);
	void update(float dt);
	void draw ( HDC hBackBufferDC, HDC hSpriteDC );
	void ResetPosition(HINSTANCE mhAppInst,PlayerType player);
	void move(Direction dir);
	void kill();
	void ResetLives();
	Rect mPlayer1Bounds ;
	Rect mTeamMateBounds ;
	Rect mPlayerBounds;
	Sprite* mPaddle;
	bool GameOver();
	
private:
	int mLives ;
};
#endif

