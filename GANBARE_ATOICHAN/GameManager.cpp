#include "GameManager.h"

#include <Siv3D.hpp>
#include "Ship.h"
#include "Shot.h"
#include "Enemy.h"
#include "Bullet.h"
#include "StageManager.h"
#include "CheckCollide.h"

GameManager::GameManager() {
	shotManager = std::make_shared<ShotManager>();
	bulletManager = std::make_shared<BulletManager>();
	ship = std::make_shared<Ship>(shotManager.get(), bulletManager.get());
	enemyManager = std::make_shared<EnemyManager>(this, ship.get(), bulletManager.get());
	stageManager = std::make_shared<StageManager>(enemyManager.get());
	state = State::IN_GAME;
	score = 0;
	FontAsset::Register(L"scoreFont", 20, Typeface::Black);
}

void GameManager::move() {
	ship->move();
	shotManager->move();
	enemyManager->move();
	bulletManager->move();
	stageManager->move();
	checkHit();
}

void GameManager::draw() {
	ship->draw();
	shotManager->draw();
	enemyManager->draw();
	bulletManager->draw();
	drawState();
}

void GameManager::checkHit() {
	auto shots = shotManager->getShots();
	auto bullets = bulletManager->getBullets();
	auto enemies = enemyManager->getEnemies();

	//shots and enemies
	for (auto s = shots->begin(); s != shots->end(); ++s) {
		for (auto e = enemies->begin(); e != enemies->end(); ++e) {
			Line line((*s)->getPos(), (*s)->getPos() + (*s)->getVel());
			Circle circle((*e)->getPos(), (*e)->getRad());
			if (Geometry::Intersect(line, circle)) {
				(*e)->damage();
				(*s)->burn();
			}
		}
	}
	//bullets and ship
	for (auto b = bullets->begin(); b != bullets->end(); ++b) {
		Line line((*b)->getPos(), (*b)->getPos() + (*b)->getVel());
		Circle circle(ship->getPos(), ship->getRad());
		if (Geometry::Intersect(line, circle)) {
			ship->destory();
			break;
		}
	}
}

void GameManager::drawState() {
	//life num
	for (int i = 0; i < ship->getLife(); i++) {
		double n = ship->getRad() * 3;
		double x = (n + 20) * i + 30;
		double y = Window::Height() - 30;
		Triangle t({ x, y - n }, { x + n, y + n }, { x - n, y + n });
		t.draw({ 255, 50, 50, 255 });
		t.drawFrame(2.0, Palette::White);
	}
	//score
	FontAsset(L"scoreFont").draw(Format(L"SCORE:", score), { 10, 10 }, Palette::White);
}
