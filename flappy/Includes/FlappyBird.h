#ifndef FLAPPYBIRD_H_
#define FLAPPYBIRD_H_
#include <Windows.h>
#include <string>
#include "BackBuffer.h"
#include "Sprite.h"
#include "Player.h"
#include "Tube.h"
#include "Button.h"
#include <list>
#include <vector>
#include<map>
#include <memory>
#include "ParallaxLayer.h"
#include "..\\Res\\resource.h"
#include <ctime>
#include "Projectile.h"
#include <algorithm>    // std::remove_if
#include <list>
#include "Rect.h"
#include <string>
using namespace std;

class FlappyBird
{
public:
	

	FlappyBird();
    FlappyBird ( HINSTANCE hAppInst, HWND hMainWnd, Vec2 wndCenterPt );
	virtual ~FlappyBird ();
    void	update ( float dt );
    void	draw ( HDC hBackBufferDC, HDC hSpriteDC );
	void ProcessInput();
    void	pause ( void );
    void	unpause ( void );
	void addProjectile();
	bool mPaused;
	int nr_of_projectiles;
	
private:
	
	void RefillAmmunition();
	void UpdateProjectiles(float dt);
	void Score();
	void CheckMechanics();
	void PlayerTubeCollision ( );
	void UpdatePlayer1 ( float dt );
	void UpdateTubes ( float dt );
	void UpdateCoins(float dt);
	void UpdateParallax ( float dt );
	void ResetGame();
	void showCursor(bool cursor);
	void KeyCheckRoutine( void );
	void CheckMenuButton();
	void LevelHandler(Tube *tube, Sprite *player);
	void BuildObjects();
	void BuildButtons();
	void BuildTubes();
	void BuildPlayer();
	void BuildBackgrounds();
	void BuildCoins();
	void Init();
	void DrawGameplay(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawMenu(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawDifficultyMenu(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawSubMenu(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawGameOver(HDC hBackBufferDC, HDC hSpriteDC);
	void DrawCoins(HDC hBackBufferDC, HDC hSpriteDC);
	int Collision(Sprite*sprite1,Sprite*sprite2);
	bool OnMouseOver ( Sprite *spr );


private:
	bool LastFrame;
	bool KeyDown;
	bool GameCompleted;
	bool KeyReleased;
	bool dead;
	float gap;
	float horizontal_gap;
	float mtimer;
	const float tube_height;	
	const float tube_width;	
	int nr_of_passed_tubes;
	int save_nr_of_passed_tubes;
	int mLevel;

private:
	Sprite* mCoin;
	Player* mPlayer;
	Tube *mTube;
	ParallaxLayer*mParallaxLayer;
	Sprite *mMenu;
	Sprite* mGameBoard;
	Sprite *mGameCompleted;
	Sprite *mGameOver;
	Sprite *mWin;
	Sprite *mLose;
	std::map<Button::Buttons,Button*> mButton;
	vector<Tube* >	mTubes;
	vector<Sprite* >mCoins;
	vector<int> score_counted;
	vector<Projectile*> mProjectiles;
	bool removetube[100];
	bool removeprojectile[100];
	Vec2 savetubeposition[100];


	bool objectexists[100];
private:
    HINSTANCE			mhAppInst;

private:
    HWND				mhMainWnd;

private:
    Vec2				mWndCenterPt;  
	Vec2 p0;
	Vec2 v0;
private:
	POINT mLastMousePos;
	POINT mCurrMousePos;
	Rect mBoardBounds;
};

#endif 
