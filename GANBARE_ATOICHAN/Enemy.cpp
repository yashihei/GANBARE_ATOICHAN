#include "Enemy.h"

#include "EnemyMove.h"

Enemy::Enemy() {
	//一応仮 TODO:initでsetする
	rad = 15.0;
	color = Color(100, 100, 100, 127);
}

void Enemy::init(Vec2 pos, std::shared_ptr<EnemyMove> enemyMove)
{
	this->enemyMove = enemyMove;
	this->pos = pos;
}

void Enemy::move() {
	enemyMove->move(&pos, cnt);
	cnt++;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(color);
	c.drawFrame(2.0, 0.0, Palette::White);
}

EnemyManager::EnemyManager() {
	enemyMoveFactory = std::make_shared<EnemyMoveFactory>();
}

void EnemyManager::create(Vec2 pos, EnemyMovePtn movePtn)
{
	//TODO: 継承より異状で
	auto e = std::make_shared<Enemy>();
	e->init(pos, enemyMoveFactory->create(movePtn));
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
