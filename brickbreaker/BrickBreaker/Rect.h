#ifndef RECT_H
#define RECT_H
#include "Circle.h"

class	Rect
{

public:
    Rect ( void );
    Rect ( const Vec2 &a, const Vec2 &b );
    Rect ( float x0, float y0, float x1, float y1 );
    void	ForceInside ( Circle &A );
    bool	IsPtInside ( const Vec2 &pt );
    Vec2	MinPt;
    Vec2	MaxPt;
};
#endif 
