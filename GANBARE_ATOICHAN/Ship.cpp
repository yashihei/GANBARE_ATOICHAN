#include <Siv3D.hpp>
#include "Ship.h"
#include "ShotManager.h"

Ship::Ship(std::shared_ptr<ShotManager> shotManager) {
	const int size = 10;
	core.setPos({ size , Window::Height() / 2 });
	core.setSize(size);

	this->shotManager = shotManager;
	cnt = 0;
}

void Ship::move() {
	Vec2 vel = { 0, 0 };
	const double speed = 3.5;
	if (Input::KeyLeft.pressed) vel.x -= speed;
	if (Input::KeyRight.pressed) vel.x = speed;
	if (Input::KeyUp.pressed) vel.y -= speed;
	if (Input::KeyDown.pressed) vel.y = speed;
	if (vel.x != 0 && vel.y != 0) {
		vel.x *= 0.707;
		vel.y *= 0.707;
	}
	core.moveBy(vel);
	//TODO: ウィンドウから出ないように

	if (Input::KeyZ.pressed && cnt % 10 == 0) {
		shotManager->createShot(this);
	}
	if (Input::KeyC.pressed) shotManager->clear();
	cnt++;
}

void Ship::draw() {
	core.draw(Palette::Red);
	core.drawFrame(2, 0, Palette::White);
}
