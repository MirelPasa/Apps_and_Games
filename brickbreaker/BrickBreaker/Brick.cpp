#include "Brick.h"
#include "resource.h"

Brick::Brick(HINSTANCE  mhAppInst,Type type,Vec2 p0)
{
	switch(type)
	{
	case GrayBrick:	
		mBrick = new Sprite ( mhAppInst, IDB_GRAYBRICK, IDB_GRAYBRICK_MASK,p0);
		break;
	case BrownBrick:
		mBrick = new Sprite ( mhAppInst, IDB_BROWNBRICK, IDB_BROWNBRICK_MASK,p0);
		break;
	case BlueBrick:
		mBrick = new Sprite ( mhAppInst, IDB_BLUEBRICK, IDB_BLUEBRICK_MASK,p0);
		break;
	}		
}

Brick::~Brick(void)
{
	delete mBrick;
}
	
void Brick::draw( HDC hBackBufferDC, HDC hSpriteDC )
{
	mBrick->draw ( hBackBufferDC, hSpriteDC );
}

