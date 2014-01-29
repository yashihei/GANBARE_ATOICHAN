#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"
#include "EnemyMove.h"
#include "Barrage.h"
#include "EnemyData.h"

Enemy::Enemy(Ship* ship, BulletManager* bulletManager)
:ship(ship), bulletManager(bulletManager)
{
}

void Enemy::setParam(Vec2 pos, EnemyData enemyData, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage)
{
	this->pos = pos;
	rad = enemyData.rad;
	color = enemyData.color;
	hp = enemyData.hp;
	limit = enemyData.limit;
	this->enemyMove = enemyMove;
	this->barrage = barrage;
}

void Enemy::move() {
	cnt++;
	subCnt++;
	if (hp < 0) enable = false;
	enemyMove->move(&pos, cnt);
	if (cnt > limit) barrage->move(pos, ship->getPos(), cnt, bulletManager);
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

EnemyManager::EnemyManager(Ship* ship, BulletManager* bulletManager)
:ship(ship), bulletManager(bulletManager)
{
	barrageFactory = std::make_shared<BarrageFactory>();
	enemyMoveFactory = std::make_shared<EnemyMoveFactory>();
	enemyDataFactory = std::make_shared<EnemyDataFactory>();
}

void EnemyManager::create(Vec2 pos, std::string enemyType, std::string moveType, std::string barrageType)
{
	std::shared_ptr<Enemy> e;
	e = std::make_shared<Enemy>(ship, bulletManager);
	e->setParam(pos, enemyDataFactory->create(enemyType), enemyMoveFactory->create(moveType), barrageFactory->create(barrageType));
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
