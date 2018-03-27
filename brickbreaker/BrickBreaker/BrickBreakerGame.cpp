#include "BrickBreakerGame.h"
#include "resource.h"
#include "vld.h"
#include <map>
using namespace std;
#define lvlbricks  48
#define allbricks 144
#define brickwidth 51
#define firstbrickposition_x 66
#define firstbrickposition_y 120
#define lastbrickposition_x 423
#define lastbrickposition_y 270

enum Mousestate
{
	down,
	up
};
Mousestate prevstate;

enum GameModes
	{
		SinglePlayer,
		TeamMode,
		PlayervsPlayer,
		PlayervsAI,
	};
GameModes gamemode;

enum Gamestates
{
	Gameplaystate,
	Menustate,
	Gameoverstate,
	Submenustate
};
Gamestates gamestate=Gamestates::Menustate;

Button::State SinglePlayerButton=Button::Normal;
Button::State TeamModeButton=Button::Normal;
Button::State PlayervsPlayerButton=Button::Normal;
Button::State PlayervsAIButton=Button::Normal;
Button::State QuitButton=Button::Normal;
Button::State ResumeButton=Button::Normal;
Button::State BackToMenuButton=Button::Normal;

BrickBreakerGame :: BrickBreakerGame ( HINSTANCE hAppInst, HWND hMainWnd, Vec2 wndCenterPt ) :
    MAX_BALL_SPEED ( 550.0f ),
    AI_SPEED ( 1500.0f ),
	MaxLevel(3),
    mWndCenterPt (wndCenterPt)
{
    // Save input parameters.
    mhAppInst = hAppInst;
    mhMainWnd = hMainWnd;
	//Build GameObjects
	BuildObjects();
	//Init variables
	Init();

}

void BrickBreakerGame::Init()
{
	//Game starts from level 1.
    mLevel = 1;
	//The game is not completed yet.
	GameCompleted=false;
	//No bricks were currently destroyed.
    mNumberOfBricksDestroyed  = 0;
	// The game is initially paused.
	mPaused    = true;
	//Variables foir checking mouse clicks
	KeyReleased=false;
	LastFrame = false;
	KeyDown = false;
	//Board bounds.
	mBoardBounds = Rect ( 1, 45, 492, 620 );	
}
void BrickBreakerGame::BuildObjects()
{
	BuildBackgrounds();
	BuildBalls();
	BuildBricks();
	BuildButtons();
	BuildPlayers();
}
void BrickBreakerGame::BuildButtons()
{
	mButton[Button::SINGLEPLAYER_NORMAL]=new  Button(mhAppInst,Button::SinglePlayer,Button::Normal);
	mButton[Button::SINGLEPLAYER_HIGHLIGHTED]=new Button(mhAppInst,Button::SinglePlayer,Button::Highlighted);
	mButton[Button::SINGLEPLAYER_PRESSED]=new  Button(mhAppInst,Button::SinglePlayer,Button::Pressed);
	mButton[Button::TEAMMODE_NORMAL]=new Button(mhAppInst,Button::TeamMode,Button::Normal);
	mButton[Button::TEAMMODE_HIGHLIGHTED]=new Button(mhAppInst,Button::TeamMode,Button::Highlighted);
	mButton[Button::TEAMMODE_PRESSED]=new Button(mhAppInst,Button::TeamMode,Button::Pressed);
	mButton[Button::PLAYERVSAI_NORMAL]=new Button(mhAppInst,Button::PlayervsAI,Button::Normal);
	mButton[Button::PLAYERVSAI_HIGHLIGHTED]=new Button(mhAppInst,Button::PlayervsAI,Button::Highlighted);
	mButton[Button::PLAYERVSAI_PRESSED]=new Button(mhAppInst,Button::PlayervsAI,Button::Pressed);
	mButton[Button::PLAYERVSPLAYER_NORMAL]=new Button(mhAppInst,Button::PlayervsPlayer,Button::Normal);
	mButton[Button::PLAYERVSPLAYER_HIGHLIGHTED]=new  Button(mhAppInst,Button::PlayervsPlayer,Button::Highlighted);
	mButton[Button::PLAYERVSPLAYER_PRESSED]= new Button(mhAppInst,Button::PlayervsPlayer,Button::Pressed);
	mButton[Button::QUIT_NORMAL]=new Button(mhAppInst,Button::Quit,Button::Normal);
	mButton[Button::QUIT_HIGHLIGHTED]=new  Button(mhAppInst,Button::Quit,Button::Highlighted);
	mButton[Button::QUIT_PRESSED]=new  Button(mhAppInst,Button::Quit,Button::Pressed);
	mButton[Button::BACK_NORMAL]=new Button(mhAppInst,Button::BackToMenu,Button::Normal);
	mButton[Button::BACK_HIGHLIGHTED]=new Button(mhAppInst,Button::BackToMenu,Button::Highlighted);
	mButton[Button::BACK_PRESSED]=new Button(mhAppInst,Button::BackToMenu,Button::Pressed);
	mButton[Button::RESUME_NORMAL]=new  Button(mhAppInst,Button::Resume,Button::Normal);
	mButton[Button::RESUME_HIGHLIGHTED]=new Button(mhAppInst,Button::Resume,Button::Highlighted);
	mButton[Button::RESUME_PRESSED]=new  Button(mhAppInst,Button::Resume,Button::Pressed);
}
void BrickBreakerGame::BuildBalls()
{
	mYellowBall=new Ball( mhAppInst,Ball::YellowBall);
	mBlueBall=new Ball( mhAppInst,Ball::BlueBall);
}

