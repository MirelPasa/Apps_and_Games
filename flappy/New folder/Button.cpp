#include "Button.h"
#include "..\\Res\\resource.h"

Button::Button(HINSTANCE  mhAppInst,Type type,State state)
{
	Vec2 p0;
	switch(type)
	{
	case SinglePlayer:
		p0.x = 250;
		p0.y = 160;
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
	
	case Quit:
		p0.x = 250;
		p0.y = 240;
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
		p0.y = 320;
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
		p0.y = 400;
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
	case Difficulty:
		p0.x = 250;
		p0.y = 320;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_DIFFICULTYNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_DIFFICULTYHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_DIFFICULTYPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case NormalDifficulty:
		p0.x = 250;
		p0.y = 240;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_NORMALNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_NORMALHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_NORMALPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case HardDifficulty:
		p0.x = 250;
		p0.y = 320;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_HARDNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_HARDHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_HARDPRESSED, IDB_BUTTON_MASK, p0 );
		break;
		}
		break;
	case EasyDifficulty:
		p0.x = 250;
		p0.y = 160;
		switch(state)
		{
		case Normal:
		mButton= new Sprite ( mhAppInst, IDB_EASYNORMAL, IDB_BUTTON_MASK, p0 );
		break;
		case Highlighted:
		mButton= new Sprite ( mhAppInst, IDB_EASYHIGHLIGHTED, IDB_BUTTON_MASK, p0 );
		break;
		case Pressed:
		mButton= new Sprite ( mhAppInst, IDB_EASYPRESSED, IDB_BUTTON_MASK, p0 );
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
