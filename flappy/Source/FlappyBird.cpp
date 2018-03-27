#include "FlappyBird.h"
using namespace std;

#define GRAVITATIONAL_CONSTANT 10
#define PIXEL_PER_METERS 20
#define MEDIUM_VISCOSITY 0.5f

enum Mousestate
{
	down,
	up
};
Mousestate prevstate;


enum Gamestates
{
	Gameplaystate,
	Menustate,
	Gameoverstate,
	Submenustate,
	DifficultyMenuState
};
Gamestates gamestate=Gamestates::Menustate;

enum Difficulty
{
	Easy,
	Normal,
	Hard
};
Difficulty difficulty=Difficulty::Easy;

Button::State SinglePlayerButton=Button::Normal;
Button::State QuitButton=Button::Normal;
Button::State ResumeButton=Button::Normal;
Button::State BackToMenuButton=Button::Normal;
Button::State DifficultyButton=Button::Normal;
Button::State NormalDifficultyButton=Button::Normal;
Button::State EasyDifficultyButton=Button::Normal;
Button::State HardDifficultyButton=Button::Normal;

FlappyBird :: FlappyBird ( HINSTANCE hAppInst, HWND hMainWnd, Vec2 wndCenterPt ):
	tube_height(500),
	tube_width(52)
{
    // Save input parameters.
    mhAppInst = hAppInst;
    mhMainWnd = hMainWnd;
	mWndCenterPt=wndCenterPt;
	//Init variables
	Init();
	//Build GameObjects
	BuildObjects();
}

void FlappyBird::Init()
{
	// The game is initially paused.
	mPaused    = true;
	//Variables for checking mouse clicks
	KeyReleased=false;
	LastFrame = false;
	KeyDown = false;
	//Vector with the size of the tubes to check whether the player has scored
	//At first no point was scored so initialize the vector with false
	score_counted.resize(mTubes.size());
	for(int i=0;i<score_counted.size();i++)
	score_counted[i]=false;
	//Timer for checking timing actions(such as playing sounds ..)
	mtimer=0;
	//player starts with 1 projectile at hand
	nr_of_projectiles=1;
	//Board bounds(useful when deleting unnecessay objects that cant be seen on the screen)
	mBoardBounds = Rect ( 0, 0, 1366, 768 );
	//At first player hasnt passed any tube
	nr_of_passed_tubes=0;
	save_nr_of_passed_tubes=0;
	//difficulty=easy;
	gap=75;//at first gap is 75 because its on easy difficulty
	horizontal_gap=75;//at first horizontal_gap is 75 because its on easy difficulty


	//
	for(int i=0;i<mCoins.size();i++)
		objectexists[i]=false;
}

