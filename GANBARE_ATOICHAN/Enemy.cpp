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
	const double sp = 5.0;
	const int interval = 5;
	const int sep = 20;
	if (cnt % interval == 0 && cnt > 40) {
		for (int i = 0; i < sep; i++) {
			bulletManager->create(pos, { Sin(rad + 6.28 / sep * i)*sp, Cos(rad + 6.28 / sep * i)*sp }, Color(0, 255, 255, 200));
		}
	}
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
	case 0:
		e = std::make_shared<Enemy1>(); break;
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
		//�b��A�͂ݏo���̂ɏ����]�T������
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0 ||
			(*it)->getPos().y > Window::Height() || (*it)->getPos().y < 0 ||
			!(*it)->isEnable()) {
			it = enemies.erase(it);
			//LOG(L"����");
			continue;
		}
		it++;
	}
}
