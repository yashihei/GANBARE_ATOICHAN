#include <Siv3D.hpp>
#include "ShotManager.h"
#include "Ship.h";

Shot::Shot() {
	speed = 30.0;
	rad = 5.0;
}

void Shot::move() {
	pos.moveBy({ speed, 0 });
}

void Shot::draw() {
	Circle c(pos, rad);
	c.draw();
}

ShotManager::ShotManager() {
}

void ShotManager::create(const Vec2 pos)
{
	auto s = std::make_shared<Shot>();
	s->setPos(pos);
	shots.push_back(s);
}

void ShotManager::move() {
	for (auto& shot : shots) {
		shot->move();
	}
	autoRemove();
}

void ShotManager::draw() {
	for (auto& shot : shots) {
		shot->draw();
	}
}

void ShotManager::autoRemove() {
	for (auto it = shots.begin(); it != shots.end();) {
		if ((*it)->getPos().x > Window::Width()) {
			it = shots.erase(it);
			continue;
		}
		it++;
	}
}

void ShotManager::clear() {
	shots.clear();
}

