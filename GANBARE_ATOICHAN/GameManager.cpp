#include "GameManager.h"

#include "Ship.h"
#include "Shot.h"
#include "Enemy.h"
#include "Bullet.h"
#include "StageManager.h"
#include "CheckCollide.h"
#include "Actor.h"
#include "Explosion.h"

GameManager::GameManager() {
	shotManager = std::make_shared<ShotManager>();
	bulletManager = std::make_shared<BulletManager>();
	ship = std::make_shared<Ship>(this);
	enemyManager = std::make_shared<EnemyManager>(this);
	stageManager = std::make_shared<StageManager>(this);
	state = State::TITLE;
	score = 0;
	cnt = 0;
	scrollCnt = 0;
	FontAsset::Register(L"font", 15, Typeface::Black);
	FontAsset::Register(L"titleFont", 20, Typeface::Black);
	FontAsset::Register(L"metaFont", 10, Typeface::Black);
	FontAsset::Register(L"waring", 40, Typeface::Black);
	SoundAsset::Register(L"music", L"dat/.wav", true);
	SoundAsset::Preload(L"music");
	SoundAsset::Register(L"burn", L"dat/burn.wav", true);
	SoundAsset::Register(L"shoot", L"dat/shoot.wav", true);
	SoundAsset::Register(L"damage", L"dat/damage.wav", true);
	TextureAsset::Register(L"bullet", L"dat/bullet.png");
	TextureAsset::Register(L"back", L"dat/back.png");
	TextureAsset::Register(L"shot", L"dat/shot.png");
}

void GameManager::move() {
	switch (state) {
	case State::TITLE:
		//if (cnt % 120 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, "chubosu");
		if (enemyManager->getEnemies()->empty()) {
			enemyManager->create({ Window::Width() / 2, 0 }, "chubosu");
		}
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
		break;
	case State::GAME_CLEAR:
		ship->move();
		shotManager->move();
		enemyManager->move();
		bulletManager->move();
		break;
	}
	if (state == State::GAME_CLEAR || state == State::GAME_OVER) {
		if (Input::KeyZ.clicked || cnt > 300) {
			SoundAsset(L"music").stop();
			state = State::TITLE;
		}
	}
	for (auto& explotion : explosions) explotion->move();
	Erase_if(explosions, [](std::shared_ptr<Explosion> explotion) { return !explotion->isEnable(); });
	cnt++;
}

void GameManager::draw() {
	drawBack();
	switch (state) {
	case State::TITLE:
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"titleFont").draw(L"DANMAKU", { 10, 300 }, Palette::White);
		if (cnt % 20 < 10) FontAsset(L"font").draw(L"PRESS SHOT BUTTON", { 10, 350 }, Palette::White);
		FontAsset(L"metaFont").draw(L"", { 280, 570 }, Palette::White);
		break;
	case State::IN_GAME:
		ship->draw();
		shotManager->draw();
		enemyManager->draw();
		bulletManager->draw();
		break;
	case State::GAME_OVER:
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"font").drawCenter(L"GAME OVER", { Window::Width()/2, 300 }, Palette::White);
		break;
	case State::GAME_CLEAR:
		ship->draw();
		shotManager->draw();
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"font").drawCenter(L"GAME CLEAR", { Window::Width()/2, 300 }, Palette::White);
		break;
	}
	drawState();
	for (auto& explotion : explosions) explotion->draw();
}

void GameManager::startInGame() {
	ship->init();
	shotManager->clear();
	enemyManager->clear();
	bulletManager->clear();
	stageManager->init();
	score = 0;
	state = State::IN_GAME;
	SoundAsset(L"music").play();
	SoundAsset(L"music").setVolume(0.5);
}

void GameManager::startGameOver() {
	state = State::GAME_OVER;
	cnt = 0;
}

void GameManager::startClear() {
	state = State::GAME_CLEAR;
	cnt = 0;
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
	//auto e = enemyManager->getEnemies->back();
	if (false) {
		//double t = (double)hp / (double)maxHp;
		double t = 0.5;
		Rect hpBar({ 25, 50 }, { (Window::Width() - 50) * t, 15 });
		//hpBar.draw({ 255, 255, 255, 200 });
		hpBar.draw(HSV(60 * t, 1.0, 1.0));
		hpBar.drawFrame(0.0, 1.5, Palette::White);
	}
	//score
	FontAsset(L"font").draw(Format(L"SCORE:", score), { 10, 10 }, Palette::Darkgray);
	FontAsset(L"font").draw(Format(L"FPS:", Profiler::FPS()), { Window::Width() - 100, Window::Height() - 50 }, Palette::Darkgray);
	//FontAsset(L"font").draw(Format(bulletManager->getBullets()->size()), { 10, 100 }, Palette::Black);
}

void GameManager::createExplosion(Vec2 pos, int num)
{
	auto e = std::make_shared<Explosion>(pos, num);
	explosions.push_back(e);
}

void GameManager::drawBack() {
	TextureAsset(L"back").draw(0, scrollCnt);
	TextureAsset(L"back").draw(0, -Window::Height() + scrollCnt);
	scrollCnt += 5;
	if (scrollCnt > Window::Height()) scrollCnt = 0;
}