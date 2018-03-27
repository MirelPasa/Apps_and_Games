#include "Rect.h"

Rect :: Rect ( void )
{ }
Rect :: Rect ( const Vec2 &a, const Vec2 &b ) :
    MinPt ( a ),
    MaxPt ( b )
{ }

Rect :: Rect ( float x0, float y0, float x1, float y1 ) :
    MinPt ( x0, y0 ),
    MaxPt ( x1, y1 )
{ }

void Rect :: ForceInside ( Circle &A )
{
    Vec2	p = A.c;
    float	r = A.r;
    // Modify coordinates to force inside.
    if ( p.x - r < MinPt.x )
    {
        p.x = MinPt.x + r+1;
    }
    if ( p.x + r > MaxPt.x )
    {
        p.x = MaxPt.x - r-1;
    }
	if(p.y - r < MinPt.y)
		p.y = MinPt.y + r + 1;
	if(p.y + r > MaxPt.y)
		p.y = MaxPt.y - r - 1;

    // Save forced position.
    A.c = p;
}

bool Rect :: IsPtInside ( const Vec2 &pt )
{
    return pt.x >= MinPt.x && pt.y >= MinPt.y && pt.x <= MaxPt.x && pt.y <= MaxPt.y;
}
