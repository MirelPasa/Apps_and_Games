#ifndef BRICKBREAKERGAME_H_
#define BRICKBREAKERGAME_H_
#include <Windows.h>
#include "Sprite.h"
#include "Rect.h"
#include "Circle.h"
#include "Player2.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Button.h"
#include <list>
#include <vector>
#include<map>
#include <memory>
using namespace std;

class BrickBreakerGame
{

public:
    BrickBreakerGame ( HINSTANCE hAppInst, HWND hMainWnd, Vec2 wndCenterPt );
   virtual ~BrickBreakerGame ();
    void	update ( float dt );
    void	draw ( HDC hBackBufferDC, HDC hSpriteDC );
    void	pause ( void );
    void	unpause ( void );
	void ProcessInput();
	bool mPaused;
private:
	BrickBreakerGame ( const BrickBreakerGame &rhs );
	BrickBreakerGame &operator	= ( const BrickBreakerGame &rhs );
private:
	int Collision(Sprite*sprite1,Sprite*sprite2);
	void UpdatePlayer1 ( float dt );
	void UpdateTeamMate ( float dt );
	void CheckAllBallCollisions(Sprite *ball);
	void AdvanceLevel();
	void UpdateAI(float dt);
	void UpdateHumanPlayer2(float dt);
	void UpdateBall(float dt);
	void BallWallCollision ( Sprite *ball );
	void Resetallobjects();
	void showCursor(bool cursor);
	void KeyCheckRoutine( void );
	void CheckMenuButton();
	void LevelHandler(Brick *brick, Sprite *ball);
	void BrickBallCollision (vector<Brick*>Brick, Sprite *ball );
	void BuildObjects();
	void BuildButtons();
	void BuildBalls();
	void BuildBricks();
	void BuildPlayers();
	void BuildBackgrounds();
	void Init();
	void DrawGameplay(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawMenu(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawSubMenu(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawGameOver(HDC hBackBufferDC, HDC hSpriteDC);	
private:
	bool OnMouseOver ( Sprite *spr );	
	bool LastFrame;
	bool KeyDown;
    bool PaddleBallCollision ( Sprite *paddle, Sprite *ball );
	bool GameCompleted;
	bool KeyReleased;
private:
	int mNumberOfBricksDestroyed;
	int mLevel;
    float			MAX_BALL_SPEED;
	const float			AI_SPEED;
	const int MaxLevel;
private:
	Player* mPlayer;
	Player* mTeamMate;
	Player2* mPlayer2;
	Player2* mAI;
	Ball *mYellowBall;
	Ball *mBlueBall;
	Sprite *mMenu;
	Sprite* mGameBoard;
	Sprite *mGameCompleted;
	Sprite *mGameOver;
	Sprite *mWin;
	Sprite *mLose;
std::map<Button::Buttons,Button*> mButton;
	vector<Brick* >	mGrayBricks;
	vector<Brick* >	mBrownBricks;
	vector<Brick* >	mBlueBricks;
	vector<Brick* >	Bricks;
private:
	Vec2 p0;
	Circle bc;
	Rect mBoardBounds;
private:
    HINSTANCE			mhAppInst;
    HWND				mhMainWnd;
    Vec2				mWndCenterPt;   
};
#endif 