//Here i build all game objects(backgrounds,tubes,buttons and player)
void FlappyBird::BuildObjects()
{
	BuildBackgrounds();
	BuildTubes();
	BuildButtons();
	BuildPlayer();
	BuildCoins();
}
void FlappyBird::BuildButtons()
{
	mButton[Button::SINGLEPLAYER_NORMAL]=new  Button(mhAppInst,Button::SinglePlayer,Button::Normal);
	mButton[Button::SINGLEPLAYER_HIGHLIGHTED]=new Button(mhAppInst,Button::SinglePlayer,Button::Highlighted);
	mButton[Button::SINGLEPLAYER_PRESSED]=new  Button(mhAppInst,Button::SinglePlayer,Button::Pressed);
	mButton[Button::QUIT_NORMAL]=new Button(mhAppInst,Button::Quit,Button::Normal);
	mButton[Button::QUIT_HIGHLIGHTED]=new  Button(mhAppInst,Button::Quit,Button::Highlighted);
	mButton[Button::QUIT_PRESSED]=new  Button(mhAppInst,Button::Quit,Button::Pressed);
	mButton[Button::BACK_NORMAL]=new Button(mhAppInst,Button::BackToMenu,Button::Normal);
	mButton[Button::BACK_HIGHLIGHTED]=new Button(mhAppInst,Button::BackToMenu,Button::Highlighted);
	mButton[Button::BACK_PRESSED]=new Button(mhAppInst,Button::BackToMenu,Button::Pressed);
	mButton[Button::RESUME_NORMAL]=new  Button(mhAppInst,Button::Resume,Button::Normal);
	mButton[Button::RESUME_HIGHLIGHTED]=new Button(mhAppInst,Button::Resume,Button::Highlighted);
	mButton[Button::RESUME_PRESSED]=new  Button(mhAppInst,Button::Resume,Button::Pressed);
	mButton[Button::DIFFICULTY_NORMAL]=new  Button(mhAppInst,Button::Difficulty,Button::Normal);
	mButton[Button::DIFFICULTY_HIGHLIGHTED]=new Button(mhAppInst,Button::Difficulty,Button::Highlighted);
	mButton[Button::DIFFICULTY_PRESSED]=new  Button(mhAppInst,Button::Difficulty,Button::Pressed);
	mButton[Button::NORMAL_NORMAL]=new  Button(mhAppInst,Button::NormalDifficulty,Button::Normal);
	mButton[Button::NORMAL_HIGHLIGHTED]=new Button(mhAppInst,Button::NormalDifficulty,Button::Highlighted);
	mButton[Button::NORMAL_PRESSED]=new  Button(mhAppInst,Button::NormalDifficulty,Button::Pressed);
	mButton[Button::HARD_NORMAL]=new  Button(mhAppInst,Button::HardDifficulty,Button::Normal);
	mButton[Button::HARD_HIGHLIGHTED]=new Button(mhAppInst,Button::HardDifficulty,Button::Highlighted);
	mButton[Button::HARD_PRESSED]=new  Button(mhAppInst,Button::HardDifficulty,Button::Pressed);
	mButton[Button::EASY_NORMAL]=new  Button(mhAppInst,Button::EasyDifficulty,Button::Normal);
	mButton[Button::EASY_HIGHLIGHTED]=new Button(mhAppInst,Button::EasyDifficulty,Button::Highlighted);
	mButton[Button::EASY_PRESSED]=new  Button(mhAppInst,Button::EasyDifficulty,Button::Pressed);
}
void FlappyBird::BuildTubes()
{
	if (difficulty==Difficulty::Hard)
		gap=75;
	else
	if (difficulty==Difficulty::Normal)
		gap=80;
	else
	if (difficulty==Difficulty::Easy)
		gap=85;


	//srand(time(0));

	int top_tube_vertical_pos;
	int bottom_tube_vertical_pos;
	//first tube horizontal position
	int top_tube_horizontal_pos=400;
	int botoom_tube_horizontal_pos=400;

	int tube_facing_left_vertical_pos;
	int tube_facing_left_horizontal_pos;


	int i=0;

			//level 1 tubes(stationary tubes)
			for(i=0;i<5;i++)
			{
			//random vertical position
			 top_tube_vertical_pos =-150+rand()%(100+150);
			p0=Vec2(float(top_tube_horizontal_pos),float( top_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Down,p0);
			mTubes.push_back(mTube);

			bottom_tube_vertical_pos = top_tube_vertical_pos+tube_height+gap;//145-410
			p0=Vec2(float(botoom_tube_horizontal_pos),float(bottom_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Up,p0);
			mTubes.push_back(mTube);
			
			//next tube horizntal position 
			top_tube_horizontal_pos=top_tube_horizontal_pos+200;
			botoom_tube_horizontal_pos=botoom_tube_horizontal_pos+200;		
			}
			//level 2 tubes(moving up)
			for(i=0;i<10;i++)
			{			
			//random vertical position
			 top_tube_vertical_pos =-150+rand()%(100+150);
			p0=Vec2(float(top_tube_horizontal_pos),float( top_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Down,p0);
			mTubes.push_back(mTube);
			mTube->setlevel(2);

			bottom_tube_vertical_pos = top_tube_vertical_pos+tube_height+gap;
			p0=Vec2(float(botoom_tube_horizontal_pos),float(bottom_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Up,p0);
			mTubes.push_back(mTube);
			mTube->setlevel(2);
			//next tube horizntal position 
			top_tube_horizontal_pos=top_tube_horizontal_pos+200;
			botoom_tube_horizontal_pos=botoom_tube_horizontal_pos+200;	
			}
			//level 3 tubes(moving down)
			for(i=0;i<10;i++)
			{			
			//random vertical position
			 top_tube_vertical_pos =-150+rand()%(100+150);
			p0=Vec2(float(top_tube_horizontal_pos),float( top_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Down,p0);
			mTubes.push_back(mTube);
			mTube->setlevel(3);

			bottom_tube_vertical_pos = top_tube_vertical_pos+tube_height+gap;
			p0=Vec2(float(botoom_tube_horizontal_pos),float(bottom_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Up,p0);
			mTubes.push_back(mTube);
			mTube->setlevel(3);
			//next tube horizntal position 
			top_tube_horizontal_pos=top_tube_horizontal_pos+200;
			botoom_tube_horizontal_pos=botoom_tube_horizontal_pos+200;	
			}

			//level 4 tubes(moving up and down at random)
			for(i=0;i<10;i++)
			{
			int k=0+rand()%5;
			
			//random vertical position
			 top_tube_vertical_pos =-150+rand()%(100+150);
			p0=Vec2(float(top_tube_horizontal_pos),float( top_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Down,p0);
			mTubes.push_back(mTube);
			mTube->setlevel(4);
			mTube->setrandomlevel(k);

			bottom_tube_vertical_pos = top_tube_vertical_pos+tube_height+gap;
			p0=Vec2(float(botoom_tube_horizontal_pos),float(bottom_tube_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Up,p0);
			mTubes.push_back(mTube);
			mTube->setlevel(4);
			mTube->setrandomlevel(k);
			//next tube horizntal position 
			top_tube_horizontal_pos=top_tube_horizontal_pos+200;
			botoom_tube_horizontal_pos=botoom_tube_horizontal_pos+200;	
			}

			//level 5 tubes are different tubes than those before,and 
			//are created right after level4 tubes so i need to save the position
			//of the last level 4 tubes
			tube_facing_left_horizontal_pos=top_tube_horizontal_pos+200;
			tube_facing_left_vertical_pos=50;
			int save=tube_facing_left_vertical_pos;
			//level 6 tubes(stationary tubes facing you)
			for(i=0;i<4;i++)
			{
			p0=Vec2(float(tube_facing_left_horizontal_pos),float(tube_facing_left_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Facing_Left,p0);
			mTubes.push_back(mTube);	
			//next tube vertical position 
			tube_facing_left_vertical_pos=tube_facing_left_vertical_pos+tube_width+gap;

			}
			//another set of level 5 tubes
			tube_facing_left_horizontal_pos=tube_facing_left_horizontal_pos+600;
			tube_facing_left_vertical_pos=save+60;
			//level 6 tubes(stationary tubes facing you)
			for(i=0;i<3;i++)
			{
			p0=Vec2(float(tube_facing_left_horizontal_pos),float(tube_facing_left_vertical_pos));
			mTube=new Tube( mhAppInst,Tube::Tube_Facing_Left,p0);
			mTubes.push_back(mTube);	
			//next tube vertical position 
			tube_facing_left_vertical_pos=tube_facing_left_vertical_pos+tube_width+gap;

			}


			
			
}	
//Functia pentru crearea monezilor
void FlappyBird::BuildCoins()
{
	//a+rand()%(b+1-a) genereaza un numar aleator cuprins intre a si b.
	srand(time(0));
	
	int coin_x_pos;
	int coin_y_pos;

	//first coin horizontal position
	coin_x_pos=500;
	int i=0;

			//the number of coins is equal to the number of tubes
			for(i=0;i<mTubes.size()/2-1;i++)
			{
			//random vertical position between 20 and 490
			coin_y_pos =20+rand()%(471);
			p0=Vec2(float(coin_x_pos),float( coin_y_pos));

			//make the coin's x speed equal to tube's x speed so that 
			//the coin looks stationary on x axis
			v0.x=-110;
			//random y speed between -20 and 20
			v0.y=-50;
			mCoin = new Sprite ( mhAppInst, IDB_COIN, IDB_COIN_MASK,p0,v0);
			mCoins.push_back(mCoin);

			//next coin horizntal position 
			coin_x_pos=coin_x_pos+200;

			objectexists[i]=true;
			}
}	


void FlappyBird::BuildBackgrounds()
{
	const int			gClientWidth = 800;
	const int			gClientHeight = 512;
	//Center point of client rectangle
	const POINT			wndCenterPt = { gClientWidth / 2, gClientHeight / 2 };
	p0 = wndCenterPt;
	mGameBoard = new Sprite ( mhAppInst, IDB_GAMEBOARD, IDB_GAMEBOARD_MASK,p0 );
	mMenu = new Sprite ( mhAppInst, IDB_MENUSCREEN, IDB_MENUSCREEN_MASK,p0 );
	mGameOver = new Sprite(mhAppInst, IDB_GAMEOVER, IDB_GAMEOVER_MASK,p0 );
	p0 = wndCenterPt;
	mParallaxLayer=new ParallaxLayer(mhAppInst,p0);
	mParallaxLayer->Move(ParallaxLayer::DIR_RIGHT);

}
void FlappyBird::BuildPlayer()
{
	mPlayer=new Player( mhAppInst);
}
//Function for showing and hiding the cursor;
//The cursor is displayed until counter is smaller than 0;
//The cursor is hidden until counter is equal or greater than 0.
void FlappyBird::showCursor(bool show)
{
      if (show)
            while (ShowCursor(TRUE) < 0);
      else
            while (ShowCursor(FALSE) >= 0);
}

FlappyBird :: ~FlappyBird ( void )
{
	delete mGameBoard;
	delete mPlayer;
	delete mMenu;
	delete mGameOver;
	for(std::map<Button::Buttons,Button*>::iterator MapItor = mButton.begin(); MapItor != mButton.end(); ++MapItor)
	{
		Button* Value = MapItor->second;
		delete Value;
	}
	mButton.clear();
	while(!mTubes.empty()) delete mTubes.back(),mTubes.pop_back();
	while(!mCoins.empty()) delete mCoins.back(),mCoins.pop_back();
	delete  mParallaxLayer;
	while(!mProjectiles.empty()) delete mProjectiles.back(), mProjectiles.pop_back();
}

void FlappyBird :: pause ( void )
{   //If in gameplay state,right after pause
	//change state to submenu state
	if (gamestate==Gameplaystate)
	{
		mPaused = true;
		showCursor(true);
		gamestate=Submenustate;
	}
	//When the game is over for example furthermore i want it to be paused
	//But pausing it returns it to submenu state(and i dont want),
	//To rezolve this i test the current state(if its not gameplaystate)
	//Just pause it without going to submenu
	if (gamestate!=Gameplaystate)
	{
		mPaused = true;
		showCursor(true);
	}
}

void FlappyBird :: unpause ( void )
{   //I dont want unpause button to be checked in menu or after the game is over
	if ((gamestate!=Menustate) && (gamestate!=Gameoverstate))
	{
		mPaused = false;
		showCursor(false);
		gamestate=Gameplaystate;
	}
}

void FlappyBird :: update ( float dt )
{  
	// Only update the game if the game is not paused.
    if ( !mPaused )
    {
        UpdatePlayer1 ( dt );
		UpdateTubes ( dt );
		CheckMechanics();
		UpdateCoins(dt);
		mtimer=mtimer+dt;
		if(!mProjectiles.empty())
			UpdateProjectiles(dt);
    }
}

void FlappyBird::DrawGameplay(HDC hBackBufferDC, HDC hSpriteDC)
{
	mParallaxLayer->draw ( hBackBufferDC, hSpriteDC );	
	for ( int i = 0; i < mTubes.size(); i++ )
		{
			mTubes[i]->draw ( hBackBufferDC, hSpriteDC );
		}
	mPlayer->draw ( hBackBufferDC, hSpriteDC ); 

	
	for ( int i = 0; i < mProjectiles.size(); i++ )
	{
		mProjectiles[i]->draw( hBackBufferDC, hSpriteDC );
	}

	
	//Dont draw coins outside the window for better performance
	// Draw if visibility condition is satisfied
	for ( int i = 0; i < mCoins.size(); i++ )
	{
		if (objectexists[i])
	if ((mCoins[i]->mPosition.x-mCoins[i]->GetWidth()<800)&&(mCoins[i]->mPosition.x+mCoins[i]->GetWidth()>0))
		
		mCoins[i]->draw ( hBackBufferDC, hSpriteDC );
	}

	char	nrofprojectiles[32];
    SetTextColor ( hBackBufferDC, RGB ( 255, 255, 255 ) );
    SetBkMode ( hBackBufferDC, TRANSPARENT );
    //Player2 lives
    sprintf_s ( nrofprojectiles, "Projectiles = %d",nr_of_projectiles );
    TextOut ( hBackBufferDC, 10, 30, nrofprojectiles, ( int ) strlen ( nrofprojectiles ) );  

	char	nroftubespassed[32];
    SetTextColor ( hBackBufferDC, RGB ( 255, 255, 255 ) );
    SetBkMode ( hBackBufferDC, TRANSPARENT );
    //Player2 lives
    sprintf_s ( nroftubespassed, "Passed tubes = %d",save_nr_of_passed_tubes );
    TextOut ( hBackBufferDC, 10, 50, nroftubespassed, ( int ) strlen ( nroftubespassed ) );   
}

void FlappyBird::DrawMenu(HDC hBackBufferDC,HDC hSpriteDC )
{
	mMenu->draw ( hBackBufferDC, hSpriteDC );
	//Draw SinglePlayer buttons
	switch(SinglePlayerButton)
	{
	case Button::Normal:
		mButton[Button::SINGLEPLAYER_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::SINGLEPLAYER_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::SINGLEPLAYER_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}
	
	//Draw Quit buttons
	switch(QuitButton)
	{
	case Button::Normal:
		mButton[Button::QUIT_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::QUIT_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::QUIT_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}	

	//Draw Quit buttons
	switch(DifficultyButton)
	{
	case Button::Normal:
		mButton[Button::DIFFICULTY_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::DIFFICULTY_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::DIFFICULTY_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}	
}
void FlappyBird::DrawSubMenu(HDC hBackBufferDC, HDC hSpriteDC)
{
	switch(QuitButton)
	{
	case Button::Normal:
		mButton[Button::QUIT_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::QUIT_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
	break;
	case Button::Pressed:
		mButton[Button::QUIT_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}		
	//Draw BacktoMenu buttons
	switch(BackToMenuButton)
	{
	case Button::Normal:
		mButton[Button::BACK_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::BACK_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::BACK_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}	
	//Draw Resume buttons
	switch(ResumeButton)
	{
	case Button::Normal:
		mButton[Button::RESUME_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::RESUME_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::RESUME_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}

	//Draw SinglePlayer buttons
	switch(SinglePlayerButton)
	{
	case Button::Normal:
		mButton[Button::SINGLEPLAYER_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::SINGLEPLAYER_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::SINGLEPLAYER_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}
}
void FlappyBird::DrawGameOver( HDC hBackBufferDC, HDC hSpriteDC )
{	
	mGameOver->draw ( hBackBufferDC, hSpriteDC );
	
	//Draw Quit buttons
	switch(QuitButton)
	{
	case Button::Normal:
		mButton[Button::QUIT_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::QUIT_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::QUIT_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}
	//Draw BacktoMenu buttons
	switch(BackToMenuButton)
	{
	case Button::Normal:
		mButton[Button::BACK_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::BACK_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::BACK_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}

	switch(SinglePlayerButton)
	{
	case Button::Normal:
		mButton[Button::SINGLEPLAYER_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::SINGLEPLAYER_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::SINGLEPLAYER_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}
}
void FlappyBird::DrawDifficultyMenu(HDC hBackBufferDC,HDC hSpriteDC )
{
	
	mMenu->draw ( hBackBufferDC, hSpriteDC );
	//Draw SinglePlayer buttons
	switch(EasyDifficultyButton)
	{
	case Button::Normal:
		mButton[Button::EASY_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::EASY_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::EASY_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}

	//Draw SinglePlayer buttons
	switch(NormalDifficultyButton)
	{
	case Button::Normal:
		mButton[Button::NORMAL_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::NORMAL_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::NORMAL_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}

	//Draw SinglePlayer buttons
	switch(HardDifficultyButton)
	{
	case Button::Normal:
		mButton[Button::HARD_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::HARD_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::HARD_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}		
}
void FlappyBird :: draw ( HDC hBackBufferDC, HDC hSpriteDC )
{
	switch(gamestate)
	{
	case Gameplaystate:
		DrawGameplay (hBackBufferDC,hSpriteDC );
		break;
	case Menustate:
		DrawMenu(hBackBufferDC,hSpriteDC );
		break;
	case Submenustate:
		DrawSubMenu(hBackBufferDC,hSpriteDC );
		break;
	case Gameoverstate:
		DrawGameOver(hBackBufferDC,hSpriteDC );
		break;
	case DifficultyMenuState:
		DrawDifficultyMenu(hBackBufferDC,hSpriteDC );
		break;
	}
}

//Function for resetting all objects and variables;
//needed when starting a new game. 
void FlappyBird::ResetGame()
{
	Init();
	delete mPlayer;
	BuildPlayer();
	while(!mTubes.empty()) delete mTubes.back(), mTubes.pop_back();
	BuildTubes();
	while(!mCoins.empty()) delete mCoins.back(), mCoins.pop_back();
	BuildCoins();
	while(!mProjectiles.empty()) delete mProjectiles.back(), mProjectiles.pop_back();
}

void FlappyBird::UpdatePlayer1(float dt)
{
   // PlayerTubeCollision();
	Vec2 a;
	// apply gravity
	a.y = GRAVITATIONAL_CONSTANT * PIXEL_PER_METERS;

	// apply Stokes law. For more info see: http://en.wikipedia.org/wiki/Stokes'_law
	a += mPlayer->mpSprite->mVelocity * (-MEDIUM_VISCOSITY);
	
	// Update the sprites position and speed
	mPlayer->mpSprite->mPosition += mPlayer->mpSprite->mVelocity * dt + a * dt * dt / 2;
	mPlayer->mpSprite->mVelocity += a * dt*4;		
}

void FlappyBird::UpdateTubes(float dt)
{
    // Update the player paddle's position.
	for(int i=0;i<mTubes.size();i++)
    mTubes[i]->update ( dt );
}
void FlappyBird::UpdateCoins(float dt)
{
    // Update the player paddle's position.
	for(int i=0;i<mCoins.size();i++)
	{
		if (objectexists[i])
		{
			mCoins[i]->update ( dt );
			if ((mCoins[i]->mPosition.y-mCoins[i]->GetHeight()/2<=0)||
				(mCoins[i]->mPosition.y+mCoins[i]->GetHeight()/2>=512))
				{
					mCoins[i]->mVelocity.y=-mCoins[i]->mVelocity.y;
				} 
		if (Collision(mPlayer->mpSprite,mCoins[i]))
		{
			mPlayer->Score();
			delete mCoins[i];
			mCoins[i]=0;
			objectexists[i]=false;
		}
		}
		
	}
	
}

int FlappyBird::Collision(Sprite*sprite1,Sprite*sprite2) {
 
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = sprite1->mPosition.x-sprite1->width()/2+2;
    left2 =	sprite2->mPosition.x-sprite2->width()/2+2;
    right1 =sprite1->mPosition.x+sprite1->width()/2-2;
    right2 =sprite2->mPosition.x+sprite2->width()/2-2;
    top1 = sprite1->mPosition.y-sprite1->height()/2+3;
    top2 = sprite2->mPosition.y-sprite2->height()/2+3;
    bottom1 = sprite1->mPosition.y+sprite1->height()/2-3;
    bottom2 = sprite2->mPosition.y+sprite2->height()/2-3;
 
	if ((top1<=bottom2) &&(bottom1>=top2)&&(right1>=left2)&&(left1<=right2))
    return true;
	else return false;
}
void FlappyBird::PlayerTubeCollision ()
{
	for(int i=0;i<mTubes.size();i++)
		if( Collision(mPlayer->mpSprite,mTubes[i]->m_pTube))
		{
			gamestate=Gameoverstate;
			pause();
			PlaySound("Data/hit.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
}

void FlappyBird::Score ()
{
	//If player is atleast half way through tube and hasnt visited that tube,increase score
	for(int i=0;i<mTubes.size();i=i+1)
		{
			 if (mPlayer->mpSprite->mPosition.x>
				 mTubes[i]->m_pTube->mPosition.x &&!score_counted[i])					
			 {
				
				 score_counted[i]=true;
				 mPlayer->Score();
				 nr_of_passed_tubes++;
				 save_nr_of_passed_tubes++;
			 }	
		}	
}
void FlappyBird::RefillAmmunition()
{
	//After each 10 or 11 consecutive passed tubes,the player gets 1 projectile  
	if (	((nr_of_passed_tubes%10==0)||((nr_of_passed_tubes-1)%10==0))&&(nr_of_passed_tubes>1)	)
					
		{
			nr_of_projectiles++; 
			nr_of_passed_tubes=0;
		}
}
void FlappyBird::CheckMechanics ()
{
	PlayerTubeCollision();
	Score();
	RefillAmmunition();	
}
void FlappyBird::ProcessInput()
{
   static UCHAR pKeyBuffer[ 256 ];
    // Retrieve keyboard state.
    if ( !GetKeyboardState ( pKeyBuffer ) )
    {
        return;
    }
	CheckMenuButton();
	if (pKeyBuffer[VK_SPACE] & 0xF0)
	{	
		mPlayer->Flap();
		//dont want to overlap sounds so im waiting 0.1 sec after last sound		
		if(mtimer>0.1)
			{
			//PlaySound("Data/wooshing.wav", NULL, SND_FILENAME | SND_ASYNC);
			mtimer=0;
			}		
	}
}

//Function for testing whether a mouse is over;
//a specific sprite.
bool FlappyBird::OnMouseOver ( Sprite *spr )
{
	POINT p;
	GetCursorPos ( &p );
    ScreenToClient ( mhMainWnd, &p );
    //Testing whether the cursor coordinates are inside a sprite's coordinates;
    if ( ( p.x + spr->width() / 2 > spr->mPosition.x ) &&
       ( p.x < spr->mPosition.x + spr->width() / 2 ) &&
       ( p.y + spr->height() / 2  > spr->mPosition.y ) &&
       ( p.y < spr->mPosition.y + spr->height() / 2 ) )
		return true;
    else
		return false;
}

//Function for checking menu buttons to know;
//whether the player wants to play against AI,against another player;
//or if he wants to quit.
void FlappyBird::CheckMenuButton()
{  

	if (gamestate==Menustate)
	{
		KeyCheckRoutine(  );
		//Check SinglePlayer Button
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::SINGLEPLAYER_NORMAL]->mButton ))
			{
				//Change state to highlighted
				SinglePlayerButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					SinglePlayerButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Play the game
					gamestate=Gameplaystate;
					//Better accuracy
					Sleep(500);
					ResetGame();
				}
			}
		else 
			//If come back to normal state 
			SinglePlayerButton=Button::Normal;


		//Check Quit Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::QUIT_NORMAL]->mButton ))
			{
				//Change state to highlighted
				QuitButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					QuitButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Better accuracy
					//Sleep(100);
					PostQuitMessage(0);
				}
			}
		else 
			//If come back to normal state 
			QuitButton=Button::Normal;


		//Check Difficulty Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::DIFFICULTY_NORMAL]->mButton ))
			{
				//Change state to highlighted
				DifficultyButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					DifficultyButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Better accuracy
					//Sleep(100);
					gamestate=DifficultyMenuState;
				}
			}
		else 
			//If come back to normal state 
			DifficultyButton=Button::Normal;
	}

	if (gamestate==DifficultyMenuState)
	{
		KeyCheckRoutine(  );
		//Check SinglePlayer Button
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::NORMAL_NORMAL]->mButton ))
			{
				//Change state to highlighted
				NormalDifficultyButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					NormalDifficultyButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					difficulty=Difficulty::Normal;
					gamestate=Menustate;
				}
			}
		else 
			//If come back to normal state 
			NormalDifficultyButton=Button::Normal;

		if (OnMouseOver(mButton[Button::HARD_NORMAL]->mButton ))
			{
				//Change state to highlighted
				HardDifficultyButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					HardDifficultyButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					difficulty=Difficulty::Hard;
					gamestate=Menustate;
				}
			}
		else 
			//If come back to normal state 
			HardDifficultyButton=Button::Normal;

		if (OnMouseOver(mButton[Button::EASY_NORMAL]->mButton ))
			{
				//Change state to highlighted
				EasyDifficultyButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					EasyDifficultyButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					difficulty=Difficulty::Easy;
					gamestate=Menustate;
				}
			}
		else 
			//If come back to normal state 
			EasyDifficultyButton=Button::Normal;
	}

	if (gamestate==Gameoverstate)
	{
		KeyCheckRoutine(  );
		//Check Quit button
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::QUIT_NORMAL]->mButton ))
			{
				//Change state to highlighted
				QuitButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					QuitButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Better accuracy
					//Sleep(100);
					PostQuitMessage(0);
				}	
			}
		else 
			//If come back to normal state 
			QuitButton=Button::Normal;

		//Check BacktoMenu  Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::BACK_NORMAL]->mButton ))
			{
				//Change state to highlighted
				BackToMenuButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					BackToMenuButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Playe the game
					gamestate=Menustate;
					//Better accuracy
					Sleep(500);
				}		
			}
		else 
			//If come back to normal state 
			BackToMenuButton=Button::Normal;

		if (OnMouseOver(mButton[Button::SINGLEPLAYER_NORMAL]->mButton ))
			{
				//Change state to highlighted
				SinglePlayerButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					SinglePlayerButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Play the game
					gamestate=Gameplaystate;
					//Better accuracy
					Sleep(500);
					ResetGame();
				}
			}
		else 
			//If come back to normal state 
			SinglePlayerButton=Button::Normal;
	}
			
	if (gamestate==Submenustate)
	{
		KeyCheckRoutine(  );
		if (OnMouseOver(mButton[Button::RESUME_NORMAL]->mButton ))
			{
				//Change state to highlighted
				ResumeButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					ResumeButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					unpause();
					//Better accuracy
					//Sleep(500);
				}		
			}
		else 
			//If come back to normal state 
			ResumeButton=Button::Normal;

		//Check Quit button
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::QUIT_NORMAL]->mButton ))
			{
				//Change state to highlighted
				QuitButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					QuitButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Better accuracy
					//Sleep(500);
					PostQuitMessage(0);
				}	
			}
		else 
			//If come back to normal state 
			QuitButton=Button::Normal;

		//Check BacktoMenu  Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::BACK_NORMAL]->mButton ))
			{
				//Change state to highlighted
				BackToMenuButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					BackToMenuButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Playe the game
					gamestate=Menustate;
					//Better accuracy
					Sleep(500);
				}		
			}
		else 
			//If come back to normal state 
			BackToMenuButton=Button::Normal;

		if (OnMouseOver(mButton[Button::SINGLEPLAYER_NORMAL]->mButton ))
			{
				//Change state to highlighted
				SinglePlayerButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					SinglePlayerButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Play the game
					gamestate=Gameplaystate;
					//Better accuracy
					Sleep(500);
					ResetGame();
				}
			}
		else 
			//If come back to normal state 
			SinglePlayerButton=Button::Normal;
	}
}

