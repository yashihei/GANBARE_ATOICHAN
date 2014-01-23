#include "Enemy.h"

#include "EnemyMove.h"
#include "Barrage.h"
#include "Ship.h"

Enemy::Enemy(Ship* ship, BulletManager* bulletManager)
:ship(ship), bulletManager(bulletManager)
{
	//一応仮 TODO:initでsetする
	rad = 15.0;
	color = Color(100, 100, 100, 127);
}

void Enemy::init(Vec2 pos, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage)
{
	this->enemyMove = enemyMove;
	this->pos = pos;
	this->barrage = barrage;
}

void Enemy::move() {
	enemyMove->move(&pos, cnt);
	barrage->move(pos, ship->getPos(), cnt, bulletManager);
	cnt++;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(color);
	c.drawFrame(2.0, 0.0, Palette::White);
}

EnemyManager::EnemyManager(Ship* ship, BulletManager* bulletManager)
:ship(ship), bulletManager(bulletManager)
{
	enemyMoveFactory = std::make_shared<EnemyMoveFactory>();
	barrageFactory = std::make_shared<BarrageFactory>();
}

void EnemyManager::create(Vec2 pos, int moveType, int barrageType)
{
	auto e = std::make_shared<Enemy>(ship, bulletManager);
	e->init(pos, enemyMoveFactory->create(moveType), barrageFactory->create(barrageType));
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
		//暫定、はみ出すのに少し余裕持たせ
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0) {
			it = enemies.erase(it);
			//LOG(L"死んだ");
			continue;
		}
		it++;
	}
}