//Create a matrix of bricks...gray bricks, brown bricks and blue bricks;
//The first brick is created in the upper left screen,;
//the next one below it and so on..untill the first collum is filled;
//After the first collum is created ,;
//the second collum is created starting from the upper screen;
//In the end the last collum of bricks is created using the same principle.
void BrickBreakerGame::BuildBricks()
{
	mGrayBricks.resize(lvlbricks);
	mBrownBricks.resize(lvlbricks);
	mBlueBricks.resize(lvlbricks);
	Bricks.reserve(allbricks);
	int brickcounter = 0;
    for ( float i = firstbrickposition_x; i <= lastbrickposition_x; i = i + brickwidth )
    {
        for ( float k = firstbrickposition_y; k <= lastbrickposition_y; k = k + 30 )
        {
            //Coordinates where the current brick is created.
			p0.x = i;  
            p0.y = k;			
            mGrayBricks[brickcounter] = new Brick ( mhAppInst, Brick::GrayBrick, p0 );
			Bricks.emplace_back(mGrayBricks[brickcounter]);
			mBrownBricks[brickcounter] = new Brick ( mhAppInst, Brick::BrownBrick, p0 );
			Bricks.emplace_back(mBrownBricks[brickcounter]);
			mBlueBricks[brickcounter] = new Brick ( mhAppInst, Brick::BlueBrick, p0 );
			Bricks.emplace_back(mBlueBricks[brickcounter]);
            brickcounter++;
        }
    }	
}
void BrickBreakerGame::BuildBackgrounds()
{
	const int			gClientWidth = 504;
	const int			gClientHeight = 662;
	//Center point of client rectangle
	const POINT			wndCenterPt = { gClientWidth / 2, gClientHeight / 2 };
	p0 = wndCenterPt;
	mGameBoard = new Sprite ( mhAppInst, IDB_GAMEBOARD, IDB_GAMEBOARD_MASK,p0 );
	//Create menu,players,balls,and gameover sprites	
	mMenu = new Sprite ( mhAppInst, IDB_MENUSCREEN, IDB_MENUSCREEN_MASK,p0 );
	mGameCompleted = new Sprite ( mhAppInst, IDB_GAMECOMPLETED, IDB_GAMECOMPLETED_MASK,p0 );
	mGameOver = new Sprite(mhAppInst, IDB_GAMEOVER, IDB_GAMEOVER_MASK,p0 );
	mWin= new Sprite ( mhAppInst, IDB_WIN, IDB_WIN_MASK,p0 );
	mLose= new Sprite ( mhAppInst, IDB_LOSE, IDB_LOSE_MASK,p0 );
}
void BrickBreakerGame::BuildPlayers()
{
	mPlayer=new Player( mhAppInst,Player::Player1);
	mTeamMate=new Player( mhAppInst,Player::TeamMate);
	mPlayer2=new Player2( mhAppInst,Player2::HumanPlayer2);
	mAI=new Player2( mhAppInst,Player2::AI);
}
//Function for showing and hiding the cursor;
//The cursor is displayed until counter is smaller than 0;
//The cursor is hidden until counter is equal or greater than 0.
void BrickBreakerGame::showCursor(bool show)
{
      if (show)
            while (ShowCursor(TRUE) < 0);
      else
            while (ShowCursor(FALSE) >= 0);
}

