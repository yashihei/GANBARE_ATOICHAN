#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"

void Enemy::setParam(Ship* ship, BulletManager* bulletManager, Vec2 pos, int dir)
{
	this->ship = ship;
	this->bulletManager = bulletManager;
	this->pos = pos;
	this->dir = dir;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(color);
	if (subCnt < 3) c.draw(Palette::White);
	c.drawFrame(2.0, 0.0, Palette::White);
}

void Enemy::damage() {
	hp--;
	subCnt = 0;
}

void Enemy::defalutMove() {
	cnt++;
	subCnt++;
	if (hp < 0) enable = false;
}

Enemy1::Enemy1() {
	hp = 10;
	rad = 15.0;
	color = Color{ 255, 0, 0, 200 };
}

void Enemy1::move() {
	const double rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	double sp = 6.5;
	const int interval = 10;
	if (cnt % interval == 0 && cnt > 40) bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp }, Color(255, 0, 255, 200), 5.0);

	if (cnt < 40) {
		pos.moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 250) {
		pos.moveBy({ 0.0, -6.0 });
	}
	Enemy::defalutMove();
}

Tossin::Tossin() {
	hp = 5;
	rad = 15.0;
	color = Color{ 255, 255, 255, 200 };
}

void Tossin::move() {
	const double rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	double sp = 7.0;
	const int interval = 5;
	if (cnt % interval == 0) bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp }, Color(0, 255, 255, 200), 5.0);

	sp = 5.0;
	if (pos.y + 100 < ship->getPos().y) vel = { Sin(rad)*sp, Cos(rad)*sp };
	pos.moveBy(vel);

	Enemy::defalutMove();
}

EnemyManager::EnemyManager(Ship* ship, BulletManager* bulletManager):
ship(ship), bulletManager(bulletManager)
{
}

void EnemyManager::create(Vec2 pos, std::string type, int dir)
{
	std::shared_ptr<Enemy> e;
	if (type == "zako") {
		e = std::make_shared<Enemy1>();
	} else if (type == "tossin") {
		e = std::make_shared<Tossin>();
	} else {
		LOG(L"name miss");
	}
	e->setParam(ship, bulletManager, pos, dir);
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
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0 ||
			(*it)->getPos().y > Window::Height() || (*it)->getPos().y < 0 ||
			!(*it)->isEnable()) {
			it = enemies.erase(it);
			continue;
		}
		it++;
	}
}
