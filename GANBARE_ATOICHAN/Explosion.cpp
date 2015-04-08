#include "Explosion.h"

#include "GameManager.h"

Explosion::Explosion(GameManager* gm,const Vec2& pos, double size):
gm(gm), pos(pos), size(size)
{
	cnt = 0;
	enable = true;
}

void Explosion::move()
{
	double t = size - cnt / 30;
	gm->getController()->setVibration(t, t);
	cnt++;
	if (cnt > 30) {
		enable = false;
		gm->getController()->setVibration(0, 0);
	}
}

void Explosion::draw()
{
	int t = cnt / 3;
	TextureAsset(L"explosion")(240 * t, 0, 240, 240).scale(size * 2.0).drawAt(pos);
}
