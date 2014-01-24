#include "Shot.h"

#include "Ship.h"

Shot::Shot() {
	speed = 30.0;
	rad = 5.0;
	vel = { 30.0, 0.0 };
}

void Shot::move() {
	pos.moveBy(vel);
}

void Shot::draw() {
	//Quad q({ pos.x - 10, pos.y + 7 }, { pos.x + 10, pos.y + 5 }, { pos.x + 10, pos.y - 5 }, { pos.x - 10, pos.y - 7 });
	//q.draw(Color(255, 255, 0, 127));
	//q.drawFrame(2.0, Palette::White);
	//Line(pos, pos+vel).draw(Palette::White);
	Circle c(pos, rad);
	c.draw();
}

ShotManager::ShotManager() {
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
		if ((*it)->getPos().x > Window::Width()) {
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