//Function for testing whether a mouse left-clicked on a sprite.
void FlappyBird::KeyCheckRoutine( void )
{
static UCHAR pKeyBuffer[ 256 ];
    //Retrieve keyboard state
    if ( !GetKeyboardState ( pKeyBuffer ) )
    {
        return;
    }
    if ( pKeyBuffer[ VK_LBUTTON  ] &  0XF0)
		{
			KeyDown = true;
		}
	else
		{
			KeyDown = false;
			prevstate=up;
		}

	 if( LastFrame && !KeyDown ) //Key had been down but now its up
            {
				KeyReleased=true;
				prevstate=down;
			}
     LastFrame = KeyDown; //Save mouse state  
}  

void FlappyBird::addProjectile()
{
	Vec2 pos;
	Vec2 vel;
		
			pos = mPlayer->mpSprite->mPosition;
			//Add bullet a little bit to the right and down
			pos.x=mPlayer->mpSprite->mPosition.x+16;
			pos.y=mPlayer->mpSprite->mPosition.y+12;
			//Projectile moves only on horizontal azix (int the right)
			vel.x = 150.0f;
			vel.y = 0;

			Projectile* projectile = new Projectile(mhAppInst, pos, vel);
			mProjectiles.push_back(projectile);				
}

void FlappyBird::UpdateProjectiles(float dt)
{
	vector<Projectile*>::iterator ii = mProjectiles.begin();
	for(ii; ii != mProjectiles.end() || mProjectiles.empty(); ii++)
			{
				(*ii)->update(dt);
				if(!mTubes.empty())
				{
				vector<Tube*>::iterator ia = mTubes.begin();
				for(ia= mTubes.begin(); ia != mTubes.end() ; ia++)
						{
						if(Collision((*ia)->m_pTube,(*ii)->mProjectileSprite))
							{

							//(*ia)->mBrick->mPosition.x=-1000;
								if ((*ii) == mProjectiles.back())
								{						
								delete (*ia);
								ia = mTubes.erase(ia);
								delete (*ii);
								mProjectiles.pop_back();
								ii = mProjectiles.end();						
								break;
								}
								else
								{
								delete (*ia);
								ia =mTubes.erase(ia);						
								delete (*ii);
								ii = mProjectiles.erase(ii);
								break;
								}		
							}
						}
				}
	if(ii != mProjectiles.end()) 
		{
			if (!mBoardBounds.IsPtInside((*ii)->mProjectileSprite->mPosition))
				{
					delete (*ii);
					ii = mProjectiles.erase(ii);

					if(ii == mProjectiles.end())
						break;
				}
		}
		else
		{
			break;
		}
	}

}