BrickBreakerGame :: ~BrickBreakerGame ( void )
{
	delete mGameBoard;
	delete mPlayer;
	delete mTeamMate;
	delete mPlayer2;
	delete mAI;
	delete mYellowBall;
	delete mBlueBall;
	delete mMenu;
	delete mGameCompleted;
	delete mWin;
	delete mLose;
	delete mGameOver;
	while(!Bricks.empty()) delete Bricks.back(), Bricks.pop_back();		
	for(std::map<Button::Buttons,Button*>::iterator MapItor = mButton.begin(); MapItor != mButton.end(); ++MapItor)
	{
		Button* Value = MapItor->second;
		delete Value;
	}
	mButton.clear();
}

void BrickBreakerGame :: pause ( void )
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

void BrickBreakerGame :: unpause ( void )
{   //I dont want unpause button to be checked in menu or after the game is over
	if ((gamestate!=Menustate) && (gamestate!=Gameoverstate))
	{
		mPaused = false;
		showCursor(false);
		gamestate=Gameplaystate;
	}
}

void BrickBreakerGame :: update ( float dt )
{
    // Only update the game if the game is not paused.
    if ( !mPaused )
    {
        UpdatePlayer1 ( dt );
		UpdateTeamMate ( dt );
        UpdateBall ( dt );
		UpdateHumanPlayer2(dt);
		UpdateAI(dt);
    }
}

