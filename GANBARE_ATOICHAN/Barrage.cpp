#include "Barrage.h"

#include "Bullet.h"

void Barrage1::move(Vec2 ownerPos, Vec2 targetPos, int cnt, BulletManager* bulletManager)
{
	const double rad = Atan2(targetPos.x - ownerPos.x, targetPos.y - ownerPos.y);
	const double sp = 10.0;
	const int interval = 5;
	if (cnt % interval == 0) bulletManager->create(ownerPos, { Sin(rad)*sp, Cos(rad)*sp });
}

std::shared_ptr<Barrage> BarrageFactory::create(int type)
{
	switch (type)
	{
	case 1:
		return std::make_shared<Barrage1>(); break;
	default:
		return nullptr; break;
	}
}