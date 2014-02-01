#include "Bullet.h"

Bullet::Bullet(Vec2 pos, Vec2 vel, Color color, double rad)
:pos(pos), vel(vel), color(color), rad(rad)
{
	cnt = 0;
}

void Bullet::move() {
	pos.moveBy(vel);
	cnt++;
}

void Bullet::draw() {
	Circle c(pos, rad*1.5);
	c.draw(color);
	c.drawFrame(1.5, 0.0, Palette::White);
}

void BulletManager::create(Vec2 pos, Vec2 vel, Color color, double rad, int moveType)
{
	auto b = std::make_shared<Bullet>(pos, vel, color, rad);
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
		//Žb’èA‚Í‚Ýo‚·‚Ì‚É­‚µ—]—TŽ‚½‚¹
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0 || (*it)->getPos().y > Window::Height() || (*it)->getPos().y < 0) {
			it = bullets.erase(it);
			continue;
		}
		it++;
	}
}
