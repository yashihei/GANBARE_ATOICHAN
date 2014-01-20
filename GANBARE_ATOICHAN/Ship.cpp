#include "Ship.h"

#include "Shot.h"

Ship::Ship(ShotManagerPtr shotManager) {
	rad = 10.0;
	this->shotManager = shotManager;

	pos.set({ rad, Window::Height() / 2 });
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
	pos.moveBy(vel);
	//TODO: ウィンドウから出ないように

	if (Input::KeyZ.pressed && cnt % 3 == 0) {
		shotManager->create(pos);
	}
	cnt++;
}

void Ship::draw() {
	Circle c(pos, rad);
	c.draw(Palette::Red);
	c.drawFrame(2, 0, Palette::White);
}
