#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"
#include "EnemyMove.h"
#include "Barrage.h"
#include "EnemyData.h"

void Enemy::setParam(Vec2 pos, int dir, Ship* ship, BulletManager* bulletManager)
{
	this->pos = pos;
	this->dir = dir;
	this->ship = ship;
	this->bulletManager = bulletManager;
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

Enemy1::Enemy1() {
	hp = 10;
	rad = 15.0;
	color = Color{ 255, 0, 0, 200 };
}

void Enemy1::move() {
}

EnemyManager::EnemyManager(Ship* ship, BulletManager* bulletManager)
:ship(ship), bulletManager(bulletManager)
{
}

void EnemyManager::create(Vec2 pos, int type, int dir)
{
	std::shared_ptr<Enemy> e;
	e = std::make_shared<Enemy>();
	e->setParam(pos, dir, ship, bulletManager);
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