void BrickBreakerGame::DrawGameplay(HDC hBackBufferDC, HDC hSpriteDC)
{
	mGameBoard->draw ( hBackBufferDC, hSpriteDC );	
	//Depending on the current game mode draw the players.
	switch(gamemode)
	{
	case SinglePlayer:
		{
			mPlayer->draw ( hBackBufferDC, hSpriteDC );
		}
		break;
	case TeamMode:
		{
			mTeamMate->draw ( hBackBufferDC, hSpriteDC );
			mPlayer->draw ( hBackBufferDC, hSpriteDC );
		}
		break;
	case PlayervsPlayer:
		{
			mPlayer2->draw ( hBackBufferDC, hSpriteDC );
			mPlayer->draw ( hBackBufferDC, hSpriteDC );
		}
		break;
	case PlayervsAI:
		{
			mAI->draw ( hBackBufferDC, hSpriteDC );
			mPlayer->draw ( hBackBufferDC, hSpriteDC );
		}
		break;
	}
	//Draw bricks and balls;
	//The bricks are drawn only on singleplayer;
	//and teammode;
	//The balls are drawn on all modes.
	switch ( mLevel )
	{
	case 1:
		//Draw gray bricks for level 1.
		if ((gamemode==SinglePlayer)||(gamemode==TeamMode))
			for ( int i = 0; i < lvlbricks; i++ )
			{
				mGrayBricks[i]->draw ( hBackBufferDC, hSpriteDC );
			}
			//Draw yellow ball for level 1.
			mYellowBall->draw ( hBackBufferDC, hSpriteDC );			
			break;
	case 2:
		//Draw brown bricks for level 2.
		if ((gamemode==SinglePlayer)||(gamemode==TeamMode))
			for ( int i = 0; i < lvlbricks; i++ )
			{
				mBrownBricks[i]->draw ( hBackBufferDC, hSpriteDC );
			}
			//Draw blue ball for level 2.
			mBlueBall->draw ( hBackBufferDC, hSpriteDC );			           
			break;
	case 3:
		//Draw blue bricks for level 3.
		if ((gamemode==SinglePlayer)||(gamemode==TeamMode))
			for ( int i = 0; i < lvlbricks; i++ )
			{
				mBlueBricks[i]->draw ( hBackBufferDC, hSpriteDC );
			}
			//Draw blue ball and yellow ball ofr level 3.
			mBlueBall->draw ( hBackBufferDC, hSpriteDC );
			mYellowBall->draw ( hBackBufferDC, hSpriteDC );         
			break;
		}
	//Draw levels only on singleplayer and teammode
	if ((gamemode==SinglePlayer)||(gamemode==TeamMode))
	{
		char	level[32];
		SetTextColor ( hBackBufferDC, RGB ( 255, 255, 255 ) );
		SetBkMode ( hBackBufferDC, TRANSPARENT );
		sprintf_s ( level, "Level = %d", mLevel );
		TextOut ( hBackBufferDC, 220, 10, level, ( int ) strlen ( level ) );
	}
}
void BrickBreakerGame::DrawMenu(HDC hBackBufferDC,HDC hSpriteDC )
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
	//Draw TeamMode buttons
	switch(TeamModeButton)
	{
	case Button::Normal:
		mButton[Button::TEAMMODE_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::TEAMMODE_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::TEAMMODE_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}
	//Draw PlayervsPlayer Buttons
	switch(PlayervsPlayerButton)
	{
	case Button::Normal:
		mButton[Button::PLAYERVSPLAYER_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::PLAYERVSPLAYER_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::PLAYERVSPLAYER_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	}
	//Draw PlayervsAI buttons
	switch(PlayervsAIButton)
	{
	case Button::Normal:
		mButton[Button::PLAYERVSAI_NORMAL]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Highlighted:
		mButton[Button::PLAYERVSAI_HIGHLIGHTED]->draw ( hBackBufferDC, hSpriteDC );
		break;
	case Button::Pressed:
		mButton[Button::PLAYERVSAI_PRESSED]->draw ( hBackBufferDC, hSpriteDC );
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
}
void BrickBreakerGame::DrawSubMenu(HDC hBackBufferDC, HDC hSpriteDC)
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
}
void BrickBreakerGame::DrawGameOver( HDC hBackBufferDC, HDC hSpriteDC )
{
	//Draw gameover sprites
	if ((gamemode==PlayervsAI)||(gamemode==PlayervsPlayer))
	{
		if (mPlayer2->GameOver()) 
			mWin->draw ( hBackBufferDC, hSpriteDC );
		if (mPlayer->GameOver()) 
			mLose->draw ( hBackBufferDC, hSpriteDC );
	}
	//Draw gamecompleted sprites
	if ((gamemode==TeamMode)||(gamemode==SinglePlayer))
	{
		if (mPlayer->GameOver()) 
			mGameOver->draw ( hBackBufferDC, hSpriteDC );
		if (GameCompleted)
			mGameCompleted->draw ( hBackBufferDC, hSpriteDC );
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
}
void BrickBreakerGame :: draw ( HDC hBackBufferDC, HDC hSpriteDC )
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
	}
}
//Function for advancing to the next level;
//and resetting some sprites and statistics.
void BrickBreakerGame::AdvanceLevel()
{
	if ( mNumberOfBricksDestroyed  == mLevel * lvlbricks)
	{
		pause();
		mPlayer->ResetPosition(mhAppInst,Player::Player1);
		mTeamMate->ResetPosition(mhAppInst,Player::TeamMate);
		mPlayer2->ResetPosition(mhAppInst,Player2::HumanPlayer2);
		mAI->ResetPosition(mhAppInst,Player2::AI);
		mYellowBall->ResetPosition(mhAppInst,Ball::YellowBall);
		mBlueBall->ResetPosition(mhAppInst,Ball::BlueBall);
		++mLevel;  
		gamestate=Gameplaystate;
		if( mNumberOfBricksDestroyed==lvlbricks*MaxLevel)
		{
			pause();
			gamestate=Gameoverstate;
			GameCompleted=true;
		}
	}	
}

