#include "ParallaxLayer.h"
#include <string>
#include "..\\Res\\resource.h"
#define PARALLAX_BACKGROUND_SPEED 110

ParallaxLayer::ParallaxLayer(HINSTANCE  mhAppInst,Vec2 p0)
{
	m_pSprite=new Sprite ( mhAppInst,IDB_LAYER, IDB_LAYER_MASK,p0);
}


ParallaxLayer::~ParallaxLayer()
{
    delete m_pSprite;
}

void ParallaxLayer::draw(HDC hBackBufferDC, HDC hspriteDC)
{
	 m_pSprite->draw(hBackBufferDC, hspriteDC);
  
}
void ParallaxLayer::update(float dt)
{
}

void ParallaxLayer::Move(ULONG ulDirection)
{
    if( ulDirection & ParallaxLayer::DIR_RIGHT )
    {
		m_pSprite->mVelocity.x = -(float)PARALLAX_BACKGROUND_SPEED;
    }

    if( ulDirection & ParallaxLayer::DIR_LEFT )
    {
        m_pSprite->mVelocity.x = (float)PARALLAX_BACKGROUND_SPEED;
    }

    if( ulDirection & ParallaxLayer::DIR_FORWARD )
    {
		m_pSprite->mVelocity.y = (float)PARALLAX_BACKGROUND_SPEED;
    }

    if( ulDirection & ParallaxLayer::DIR_BACKWARD )
    {
		m_pSprite->mVelocity.y = -(float)PARALLAX_BACKGROUND_SPEED;
    }

}



