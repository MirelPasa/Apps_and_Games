#ifndef RECT_H
#define RECT_H
#include "Vec2.h"

class	Rect
{

public:
    Rect ( void );
    Rect ( const Vec2 &a, const Vec2 &b );
    Rect ( float x0, float y0, float x1, float y1 );
    
    bool	IsPtInside ( const Vec2 &pt );
    Vec2	MinPt;
    Vec2	MaxPt;
};
#endif 
