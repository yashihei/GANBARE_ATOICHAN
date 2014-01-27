#include "Barrage.h"

#include "Bullet.h"

const double PI = 3.14;
const double PI2 = 6.28;

void Barrage1::move(Vec2 ownerPos, Vec2 targetPos, int cnt, BulletManager* bulletManager)
{
	const double rad = Atan2(targetPos.x - ownerPos.x, targetPos.y - ownerPos.y);
	const double sp = 4.0;
	const int interval = 10;
	if (cnt % interval == 0) bulletManager->create(ownerPos, { Sin(rad)*sp, Cos(rad)*sp }, Color(0, 255, 255, 200));
}

void Barrage2::move(Vec2 ownerPos, Vec2 targetPos, int cnt, BulletManager* bulletManager)
{
	const double rad = Atan2(targetPos.x - ownerPos.x, targetPos.y - ownerPos.y);
	const double sp = 3.0;
	const int interval = 10;
	const int sep = 20;
	if (cnt % interval == 0 && cnt > 40) {
		for (int i = 0; i < sep; i++) {
			bulletManager->create(ownerPos, { Sin(rad + PI2 / sep * i)*sp, Cos(rad + PI2 / sep * i)*sp }, Color(0, 255, 255, 200));
		}
	}
}

BarrageFactory::BarrageFactory()
{
	barrageList["Barrage1"] = std::make_shared<Barrage1>();
	barrageList["Barrage2"] = std::make_shared<Barrage2>();
}

std::shared_ptr<Barrage> BarrageFactory::create(std::string type) {
	return barrageList[type];
}