//Function for resetting all objects and variables;
//needed when starting a new game. 
void BrickBreakerGame::Resetallobjects()
{
	mYellowBall->ResetPosition(mhAppInst,Ball::YellowBall);
	mBlueBall->ResetPosition(mhAppInst,Ball::BlueBall);
	mPlayer->ResetLives();
	mTeamMate->ResetLives();
	mPlayer2->ResetLives();
	mAI->ResetLives();
	mLevel=1;
	mNumberOfBricksDestroyed  = 0;
	GameCompleted=false;
	BuildBricks();
	mPlayer->ResetPosition(mhAppInst,Player::Player1);
	mTeamMate->ResetPosition(mhAppInst,Player::TeamMate);
	mPlayer2->ResetPosition(mhAppInst,Player2::HumanPlayer2);
	mAI->ResetPosition(mhAppInst,Player2::AI);
}

void BrickBreakerGame::UpdatePlayer1(float dt)
{
    // Update the player paddle's position.
    mPlayer->update ( dt );
    // Make sure the player paddle stays inbounds.
	mPlayer->mPlayerBounds.ForceInside ( mPlayer->mPaddle->mBoundingCircle );
    mPlayer->mPaddle->mPosition = mPlayer->mPaddle->mBoundingCircle.c;
	//On teammode,players can only move to the center of the board;
	//preventing them from crossing their bounds.
	if (gamemode==TeamMode)
	{
	mPlayer->mPlayer1Bounds.ForceInside ( mPlayer->mPaddle->mBoundingCircle );
    mPlayer->mPaddle->mPosition = mPlayer->mPaddle->mBoundingCircle.c;
	}
}
void BrickBreakerGame::UpdateTeamMate(float dt)
{
    // Update the player paddle's position.
    mTeamMate->update ( dt );
    // Make sure the player paddle stays inbounds.
    mTeamMate->mTeamMateBounds.ForceInside ( mTeamMate->mPaddle->mBoundingCircle );
    mTeamMate->mPaddle->mPosition = mTeamMate->mPaddle->mBoundingCircle.c;
}

void BrickBreakerGame :: UpdateBall ( float dt )
{
	//Since there is no yellow ball on level 2 don't check collisions.
	if((mLevel==1)||(mLevel==3))
		CheckAllBallCollisions(mYellowBall->mBall);
	//Since there is no blue ball on level 1 don't check collisions.
	if((mLevel==2)||(mLevel==3))
		CheckAllBallCollisions(mBlueBall->mBall);
	// Clamp balls speed to some maximum velocity;
	// This provides good stability.
	if ( mBlueBall->mBall->mVelocity.length () >= MAX_BALL_SPEED )
		{
			mBlueBall->mBall->mVelocity.normalize () *= MAX_BALL_SPEED;
		}
	if ( mYellowBall->mBall->mVelocity.length () >= MAX_BALL_SPEED )
		{
			mYellowBall->mBall->mVelocity.normalize () *= MAX_BALL_SPEED;
		}
	// Make sure the yellowball stays inbounds of the gameboard.
	mBoardBounds.ForceInside ( mBlueBall->mBall->mBoundingCircle );
	mBlueBall->mBall->mPosition = mBlueBall->mBall->mBoundingCircle.c;
	mBlueBall->mBall->update ( dt );
	// Make sure the blueball stays inbounds of the gameboard.
	mBoardBounds.ForceInside ( mYellowBall->mBall->mBoundingCircle );
	mYellowBall->mBall->mPosition = mYellowBall->mBall->mBoundingCircle.c;
	mYellowBall->mBall->update ( dt );	
}
int BrickBreakerGame::Collision(Sprite*sprite1,Sprite*sprite2) {
 
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;


    left1 = sprite1->mPosition.x-sprite1->width()/2;
    left2 =	sprite2->mPosition.x-sprite2->width()/2;
    right1 =sprite1->mPosition.x+sprite1->width()/2;
    right2 =sprite2->mPosition.x+sprite2->width()/2;
    top1 = sprite1->mPosition.y-sprite1->height()/2;
    top2 = sprite2->mPosition.y-sprite2->height()/2;
    bottom1 = sprite1->mPosition.y+sprite1->height()/2;
    bottom2 = sprite2->mPosition.y+sprite2->height()/2;
 
 
	if ((top1<=bottom2) &&(bottom1>=top2)&&(right1>=left2)&&(left1<=right2))
    return true;
	else return false;
};

