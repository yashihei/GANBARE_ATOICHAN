#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"

void Enemy::init(Vec2 pos, Ship* ship, BulletManager* bulletManager) {
	this->pos = pos;
	this->ship = ship;
	this->bulletManager = bulletManager;
}

void Enemy::move() {
	cnt++;
	subCnt++;
	if (hp < 0) enable = false;
}

void Enemy::damage() {
	hp--;
	subCnt = 0;
}

Enemy1::Enemy1() {
	rad = 15.0;
	color = Color(100, 100, 100, 127);
	hp = 10;
}

void Enemy1::move() {
	Enemy::move();
	if (cnt < 40) {
		pos.moveBy({ 0.0, 3.0 });
	} else if (cnt > 180) {
		pos.moveBy({ 0.0, -6.0 });
	}

	const double rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	const double sp = 10.0;
	const int interval = 10;
	if (cnt % interval == 0) bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp });
}

void Enemy1::draw() {
	Circle c(pos, rad);
	c.draw(color);
	if (subCnt < 3) c.draw(Palette::White);
	c.drawFrame(2.0, 0.0, Palette::White);
}

EnemyManager::EnemyManager(Ship* ship, BulletManager* bulletManager)
:ship(ship), bulletManager(bulletManager)
{
}

void EnemyManager::create(Vec2 pos, int type)
{
	std::shared_ptr<Enemy> e;
	switch (type)
	{
	case 1:
		e = std::make_shared<Enemy1>();
		break;
	default:
		LOG(L"default");
	}
	e->init(pos, ship, bulletManager);
	enemies.push_back(e);
}

void EnemyManager::clear() {
	enemies.clear();
}

void EnemyManager::draw() {
	for (auto& enemy : enemies) {
		enemy->draw();
	}
}

void EnemyManager::move() {
	for (auto it = enemies.begin(); it != enemies.end();) {
		(*it)->move();
		//Žb’èA‚Í‚Ýo‚·‚Ì‚É­‚µ—]—TŽ‚½‚¹
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0 || !(*it)->isEnable()) {
			it = enemies.erase(it);
			//LOG(L"Ž€‚ñ‚¾");
			continue;
		}
		it++;
	}
}
