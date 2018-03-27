#include "Tube.h"
#include "..\\Res\\resource.h"
#define framewidth 800
Tube::Tube()
{}
Tube::Tube(HINSTANCE  mhAppInst,Type type,Vec2 p0)
{
	
	float fSizeFactor = 0.0f;
	int height=320;
	level=1;
	switch (type)
	{
	case Tube_Up:
		m_pTube = new Sprite ( mhAppInst, IDB_TUBE_UP, IDB_TUBE_UP_MASK,p0);
		break;
	case Tube_Down:
		m_pTube = new Sprite ( mhAppInst, IDB_TUBE_DOWN, IDB_TUBE_DOWN_MASK,p0);	
		break;
	case Tube_Up_Diagonal:
		m_pTube = new Sprite ( mhAppInst, IDB_TUBE_UP_DIAGONAL, IDB_TUBE_UP_DIAGONAL_MASK,p0);	
		break;
	case Tube_Down_Diagonal:
		m_pTube = new Sprite ( mhAppInst, IDB_TUBE_DOWN_DIAGONAL, IDB_TUBE_DOWN_DIAGONAL_MASK,p0);	
		break;
	case Tube_Facing_Left:
		m_pTube = new Sprite ( mhAppInst, IDB_TUBE_FACING_LEFT, IDB_TUBE_FACING_LEFT_MASK,p0);	
		break;
	default:
		m_pTube = NULL;
		break;
	}	
	
}

Tube::~Tube(void)
{
	delete m_pTube;
}
	
void Tube::draw( HDC hBackBufferDC, HDC hSpriteDC )
{
	// Draw if visibility condition is satisfied
	if ((m_pTube->mPosition.x-m_pTube->GetWidth()<800)&&(m_pTube->mPosition.x+m_pTube->GetWidth()>0))
		m_pTube->draw ( hBackBufferDC, hSpriteDC );
}

void Tube::update(float dt)
{
	collision=false;
	//lock this because level 1 tubes moves only horizontal
	if( level==1)
	{
	m_pTube->mVelocity.y=0;
	m_pTube->mVelocity.x=-110;
	}
		else
		if (level==2)
		{
		//i want the tubes to move left even if i dont see them
		m_pTube->mVelocity.x=-110;
		//i dont want to move the tubes up and down untill i see them
		if ((m_pTube->mPosition.x-m_pTube->GetWidth()<800)&&(m_pTube->mPosition.x+m_pTube->GetWidth()>0))
			{
			m_pTube->mVelocity.y=-10;
			}
		}
		else
		if (level==3)
		{
		//i want the tubes to move left even if i dont see them
		m_pTube->mVelocity.x=-110;
		//i dont want to move the tubes up and down untill i see them
		if ((m_pTube->mPosition.x-m_pTube->GetWidth()<800)&&(m_pTube->mPosition.x+m_pTube->GetWidth()>0))
			{
			m_pTube->mVelocity.y=+10;
			}
		}
		else
		if (level==4)
		{
		//i want the tubes to move left even if i dont see them
		m_pTube->mVelocity.x=-110;
		//i dont want to move the tubes up and down untill i see them
		if ((m_pTube->mPosition.x-m_pTube->GetWidth()<800)&&(m_pTube->mPosition.x+m_pTube->GetWidth()>0))
			{
			if (randommoving==1)
			m_pTube->mVelocity.y=-10;
			if (randommoving==2)
			m_pTube->mVelocity.y=+10;
			}
		}
	m_pTube->update(dt);	
}

void Tube::setrandomlevel(int k)
{
	if( k%2==0)
	randommoving=1;
	if( k%2==1)
	randommoving=2;
}

void Tube::setlevel(int lvl)
{
	level=lvl;
}

//if ..
bool Tube::Expired() const
{
	if (collision==true)
	return true;
	else return false;
	

	
}