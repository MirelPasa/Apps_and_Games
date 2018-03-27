#ifndef TUBE_H
#define TUBE_H
#include "Sprite.h"

using namespace std;

class Tube
{
public:
	enum Type
	{
		Tube_Up,
		Tube_Down,
		Tube_Up_Diagonal,
		Tube_Down_Diagonal,
		Tube_Facing_Left
	};
	Tube();
	Tube(HINSTANCE appInst,Type type,Vec2 p0);
	virtual~Tube(void);
	void draw(HDC hBackBufferDC, HDC hspriteHDC);
	void update(float dt);
	void setrandomlevel(int k);
	void setlevel(int lvl);
	Sprite* m_pTube;
	bool collision;
	virtual bool			Expired() const;
private:
	int level;
	int randommoving;
};
#endif // _CTUBE_H_