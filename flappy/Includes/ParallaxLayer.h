#ifndef PARALLAX_LAYER_H
#define PARALLAX_LAYER_H

#include "Sprite.h"
using namespace std;

//-----------------------------------------------------------------------------
// Main Class Definitions
//-----------------------------------------------------------------------------
class ParallaxLayer :public Sprite
{
public:
	/*-------------------------------------------------------------------------
	 Enumerators
	-------------------------------------------------------------------------*/
	enum DIRECTION
	{ 
		DIR_FORWARD	 = 1,
		DIR_BACKWARD = 2,
		DIR_LEFT     = 4,
		DIR_RIGHT    = 8,
	};

    enum AXIS
    {
        AXIS_HORIZONTAL = 1,
        AXIS_VERTICAL = 2
    };

    /*-------------------------------------------------------------------------
	 Constructors & Destructors for This Class.
	-------------------------------------------------------------------------*/

	 ParallaxLayer(HINSTANCE mhAppInst,Vec2 p0);
	virtual ~ParallaxLayer();

	/*-------------------------------------------------------------------------
	 Public Functions for This Class.
	-------------------------------------------------------------------------*/
   
    void            Move(ULONG ulDirection);
	void update(float dt);
	void draw ( HDC hBackBufferDC, HDC hSpriteDC );
	Sprite *m_pSprite;

private:
	/*-------------------------------------------------------------------------
	 Private Variables for This Class.
	-------------------------------------------------------------------------*/
    int             m_iLayerSpeed;
    ULONG           m_nViewWidth;
    ULONG           m_nViewHeight;
    virtual int     GetWidth() const { return m_pSprite->GetWidth(); }
    virtual int     GetHeight() const { return m_pSprite->GetHeight(); }
};

#endif // PARALLAX_LAYER_H