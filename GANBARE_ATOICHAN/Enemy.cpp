#include "Enemy.h"

void EnemyMove1::move(Vec2* pos, int cnt) {
	if (cnt < 60) {
		pos->moveBy({ -3.0, 0.0 });
	} else if (cnt > 180) {
		pos->moveBy({ 6.0, 0.0 });
	}
}

Enemy::Enemy(Vec2 pos) : pos(pos) {
	enemyMove = std::make_shared<EnemyMove1>();
	rad = 15.0;
	cnt = 0;
}

void Enemy::move() {
	enemyMove->move(&pos, cnt);
	cnt++;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(palette);
	c.drawFrame(2.0, 0.0, Palette::White);
}

EnemyManager::EnemyManager() {
}

void EnemyManager::create(Vec2 pos)
{
	auto e = std::make_shared<Enemy>(pos);
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
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0) {
			it = enemies.erase(it);
			//LOG(L"Ž€‚ñ‚¾");
			continue;
		}
		it++;
	}
	if (Random(0, 50) == 0) create({ Window::Width(), Random(0, Window::Height()) });
}
