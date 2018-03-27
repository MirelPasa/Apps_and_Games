#ifndef SPRITE_H
#define SPRITE_H
#include <windows.h>
#include "Circle.h"
#include "Vec2.h"

class	Sprite
{

public:
    Sprite ( HINSTANCE hAppInst, int imageID, int maskID, const Circle &bc, const Vec2 &p0, const Vec2 &v0 );
	Sprite ( HINSTANCE hAppInst, int imageID, int maskID,const Vec2 &p0 );
	Sprite ( HINSTANCE hAppInst, int imageID, int maskID,const Circle &bc,const Vec2 &p0 );
    ~Sprite ( void );
   virtual int		width ( void );
   virtual int		height ( void );
    void	update ( float dt );
    void	draw ( HDC hBackBufferDC, HDC hSpriteDC );

public:
    Circle	mBoundingCircle;
    Vec2	mPosition;
    Vec2	mVelocity;

private:
    Sprite ( const Sprite &rhs );
    Sprite &operator	= ( const Sprite &rhs );

protected:
    HINSTANCE	mhAppInst;
    HBITMAP		mhImage;
    HBITMAP		mhMask;
    BITMAP		mImageBM;
    BITMAP		mMaskBM;
};
#endif 
