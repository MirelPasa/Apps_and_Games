#include "Button.h"
#include "resource.h"

Button::Button(HINSTANCE  mhAppInst,Type type,State state)
{
	Vec2 p0;
	switch(type)
	{
	case SinglePlayer:
		p0.x = 250;
		p0.y = 180;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_SINGLEPLAYERNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_SINGLEPLAYERHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_SINGLEPLAYERPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case TeamMode:
		p0.x = 250;
		p0.y = 260;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_TEAMMODENORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_TEAMMODEHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_TEAMMODEPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case PlayervsAI:
		p0.x = 250;
		p0.y = 340;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_PLAYERVSAINORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_PLAYERVSAIHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_PLAYERVSAIPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case PlayervsPlayer:
		p0.x = 250;
		p0.y = 420;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_PLAYERVSPLAYERNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_PLAYERVSPLAYERHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_PLAYERVSPLAYERPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case Quit:
		p0.x = 250;
		p0.y = 500;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_QUITNORMAL,IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_QUITHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_QUITPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case BackToMenu:
		p0.x = 250;
		p0.y = 420;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_BACKTOMENUNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_BACKTOMENUHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_BACKTOMENUPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case Resume:
		p0.x = 250;
		p0.y = 340;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_RESUMENORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_RESUMEHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_RESUMEPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	}  
}

Button::~Button(void)
{
	delete mButton;    
}

void Button::draw( HDC hBackBufferDC, HDC hSpriteDC )
{
	mButton->draw ( hBackBufferDC, hSpriteDC );
}
