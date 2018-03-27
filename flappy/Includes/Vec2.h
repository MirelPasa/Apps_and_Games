#ifndef VEC2_H
#define VEC2_H
#include <windows.h>

class	Vec2
{

public:
    Vec2 ( void );
    Vec2 ( float s, float t );
	Vec2 ( float s );
    Vec2 ( float d[2] );
    Vec2 ( const POINT &p );
    Vec2 operator	+ ( const Vec2 &rhs ) const;
    Vec2 operator	- ( const Vec2 &rhs ) const;
    Vec2 operator	- ( void );
	Vec2			&normalize ( void );
    operator		POINT ( void );
    void operator	+= ( const Vec2 &rhs );
    void operator	-= ( const Vec2 &rhs );
    void operator	*= ( float s );
    void operator	/= ( float s );
    float			length ( void );
    float			dot ( const Vec2 &rhs );
    float			x;
    float			y;
};
//
// * Define with left hand and right hand sides reversed ;
// * so we can write both v*s and s*v.
//
Vec2 operator	* ( const Vec2 &v, float s );
Vec2 operator	* ( float s, const Vec2 &v );
Vec2 operator	/ ( const Vec2 &v, float s );
Vec2 operator	/ ( float s, const Vec2 &v );
#endif 
