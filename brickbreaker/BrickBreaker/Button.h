#ifndef BUTTON_H
#define BUTTON_H
#include "Sprite.h"
using namespace std;

class Button
{
public:
	 enum Type
	 {
		 SinglePlayer,
		 TeamMode,
		 PlayervsAI,
		 PlayervsPlayer,
		 Quit,
		 BackToMenu,
		 Resume
	 };
	 enum State
	 {
		 Normal,
		 Highlighted,
		 Pressed
	 };
	 enum Buttons
	 {
		 SINGLEPLAYER_NORMAL,SINGLEPLAYER_HIGHLIGHTED,SINGLEPLAYER_PRESSED,
		 TEAMMODE_NORMAL,TEAMMODE_HIGHLIGHTED,TEAMMODE_PRESSED,
		 PLAYERVSAI_NORMAL,PLAYERVSAI_HIGHLIGHTED,PLAYERVSAI_PRESSED,
		 PLAYERVSPLAYER_NORMAL,PLAYERVSPLAYER_HIGHLIGHTED,PLAYERVSPLAYER_PRESSED,
		 QUIT_NORMAL,QUIT_HIGHLIGHTED,QUIT_PRESSED,
		 BACK_NORMAL,BACK_HIGHLIGHTED,BACK_PRESSED,
		 RESUME_NORMAL,RESUME_HIGHLIGHTED,RESUME_PRESSED
	 };
	 Button();
	Button(HINSTANCE appInst,Type type,State state);
	virtual~Button(void);
	void draw(HDC hBackBufferDC, HDC hspriteHDC);
	Sprite* mButton;	
};
#endif

