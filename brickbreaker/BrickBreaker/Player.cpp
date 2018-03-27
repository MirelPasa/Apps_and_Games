#include "Player.h"
#include <string>
#include "resource.h"

Player::Player(HINSTANCE  mhAppInst,PlayerType player)
{
	Circle bc;
	Vec2 p0;
	switch(player)
	{
	case Player1:	
	//Player1 paddle position
    p0.x = 40;
    p0.y = 622;
    bc.c = p0;
    bc.r = 35.0f;
    mPaddle = new Sprite ( mhAppInst, IDB_PLAYERPADDLE, IDB_PLAYERPADDLE_MASK, bc, p0);
	//Y coordinates are the same because i dont want
	//player to move up and down ,only left and right
	mPlayer1Bounds = Rect ( 1, 657, 246, 657 );
	mPlayerBounds= Rect ( 1, 657, 492, 657 );	
	break;	
	case TeamMate:	
	//TeamMate paddle position
    p0.x = 450;
    p0.y = 622;
    bc.c = p0;
    bc.r = 35.0f;
    mPaddle = new Sprite ( mhAppInst, IDB_TEAMMATEPADDLE, IDB_TEAMMATEPADDLE_MASK, bc, p0);
	mTeamMateBounds = Rect ( 247, 657, 492, 657 );	
	break;
	}
    mLives = 10;
}

Player::~Player(void)
{
	delete mPaddle;
}

void Player::update(float dt)
{
	mPaddle->update(dt);
}

void Player::draw(HDC hBackBufferDC, HDC hspriteDC)
{
	mPaddle->draw(hBackBufferDC, hspriteDC);
    char	lives[32];
    SetTextColor ( hBackBufferDC, RGB ( 255, 255, 255 ) );
    SetBkMode ( hBackBufferDC, TRANSPARENT );
    //Player lives
    sprintf_s ( lives, "Lives = %d",mLives );
    TextOut ( hBackBufferDC, 10, 630, lives, ( int ) strlen ( lives ) );	
}

void Player::ResetPosition(HINSTANCE mhAppInst,PlayerType player)
{
	Circle bc;
	Vec2 p0;
	switch(player)
	{
	case Player1:
	//Reset player1 paddle position
	p0.x = 40;
    p0.y = 622;
    bc.c = p0;
    bc.r = 35.f;
    mPaddle->mPosition=p0;
	mPaddle->mBoundingCircle=bc;
	break;
	case TeamMate:
	//Reset teammate paddle position
	p0.x = 455;
    p0.y = 622;
    bc.c = p0;
    bc.r = 35.f;
    mPaddle->mPosition=p0;
	mPaddle->mBoundingCircle=bc;
	break;
	}
}

void Player::move(Direction dir)
{
	switch(dir)
	{
	case Left:
	mPaddle->mPosition.x-=4;
	break;
	case Right:
	mPaddle->mPosition.x+=4;
	break;
	}
}

void Player::kill()
{
	mLives--;
}

void Player::ResetLives()
{
	mLives=10;
}

bool Player::GameOver()
{
	if (mLives<=0)return true;
	 return false;
}

