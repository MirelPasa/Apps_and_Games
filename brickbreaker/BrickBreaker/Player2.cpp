#include "Player2.h"
#include <string>
#include "resource.h"

Player2::Player2(HINSTANCE mhAppInst,Type type)
{
     Circle bc;
	 Vec2 p0;
	 switch(type)
	 {
	 case AI:
		//AI paddle position
		p0.x = 250;
		p0.y = 43;
		bc.c = p0;
		bc.r = 35.0f;
		mPaddle = new Sprite ( mhAppInst, IDB_AIPADDLE, IDB_AIPADDLE_MASK, bc, p0);
		//Although AI moves only left and right we need y(veritcal) coordinates to know 
		//whether the ball approaches at some point the AI paddles
		//The greater the distance between y cordinates 
		//the greater range for the AI (when the ball leaveas Y coords the AI returns to center 
		//so basically the AI has more time to do his stuff
		mPlayer2Bounds = Rect ( 1,43,492,78 );
		break;
	 case HumanPlayer2:
		 //Player2 paddle position
		p0.x = 500;
		p0.y = 43;
		bc.c = p0;
		bc.r = 35.0f;
		mPaddle = new Sprite ( mhAppInst, IDB_PLAYER2PADDLE, IDB_PLAYER2PADDLE_MASK, bc, p0);
		   
		mPlayer2Bounds = Rect ( 1,78,492,78 );
		break;
	 }
    mLives = 10;
}

Player2::~Player2(void)
{
	delete mPaddle;
}

void Player2::update(float dt)
{
	mPaddle->update(dt);
}

void Player2::draw( HDC hBackBufferDC, HDC hSpriteDC )
{
	mPaddle->draw ( hBackBufferDC, hSpriteDC );
    char	lives[32];
    SetTextColor ( hBackBufferDC, RGB ( 255, 255, 255 ) );
    SetBkMode ( hBackBufferDC, TRANSPARENT );
    //Player2 lives
    sprintf_s ( lives, "Lives = %d",mLives );
    TextOut ( hBackBufferDC, 420, 10, lives, ( int ) strlen ( lives ) );   
}

void Player2::ResetPosition(HINSTANCE mhAppInst,Type type)
{
	 Circle bc;
	 Vec2 p0;
	 switch(type)
	 {
		case AI:
		//Reset AI paddle position
		p0.x = 250;
		p0.y = 43;
		bc.c = p0;
		bc.r = 35.f;
		mPaddle->mPosition=p0;
		mPaddle->mBoundingCircle=bc;
	break;
	 case HumanPlayer2:
		//Reset Human Player2 paddle position
		p0.x = 455;
		p0.y = 43;
		bc.c = p0;
		bc.r = 35.f;
		mPaddle->mPosition=p0;
		mPaddle->mBoundingCircle=bc;
	 }
}

void Player2::move(Direction dir)
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

void Player2::kill()
{
	mLives--;
}

void Player2::ResetLives()
{	
	mLives=10;
}

bool Player2::GameOver()
{
	if (mLives<=0)return true;
	 return false;
}
