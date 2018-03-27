#include "Ball.h"
#include "resource.h"

Ball::Ball(HINSTANCE  mhAppInst,Type type)
{
    //Ball position and speed
	//The first coordinate represents x axis so in this case ball direction
	//(For example if its 0 the ball moves at a 90 degrees angle toward player
	//If its negative it goes to the left)
	//The second coordinate represents y axis so in this gase ball speed
	Vec2	v0 ( -550.0f, 550.0f );
	Circle bc;
	Vec2 p0;
    //Yellow ball position,center and radius.
	switch(type)
	{
	case YellowBall:
		p0.x = 250;
		p0.y = 400;
		bc.c = p0;
		bc.r = 7.5f;
		mBall = new Sprite ( mhAppInst, IDB_YELLOWBALL, IDB_YELLOWBALL_MASK, bc, p0, v0 );
		break;
	case BlueBall:
		p0.x = 200;
		p0.y = 400;
		bc.c = p0;
		bc.r = 7.5f;
		mBall = new Sprite ( mhAppInst, IDB_BLUEBALL, IDB_BLUEBALL_MASK, bc, p0, v0 );
		break;
	}		
}

Ball::~Ball(void)
{
	delete mBall;
}
	
void Ball::update(float dt)
{
	mBall->update(dt);	
}

void Ball::draw( HDC hBackBufferDC, HDC hSpriteDC )
{
	mBall->draw ( hBackBufferDC, hSpriteDC );
}
void Ball::ResetPosition(HINSTANCE mhAppInst,Type type)
{
	Circle bc;
	Vec2 p0;
	switch(type)
	{
	case  YellowBall:
		{
		Vec2 v0(-550.f,550.f);
		p0.x = 250;
		p0.y = 400;
		bc.c = p0;
		bc.r = 7.5f;
		mBall->mPosition=p0;
		mBall->mBoundingCircle=bc;
		mBall->mVelocity=v0;
		//mBall = new Sprite ( mhAppInst, IDB_YELLOWBALL, IDB_YELLOWBALL_MASK, bc, p0, v0 );	
		break;
		}
	case BlueBall:
		{
		Vec2 v0(-400.f,550.f);
		p0.x = 200;
		p0.y = 400;
		bc.c = p0;
		bc.r = 7.5f;
		mBall->mPosition=p0;
		mBall->mBoundingCircle=bc;
		mBall->mVelocity=v0;
		//mBall = new Sprite ( mhAppInst, IDB_BLUEBALL, IDB_BLUEBALL_MASK, bc, p0, v0 );	
		break;
		}
	}
}
