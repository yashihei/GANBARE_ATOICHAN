#include "Shot.h"

#include "Ship.h"

Shot::Shot() {
	rad = 5.0;
	vel = { 0.0, -30.0 };
	enable = true;
}

void Shot::move() {
	pos.moveBy(vel);
}

void Shot::draw() {
	Line l(pos, pos + Vec2(0.0, 10.0));
	l.draw(3.0, Palette::White);
}

void Shot::burn()
{
	enable = false;
}

void ShotManager::create(Vec2 pos)
{
	auto s = std::make_shared<Shot>();
	s->setPos(pos);
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

