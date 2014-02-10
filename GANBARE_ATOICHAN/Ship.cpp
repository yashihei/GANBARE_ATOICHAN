#include "Ship.h"

#include "GameManager.h"
#include "Shot.h"
#include "Bullet.h"

Ship::Ship(GameManager* gm):
gm(gm)
{
	rad = 5.0;
	init();
}

void Ship::init() {
	life = 3;
	pos = { Window::Width() / 2, Window::Height() - 100 };
	cnt = 0;
	comeBack = false;
	muteki = false;
}

void Ship::move() {
	if (comeBack) comeBackControl();
	else moveControl();
	if (muteki) {
		mutekiCnt++;
		if (mutekiCnt > 200) muteki = false;
	}

	//fire
	if (Input::KeyZ.pressed && cnt % 3 == 0) {
		auto shots = gm->getShots();
		shots->create(pos + Vec2(-10.0, 0.0), { 0.0, -30.0 });
		shots->create(pos + Vec2(10.0, 0.0), { 0.0, -30.0 });
		if (slowMove) {
			shots->create(pos + Vec2(-15.0, 0.0), { 0.0, -30.0 });
			shots->create(pos + Vec2(15.0, 0.0), { 0.0, -30.0 });
		} else {
			shots->create(pos + Vec2(-10.0, 0.0), { -5.0, -30.0 });
			shots->create(pos + Vec2(10.0, 0.0), { 5.0, -30.0 });
		}
	}
	if (Input::KeySemicolon.clicked) life++;
	if (Input::KeyMinus.clicked) life--;
	cnt++;
}

void Ship::draw() {
	double num = rad * 3;
	Triangle t({ pos.x, pos.y - num }, { pos.x + num, pos.y + num }, { pos.x - num, pos.y + num });
	if (muteki) t.draw({ 255, 50, 50, 100 });
	else t.draw({255, 50, 50, 255});
	t.drawFrame(2.0, Palette::White);
	if (slowMove) Circle(pos, rad).draw({255, 255, 255, 255});
}

void Ship::destory() {
	if (muteki) return;
	LOG(L"ship destory!!");
	pos = { Window::Width() / 2, Window::Height() + rad };
	life--;
	gm->getBullets()->clear();
	comeBack = true;
	comeBackCnt = 0;
	muteki = true;
	mutekiCnt = 0;
	if (life < 0) gm->startGameOver();
}

void Ship::moveControl() {
	const double ROOT2 = 1.414;

	Joypad j(0);//�����
	if (Input::KeyShift.pressed || j.button(7).pressed) slowMove = true;
	else slowMove = false;

	Vec2 vel = { 0, 0 };
	const double speed = 5.5;
	if (Input::KeyLeft.pressed) vel.x -= speed;
	if (Input::KeyRight.pressed) vel.x = speed;
	if (Input::KeyUp.pressed) vel.y -= speed;
	if (Input::KeyDown.pressed) vel.y = speed;
	if (vel.x != 0 && vel.y != 0) {
		vel.x /= ROOT2;
		vel.y /= ROOT2;
	}
	//slow move
	if (slowMove) {
		vel.x *= 0.5;
		vel.y *= 0.5;
	}
	pos.moveBy(vel);
	//move control
	if (pos.x < 0) pos.x = 0;
	else if (pos.x > Window::Width()) pos.x = Window::Width();
	else if (pos.y < 0) pos.y = 0;
	else if (pos.y > Window::Height()) pos.y = Window::Height();
}

void Ship::comeBackControl() {
	comeBackCnt++;
	if (comeBackCnt > 50) {
		comeBack = false;
	}
	pos += {0.0, -2.0};
}