//Function for checking all ball's collisions;
//(with bricks,walls and paddles).
void BrickBreakerGame::CheckAllBallCollisions(Sprite *ball)
{
	switch(gamemode)
	{
	case SinglePlayer:
		PaddleBallCollision ( mPlayer->mPaddle, ball );
		switch(mLevel)
		{
		case 1:
			BrickBallCollision ( mGrayBricks, ball );
			break;
		case 2:
			BrickBallCollision ( mBrownBricks, ball );
			break;
		case 3:
			BrickBallCollision ( mBlueBricks, ball );	
			break;
		}
		break;
	case TeamMode:
		PaddleBallCollision ( mPlayer->mPaddle, ball );
		PaddleBallCollision ( mTeamMate->mPaddle, ball );
		switch(mLevel)
		{
		case 1:
			BrickBallCollision ( mGrayBricks, ball );
			break;
		case 2:
			BrickBallCollision ( mBrownBricks, ball );
			break;
		case 3:
			BrickBallCollision ( mBlueBricks, ball );
			break;
		}
		break;
	case PlayervsPlayer:
		PaddleBallCollision ( mPlayer->mPaddle, ball );
		PaddleBallCollision ( mPlayer2->mPaddle, ball );
		break;
	case PlayervsAI:
		PaddleBallCollision ( mPlayer->mPaddle, ball );
		PaddleBallCollision ( mAI->mPaddle, ball );
		break;
	}
	BallWallCollision ( ball );
}

void BrickBreakerGame::BallWallCollision ( Sprite *ball )
{
    Circle	ballCircle = ball->mBoundingCircle;
    // Did the ball hit a wall? If so, reflect about edge.
    if ( ballCircle.c.x - ballCircle.r < mBoardBounds.MinPt.x )
    {
        ball->mVelocity.x *= -1.0f;
    }
    if ( ballCircle.c.x + ballCircle.r > mBoardBounds.MaxPt.x )
    {
        ball->mVelocity.x *= -1.0f;
    }
    if ( ballCircle.c.y - ballCircle.r < mBoardBounds.MinPt.y )
    {
        ball->mVelocity.y *= -1.0f;
		//If the ball hits player2's bounds \
		//and decrease player2's lives.
		mPlayer2->kill();
		mAI->kill();
    }
    if ( ballCircle.c.y + ballCircle.r > mBoardBounds.MaxPt.y )
    {
        ball->mVelocity.y *= -1.0f;
		//If the ball hits player1's bounds 
		//and decrease player1's lives.
		mPlayer->kill();
		mTeamMate->kill();
    }
	if ((gamemode==SinglePlayer)||(gamemode==TeamMode))
		if  (mPlayer->GameOver())
		{
			gamestate=Gameoverstate;
			pause();
		}
	if ((gamemode==PlayervsPlayer)||(gamemode==PlayervsAI))
		if  ((mPlayer2->GameOver()) || (mPlayer->GameOver()))
		{
			gamestate=Gameoverstate;
			pause();
		}
}

bool BrickBreakerGame :: PaddleBallCollision ( Sprite *paddle, Sprite *ball )
{
    Vec2	normal;
    if ( paddle->mBoundingCircle.hits ( ball->mBoundingCircle, normal ) )
    {
        // Compute the paddle's velocity relative to the ball's velocity.
        Vec2	relVel = ( paddle->mVelocity - ball->mVelocity );
        // Get the component of the relative velocity along the normal.
        float	impulseMag = relVel.dot ( normal );
        // Are the objects getting closer together?
        if ( impulseMag >= 0.0f )
        {
            // Project the relative velocity onto the normal.
            Vec2	impulse = impulseMag * normal;
            // Add the impulse to the ball.
            ball->mVelocity += 2.0f * impulse;
            return true;
        }
    }
    return false;
}

