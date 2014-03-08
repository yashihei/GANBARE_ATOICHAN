#include "Explosion.h"

Explosion::Explosion(const Vec2& pos, double size):
pos(pos), size(size)
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
	TextureAsset(L"explosion")(240 * t, 0, 240, 240).scale(size).drawAt(pos);
}
