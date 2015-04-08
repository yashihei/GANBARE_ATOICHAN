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
	if (gm->isEasy()) life = 5;
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
	if ((Input::KeyZ.pressed || gm->getController()->buttonX.pressed) && cnt % 3 == 0) {
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
		SoundAsset(L"shoot").playMulti();
	}
	if (Input::KeySemicolon.clicked) life++;
	if (Input::KeyMinus.clicked) life--;
	cnt++;
}

void Ship::draw() {
	int a = 255;
	if (muteki) a = 150;
	if (cnt % 10 < 5) TextureAsset(L"atoi")(0, 0, 300, 430).scale(0.2).drawAt(pos, Alpha(a));
	else TextureAsset(L"atoi")(300, 0, 300, 430).scale(0.2).drawAt(pos, Alpha(a));
	if (slowMove) Circle(pos, rad).draw({ 255, 0, 0, 255 });
}

void Ship::destory() {
	if (muteki) return;
	pos = { Window::Width() / 2, Window::Height() + rad };
	life--;
	SoundAsset(L"damage").playMulti();
	gm->getBullets()->clear();
	comeBack = true;
	comeBackCnt = 0;
	muteki = true;
	mutekiCnt = 0;
	if (life < 0) gm->startGameOver();
}

void Ship::moveControl() {
	const double ROOT2 = 1.414;

	auto controller = gm->getController();

	if (Input::KeyShift.pressed || controller->buttonRB.pressed) slowMove = true;
	else slowMove = false;

	Vec2 vel = { 0, 0 };
	const double speed = 5.5;
	//“ËŠÑHŽ–
	const double limit = 0.4;
	if (Input::KeyLeft.pressed || controller->buttonLeft.pressed || (controller->leftThumbX < -limit)) vel.x -= speed;
	if (Input::KeyRight.pressed || controller->buttonRight.pressed || (controller->leftThumbX > limit)) vel.x = speed;
	if (Input::KeyUp.pressed || controller->buttonUp.pressed || (controller->leftThumbY > limit)) vel.y -= speed;
	if (Input::KeyDown.pressed || controller->buttonDown.pressed || (controller->leftThumbY < -limit)) vel.y = speed;
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
