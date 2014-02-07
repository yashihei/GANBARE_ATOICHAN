#include "GameManager.h"

#include "Ship.h"
#include "Shot.h"
#include "Enemy.h"
#include "Bullet.h"
#include "StageManager.h"
#include "CheckCollide.h"
#include "Actor.h"

GameManager::GameManager() {
	shotManager = std::make_shared<ShotManager>();
	bulletManager = std::make_shared<BulletManager>();
	ship = std::make_shared<Ship>(this);
	enemyManager = std::make_shared<EnemyManager>(this);
	stageManager = std::make_shared<StageManager>(this);
	state = State::TITLE;
	score = 0;
	cnt = 0;
	FontAsset::Register(L"font", 15, Typeface::Black);
	FontAsset::Register(L"titleFont", 30, Typeface::Black);
}

void GameManager::move() {
	switch (state) {
	case State::TITLE:
		if (cnt % 1000 == 0) enemyManager->create({ Window::Width() / 2, 0 }, "chubosu");
		cnt++;
		enemyManager->move();
		bulletManager->move();
		if (Input::KeyZ.clicked) startInGame();
		break;
	case State::IN_GAME:
		ship->move();
		shotManager->move();
		enemyManager->move();
		bulletManager->move();
		stageManager->move();
		checkHit();
		break;
	case State::GAME_OVER:
		enemyManager->move();
		bulletManager->move();
		stageManager->move();
		if (Input::KeyZ.clicked) state = State::TITLE;
		break;
	case State::GAME_CLEAR:
		ship->move();
		shotManager->move();
		enemyManager->move();
		bulletManager->move();
		stageManager->move();
		if (Input::KeyZ.clicked) state = State::TITLE;
		break;
	}
}

void GameManager::draw() {
	switch (state) {
	case State::TITLE:
		FontAsset(L"titleFont").draw(L"atoi(0141)", { 10, 300 }, Palette::White);
		if (cnt % 2 == 0) FontAsset(L"font").draw(L"PUSH SHOT BUTTON", { 10, 350 }, Palette::White);
		enemyManager->draw();
		bulletManager->draw();
		break;
	case State::IN_GAME:
		ship->draw();
		shotManager->draw();
		enemyManager->draw();
		bulletManager->draw();
		drawState();
		break;
	case State::GAME_OVER:
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"font").draw(L"GAME OVER", { 160, 300 }, Palette::White);
		break;
	case State::GAME_CLEAR:
		ship->draw();
		shotManager->draw();
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"font").draw(L"GAME CLEAR", { 160, 300 }, Palette::White);
	}
}

void GameManager::startInGame() {
	ship->init();
	shotManager->clear();
	enemyManager->clear();
	bulletManager->clear();
	stageManager->init();
	state = State::IN_GAME;
}

void GameManager::startGameOver() {
	state = State::GAME_OVER;
}

void GameManager::startClear() {
	state = State::GAME_CLEAR;
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
		if (!(*b)->getEnable()) continue;
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
	FontAsset(L"font").draw(Format(L"SCORE:", score), { 10, 10 }, Palette::White);
	FontAsset(L"font").draw(Format(L"FPS:", Profiler::FPS()), { Window::Width() - 100, Window::Height() - 50 }, Palette::White);
}
