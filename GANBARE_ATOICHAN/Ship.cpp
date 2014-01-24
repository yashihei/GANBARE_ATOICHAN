#include "Ship.h"

#include "Shot.h"

Ship::Ship(ShotManager* shotManager) {
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
	//slow move
	if (Input::KeyShift.pressed) {
		vel.x *= 0.5;
		vel.y *= 0.5;
	}
	pos.moveBy(vel);
	//move control
	if (pos.x < 0) pos.x = 0;
	else if (pos.x > Window::Width()) pos.x = Window::Width();
	else if (pos.y < 0) pos.y = 0;
	else if (pos.y > Window::Height()) pos.y = Window::Height();

	if (Input::KeyZ.pressed && cnt % 3 == 0) {
		shotManager->create(pos);
	}
	cnt++;
}

void Ship::draw() {
	Triangle t({ pos.x - rad, pos.y + rad }, { pos.x + rad, pos.y }, { pos.x - rad, pos.y - rad });
	t.draw({255, 0, 0, 200});
	t.drawFrame(2, Palette::White);
}

void Ship::damage()
{
}
