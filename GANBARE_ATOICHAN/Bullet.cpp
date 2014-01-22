#include "Bullet.h"

Bullet::Bullet(Vec2 pos, Vec2 vel) :pos(pos), vel(vel) {
	rad = 5.0;
	color = Color(Palette::Wheat);
} 

void Bullet::move() {
	pos.moveBy(vel);
}

void Bullet::draw() {
	Circle c(pos, rad);
	c.draw(color);
}

void BulletManager::create(Vec2 pos, Vec2 vel)
{
	auto b = std::make_shared<Bullet>(pos, vel);
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
		//暫定、はみ出すのに少し余裕持たせ
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0) {
			it = bullets.erase(it);
			continue;
		}
		it++;
	}
}