//Different levels;
//On level 1 when the ball collides with the brick it passes throught it;
//On level 2 when the ball collides with the brick it reflects;
//On level 3 when the ball collides with the brick it passes throught it.
void BrickBreakerGame::LevelHandler(Brick *brick, Sprite *ball)
{
	switch(mLevel)
	{	
	case 1:
		brick->mBrick->mPosition.x = -1000; 
		break;
	case 2:
		brick->mBrick->mPosition.x = -1000;
		//If the ball hits left or right side of the brick,reflect
		if( ( ball->mPosition.y - ball->height()/2 <= brick->mBrick->mPosition.y+ brick->mBrick->height()/2) &&
           (ball->mPosition.y + ball->height()/2>= brick->mBrick->mPosition.y- brick->mBrick->height()/2 ) )
		ball->mVelocity.y *= -1.0f; //reflect
		//If the ball hits top or bottom side of the brick,reflect
        if ( ( ball->mPosition.x - ball->width()/2 <= brick->mBrick->mPosition.x+brick->mBrick->width()/2 ) &&
           ( ball->mPosition.x + ball->width()/2>=brick->mBrick->mPosition.x - brick->mBrick->width()/2 ) )
		ball->mVelocity.x *= -1.0f;
		break;
	case 3:
		brick->mBrick->mPosition.x = -1000;	
		break;
		}
	//If all the bricks were detroyed,advance to the next level.
	AdvanceLevel();	
}

void BrickBreakerGame :: BrickBallCollision (vector<Brick*>brick, Sprite *ball )
{
    for ( int i = 0; i < lvlbricks; i++ )
    {

		//If the ball collides with the brick.
		if ( Collision(brick[i]->mBrick,ball))
			{
				//When the brick collides with the ball save;
				//the number if bricks destroyed for knowing;
				//when to advance to the next level
				mNumberOfBricksDestroyed++;
				//Since levels depend on bricks check levels here.
				LevelHandler(brick[i],ball);
			}
    }
}

void BrickBreakerGame::ProcessInput()
{
   static UCHAR pKeyBuffer[ 256 ];
    // Retrieve keyboard state.
    if ( !GetKeyboardState ( pKeyBuffer ) )
    {
        return;
    }
	//Check which menu buttons were pressed.
	CheckMenuButton();
	//Check keyboard keys only if the game is running.
    if ( !mPaused )
    {
			if ( pKeyBuffer[ 0x41  ] & 0xF0 )
			{
				mTeamMate->move(Player::Left);

				mPlayer2->move(Player2::Left);
			}
			if ( pKeyBuffer[ 0x44 ] & 0xF0 )
			{
				mTeamMate->move(Player::Right);

				mPlayer2->move(Player2::Right);
			}				
			if ( pKeyBuffer[ VK_LEFT  ] & 0xF0 )
			{
				mPlayer->move(Player::Left);
			}
			if ( pKeyBuffer[ VK_RIGHT ] & 0xF0 )
			{
				mPlayer->move(Player::Right);
			}	
    }	
}
void BrickBreakerGame::UpdateAI(float dt)
{
// The player2 paddle's AI is overly simplistic: When the ;
// ball moves into player2's boundary, the player2 paddle ;
// simply moves directly towards the ball to hit it. ;
// When the ball leaves player2's boundaries, the player2 ;
// paddle returns to the center of its boundary.

    // Is the ball in player2's boundary? If yes, then ;
    // move the player2 paddle directly toward the ball.
    if ( mAI->mPlayer2Bounds.IsPtInside ( mYellowBall->mBall->mPosition )  || 
		mAI->mPlayer2Bounds.IsPtInside ( mBlueBall->mBall->mPosition ))
		{
        // Vectors directed from paddle to ball.
        Vec2	AIVel = mYellowBall->mBall->mPosition - mAI->mPaddle->mPosition;
		Vec2	AIVELVSBLUEBALL = mBlueBall->mBall->mPosition - mAI->mPaddle->mPosition;
        AIVel.normalize ();
        AIVel *= AI_SPEED;
		AIVELVSBLUEBALL.normalize ();
        AIVELVSBLUEBALL *= AI_SPEED;                
        //If player2 paddle is closer to yellow ball move toward it;
        //If player2 is closer to blue ball move toward it.
		if ( ( AIVel.y ) <= ( AIVELVSBLUEBALL.y ) )
			{
				mAI->mPaddle->mVelocity = AIVel;
            }                  
		else						 
            {
				mAI->mPaddle->mVelocity = AIVELVSBLUEBALL;
            }                                      
		}
		// If no, then move the player2 paddle to the point (250, 200).
		else
			{
			Vec2	AIVel = Vec2 ( 250, 200 ) - mAI->mPaddle->mPosition;
            if ( AIVel.length () > 5.0f )
				{
                AIVel.normalize ();
                AIVel *= AI_SPEED;
                mAI->mPaddle->mVelocity = AIVel;
                } // Within 5 units--close enough.
				else
                    {
                       mAI-> mPaddle->mVelocity = Vec2 ( 0.0f, 0.0f );
                    }
			}
				//Update the player2 paddle's position.
                mAI->update ( dt );
                // Make sure the player2 paddle stays inbounds.
                mAI->mPlayer2Bounds.ForceInside ( mAI->mPaddle->mBoundingCircle );
                mAI->mPaddle->mPosition = mAI->mPaddle->mBoundingCircle.c;     
}
void BrickBreakerGame::UpdateHumanPlayer2(float dt)
{
    // Update the player paddle's position.
    mPlayer2->update ( dt );
    // Make sure the player paddle stays inbounds.
    mPlayer2->mPlayer2Bounds.ForceInside ( mPlayer2->mPaddle->mBoundingCircle );
    mPlayer2->mPaddle->mPosition = mPlayer2->mPaddle->mBoundingCircle.c;
}

