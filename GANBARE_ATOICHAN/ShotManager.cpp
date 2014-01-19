#include <Siv3D.hpp>
#include "ShotManager.h"
#include "Ship.h";

Shot::Shot() {
	core.setSize(5);
}

ShotManager::ShotManager() {
}

void ShotManager::createShot(Ship* ship) {
	auto s = std::make_shared<Shot>();
	s->core.center = ship->core.center;
	shots.push_back(s);
}

void ShotManager::move() {
	for (auto shot : shots) {
		shot->core.moveBy({ 10, 0 });
	}
	autoRemove();
}

void ShotManager::draw() {
	for (auto shot : shots) {
		shot->core.draw();
	}
}

void ShotManager::autoRemove() {
	for (auto it = shots.begin(); it != shots.end();) {
		if ((*it)->core.x > Window::Width()) {
			it = shots.erase(it);
			continue;
		}
		it++;
	}
}

void ShotManager::clear() {
	shots.clear();
}

