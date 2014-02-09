#include "Bullet.h"

namespace EnemyMove {
	void tokasoku(Vec2* pos, Vec2* vel) {
		pos->moveBy(*vel);
	}

	void juryoku(Vec2* pos, Vec2* vel) {
		const double G = 0.025;
		*vel += {0, G};
		pos->moveBy(*vel);
	}
}

void Bullet::init(Vec2 pos, Vec2 vel, Color color, int moveType) {
	this->pos = pos;
	this->vel = vel;
	this->color = color;
	if (moveType == 0) bulletMove = EnemyMove::tokasoku;
	else if (moveType == 1) bulletMove = EnemyMove::juryoku;
	cnt = 0;
	rad = 1.0;
	enable = true;
}

void Bullet::move() {
	bulletMove(&pos, &vel);
	cnt++;
	if (pos.x > Window::Width() + rad || pos.x < 0 - rad ||
		pos.y > Window::Height() + rad || pos.y < 0 - rad) {
		burn();
	}
}

void Bullet::draw() {
	Circle c(pos, 8.0);
	c.draw(color);
	c.drawFrame(1.5, 0.0, Palette::White);//これのコスト大きい
}

void Bullet::burn() {
	enable = false;
}

BulletManager::BulletManager() {
	bullets.resize(500);
	for (auto& bullet : bullets) {
		bullet = std::make_shared<Bullet>();
	}
}

void BulletManager::create(Vec2 pos, Vec2 vel, Color color, int moveType)
{
	for (const auto& bullet : bullets) {
		if (!bullet->getEnable()) {
			bullet->init(pos, vel, color, moveType);
			break;
		}
	}
}

void BulletManager::clear() {
	for (const auto& bullet : bullets) {
		bullet->burn();
	}
}

void BulletManager::draw() {
	for (const auto& bullet : bullets) {
		if (bullet->getEnable()) bullet->draw();
	}
}

void BulletManager::move() {
	for (const auto& bullet : bullets) {
		if (bullet->getEnable()) bullet->move();
	}
}
