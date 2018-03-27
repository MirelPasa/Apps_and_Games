#include "Projectile.h"
#include "..\\Res\\resource.h"


Projectile::Projectile(HINSTANCE appInst, Vec2 loc, Vec2 vel)
{
	Vec2 p0;
	p0 = loc;
	
	mProjectileSprite = new Sprite(appInst, IDB_BULLET, IDB_BULLET_MASK,loc, vel);
}

Projectile::~Projectile(void)
{
	delete mProjectileSprite;
}

void Projectile::draw(HDC backbuffer, HDC spriteDC)
{
	mProjectileSprite->draw(backbuffer, spriteDC);
}

void Projectile::update(float dt)
{
	mProjectileSprite->update(dt);
}
