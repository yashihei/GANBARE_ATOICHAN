#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"
#include "EnemyMove.h"
#include "Barrage.h"

Enemy::Enemy(Vec2 pos, Ship* ship, BulletManager* bulletManager, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage)
:pos(pos), ship(ship), bulletManager(bulletManager), enemyMove(enemyMove), barrage(barrage)
{
	//test data
	rad = 15.0;
	color = Color(100, 100, 100, 127);
	hp = 10;
}

void Enemy::move() {
	cnt++;
	subCnt++;
	if (hp < 0) enable = false;
	enemyMove->move(&pos, cnt);
	barrage->move(pos, ship->getPos(), cnt, bulletManager);
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
}

void EnemyManager::create(Vec2 pos, int enemyType, int moveType, int barrageType)
{
	std::shared_ptr<Enemy> e;
	e = std::make_shared<Enemy>(pos, ship, bulletManager, enemyMoveFactory->create(moveType), barrageFactory->create(barrageType));
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
