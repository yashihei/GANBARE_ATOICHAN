#include "Bullet.h"

namespace EnemyMove {
	void tokasoku(Vec2* pos, Vec2* vel) {
		pos->moveBy(*vel);
	}

	void juryoku(Vec2* pos, Vec2* vel) {
		const double G = 0.03;
		*vel += {0, G};
		pos->moveBy(*vel);
	}
}

Bullet::Bullet(Vec2 pos, Vec2 vel, Color color, double rad, int moveType)
:pos(pos), vel(vel), color(color), rad(rad)
{
	if (moveType == 0) bulletMove = EnemyMove::tokasoku;
	else if (moveType == 1) bulletMove = EnemyMove::juryoku;
	cnt = 0;
}

void Bullet::move() {
	//pos.moveBy(vel);
	bulletMove(&pos, &vel);
	cnt++;
}

void Bullet::draw() {
	Circle c(pos, rad*1.5);
	c.draw(color);
	c.drawFrame(1.5, 0.0, Palette::White);
}

void BulletManager::create(Vec2 pos, Vec2 vel, Color color, double rad, int moveType)
{
	auto b = std::make_shared<Bullet>(pos, vel, color, rad, moveType);
	bullets.push_back(b);
}

void BulletManager::clear() {
	bullets.clear();
}

void BulletManager::draw() {
	for (const auto& bullet : bullets) {
		bullet->draw();
	}
}

void BulletManager::move() {
	for (auto it = bullets.begin(); it != bullets.end();) {
		(*it)->move();
		//TODO:Žb’èA‚Í‚Ýo‚·‚Ì‚É­‚µ—]—TŽ‚½‚¹
		double r = (*it)->getRad();
		if ((*it)->getPos().x > Window::Width() + r || (*it)->getPos().x < 0 - r ||
			(*it)->getPos().y > Window::Height() + r || (*it)->getPos().y < 0 - r) {
			it = bullets.erase(it);
			continue;
		}
		it++;
	}
}
