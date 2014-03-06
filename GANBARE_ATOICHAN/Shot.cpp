#include "Shot.h"

#include "Ship.h"

Shot::Shot(Vec2 pos, Vec2 vel):
pos(pos), vel(vel)
{
	enable = true;
}

void Shot::move() {
	pos.moveBy(vel);
	if (pos.x > Window::Height() || pos.x < 0 || pos.y > Window::Height() || pos.y < -100) {
		enable = false;
	}
}

void Shot::draw() {
	TextureAsset(L"shot").drawAt(pos);
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
	for (auto& shot : shots) {
		shot->move();
	}
	Erase_if(shots, [](std::shared_ptr<Shot> shot) {return !shot->getEnable(); });
}

void ShotManager::draw() {
	for (auto& shot : shots) {
		shot->draw();
	}
}

void ShotManager::clear() {
	shots.clear();
}

