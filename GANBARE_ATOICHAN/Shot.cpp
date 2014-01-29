#include "Shot.h"

#include "Ship.h"

Shot::Shot(Vec2 pos, Vec2 vel):
pos(pos), vel(vel)
{
}

void Shot::move() {
	pos.moveBy(vel);
}

void Shot::draw() {
	Line l(pos, pos + vel);
	l.draw(3.0, { 255, 255, 255, 200 });
}

void Shot::burn()
{
	enable = false;
}

void ShotManager::create(Vec2 pos, Vec2 vel)
{
	auto s = std::make_shared<Shot>(pos, vel);
	shots.push_back(s);
}

void ShotManager::move() {
	for (auto it = shots.begin(); it != shots.end();) {
		(*it)->move();
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0 ||
			(*it)->getPos().y > Window::Height() || (*it)->getPos().y < -100 ||
			!(*it)->getEnable())
		{
			it = shots.erase(it);
			continue;
		}
		it++;
	}
}

void ShotManager::draw() {
	for (auto& shot : shots) {
		shot->draw();
	}
}

void ShotManager::clear() {
	shots.clear();
}

