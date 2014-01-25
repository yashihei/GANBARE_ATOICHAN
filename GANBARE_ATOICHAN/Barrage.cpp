#include "Barrage.h"

#include "Bullet.h"

void Barrage1::move(Vec2 ownerPos, Vec2 targetPos, int cnt, BulletManager* bulletManager)
{
	const double rad = Atan2(targetPos.x - ownerPos.x, targetPos.y - ownerPos.y);
	const double sp = 10.0;
	const int interval = 5;
	//if (cnt % interval == 0) bulletManager->create(ownerPos, { Sin(rad)*sp, Cos(rad)*sp }, TODO);
}

void Barrage2::move(Vec2 ownerPos, Vec2 targetPos, int cnt, BulletManager* bulletManager)
{
	const double rad = Atan2(targetPos.x - ownerPos.x, targetPos.y - ownerPos.y);
	const double sp = 5.0;
	const int interval = 5;
	const int sep = 20;
	if (cnt % interval == 0 && cnt > 40) {
		for (int i = 0; i < sep; i++) {
			bulletManager->create(ownerPos, { Sin(rad + 6.28 / sep * i)*sp, Cos(rad + 6.28 / sep * i)*sp }, Color(0, 255, 255, 200));
		}
	}
}

std::shared_ptr<Barrage> BarrageFactory::create(int type)
{
	switch (type)
	{
	case 0:
		return std::make_shared<Barrage1>(); break;
	case 1:
		return std::make_shared<Barrage2>(); break;
	default:
		LOG(L"defalut");
		return nullptr; break;
	}
}

