#include "Explosion.h"

Explosion::Explosion(const Vec2& pos):
pos(pos)
{
	cnt = 0;
	enable = true;
}

void Explosion::move()
{
	cnt++;
	if (cnt > 30) enable = false;
}

void Explosion::draw()
{
	int t = cnt / 3;
	TextureAsset(L"explosion")(240 * t, 0, 240, 240).scale(0.8).drawAt(pos);
}
