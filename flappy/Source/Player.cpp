#include "Player.h"
#include <string>
#include "..\\Res\\resource.h"
#define FLAP_SPEED_IMPULSE -250

Player::Player(HINSTANCE  mhAppInst)
{
	Vec2 p0;
	p0.x = 40;
    p0.y =422;
	mpSprite=new Sprite ( mhAppInst, IDB_BIRD, IDB_BIRD_MASK,p0);
	mScore=0;
}

Player::~Player(void)
{
	delete mpSprite;
}

void Player::update(float dt)
{
	mpSprite->update(dt);
}

void Player::draw(HDC hBackBufferDC, HDC hspriteDC)
{
	mpSprite->draw(hBackBufferDC, hspriteDC);

	char	score[32];
    SetTextColor ( hBackBufferDC, RGB ( 255, 255, 255 ) );
    SetBkMode ( hBackBufferDC, TRANSPARENT );
    //Player2 lives
    sprintf_s ( score, "Score = %d",mScore );
    TextOut ( hBackBufferDC, 10, 10, score, ( int ) strlen ( score ) );   

}

void Player::Flap()
{
	mpSprite->mVelocity.y = FLAP_SPEED_IMPULSE;
}


void Player::Score()
{
	mScore=(mScore+1);
	PlaySound("Data/score.wav", NULL, SND_FILENAME | SND_ASYNC);
}

