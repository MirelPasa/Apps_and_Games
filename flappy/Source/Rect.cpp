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



bool Rect :: IsPtInside ( const Vec2 &pt )
{
    return pt.x >= MinPt.x && pt.y >= MinPt.y && pt.x <= MaxPt.x && pt.y <= MaxPt.y;
}