//Function for testing whether a mouse is over;
//a specific sprite.
bool BrickBreakerGame::OnMouseOver ( Sprite *spr )
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
void BrickBreakerGame::CheckMenuButton()
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
					Resetallobjects();
					gamemode=SinglePlayer;
				}
			}
		else 
			//If come back to normal state 
			SinglePlayerButton=Button::Normal;

		//Check TeamMode Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::TEAMMODE_NORMAL]->mButton ))
			{
				//Change state to highlighted
				TeamModeButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					TeamModeButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Playe the game
					gamestate=Gameplaystate;
					//Better accuracy
					Sleep(500);
					Resetallobjects();
					gamemode=TeamMode;
				}	
			}
		else 
			//If come back to normal state 
			TeamModeButton=Button::Normal;

		//Check PlayervsPlayer Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::PLAYERVSPLAYER_NORMAL]->mButton ))
			{
				//Change state to highlighted
				PlayervsPlayerButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					PlayervsPlayerButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Playe the game
					gamestate=Gameplaystate;
					//Better accuracy
					Sleep(500);
					Resetallobjects();
					gamemode=PlayervsPlayer;
				}
			}
		else 
			//If come back to normal state 
			PlayervsPlayerButton=Button::Normal;

		//Check PlayervsAI Button.
		//If mouse is over current sprite
		if (OnMouseOver(mButton[Button::PLAYERVSAI_NORMAL]->mButton ))
			{
				//Change state to highlighted
				PlayervsAIButton=Button::Highlighted;
				//Check if current button is pressed
				if (KeyDown)
				{
					//If yes,change state to pressed
					PlayervsAIButton=Button::Pressed;
				}
				//If current sprite button was pressed
				//and after that click was released
				if((KeyReleased==true)&&(prevstate==down))
				{
					//Playe the game
					gamestate=Gameplaystate;
					//Better accuracy
					Sleep(500);
					Resetallobjects();
					gamemode=PlayervsAI;
				}	
			}
		else 
			//If come back to normal state 
			PlayervsAIButton=Button::Normal;

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
	}
}

//Function for testing whether a mouse left-clicked on a sprite.
void BrickBreakerGame::KeyCheckRoutine( void )
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


