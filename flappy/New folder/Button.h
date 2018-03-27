#ifndef PARALLAXLAYER_H
#define PARALLAXLAYER_H
#include "Sprite.h"
using namespace std;

class Button
{
public:
	 enum Type
	 {
		 SinglePlayer,
		 Quit,
		 BackToMenu,
		 Resume,
		 Difficulty,
		 NormalDifficulty,
		 EasyDifficulty,
		 HardDifficulty
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
		 QUIT_NORMAL,QUIT_HIGHLIGHTED,QUIT_PRESSED,
		 BACK_NORMAL,BACK_HIGHLIGHTED,BACK_PRESSED,
		 RESUME_NORMAL,RESUME_HIGHLIGHTED,RESUME_PRESSED,
		 DIFFICULTY_NORMAL,DIFFICULTY_HIGHLIGHTED,DIFFICULTY_PRESSED,
		 EASY_NORMAL,EASY_HIGHLIGHTED,EASY_PRESSED,
		 NORMAL_NORMAL,NORMAL_HIGHLIGHTED,NORMAL_PRESSED,
		 HARD_NORMAL,HARD_HIGHLIGHTED,HARD_PRESSED
	 };
	Button();
	Button(HINSTANCE appInst,Type type,State state);
	virtual~Button(void);
	void draw(HDC hBackBufferDC, HDC hspriteHDC);
	Sprite* mButton;
};
#endif

