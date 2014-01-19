#include "EnemyManager.h"

Enemy::Enemy() {
	rad = 15.0;
}

void Enemy::move() {
	pos.moveBy({ -4.0, 0 });//‰¼
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(Palette::Blue);
	c.drawFrame(2.0, 0.0, Palette::White);
}

EnemyManager::EnemyManager() {
}

void EnemyManager::create(Vec2 pos) {
	auto e = std::make_shared<Enemy>();
	e->setPos(pos);
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
	for (auto& enemy : enemies) {
		enemy->move();
	}
	if (Random(0, 20) == 0) create({ Window::Width(), Random(0, Window::Height()) });
}
