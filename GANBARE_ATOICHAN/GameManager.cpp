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
	SoundAsset::Register(L"music", L"dat/music.mp3", true);
	SoundAsset::Preload(L"music");
	SoundAsset::Register(L"burn", L"dat/burn.wav", true);
	SoundAsset::Register(L"shoot", L"dat/shoot.wav", true);
	SoundAsset::Register(L"damage", L"dat/damage.wav", true);
	TextureAsset::Register(L"bullet", L"dat/bullet.png");
	TextureAsset::Register(L"back", L"dat/back.png");
	TextureAsset::Register(L"shot", L"dat/shot.png");
	TextureAsset::Register(L"title", L"dat/title.png");
	TextureAsset::Register(L"start", L"dat/start.png");
	TextureAsset::Register(L"enemy", L"dat/enemy.png");
	TextureAsset::Register(L"explosion", L"dat/explosion.png");
	TextureAsset::Register(L"atoi", L"dat/atoi.png");
}

void GameManager::move() {
	switch (state) {
	case State::TITLE:
		//if (cnt % 120 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, "chubosu");
		if (enemyManager->getEnemies()->empty()) {
			//enemyManager->create({ Window::Width() / 2, 0 }, "chubosu");
		}
		stageManager->move();
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
		TextureAsset(L"title").draw( 0, 300 );
		if (cnt % 50 < 25) TextureAsset(L"start").draw( 0, 360 );
		FontAsset(L"metaFont").draw(L"", { 280, 570 }, Palette::White);
		break;
	case State::IN_GAME:
		shotManager->draw();
		enemyManager->draw();
		ship->draw();
		bulletManager->draw();
		drawState();
		break;
	case State::GAME_OVER:
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"font").drawCenter(L"GAME OVER", { Window::Width() / 2, 300 }, Palette::Black);
		FontAsset(L"font").drawCenter(L"GAME OVER", { Window::Width() / 2 - 2, 300 - 2 }, Palette::White);
		break;
	case State::GAME_CLEAR:
		ship->draw();
		shotManager->draw();
		enemyManager->draw();
		bulletManager->draw();
		FontAsset(L"font").drawCenter(L"GAME CLEAR", { Window::Width() / 2, 300 }, Palette::Black);
		FontAsset(L"font").drawCenter(L"GAME CLEAR", { Window::Width() / 2 - 2, 300 - 2 }, Palette::White);
		break;
	}
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

//いんふぉめーしょん
void GameManager::drawState() {
	//life num
	for (int i = 0; i < ship->getLife(); i++) {
		TextureAsset(L"atoi")(0, 0, 300, 430).scale(0.15).drawAt(30 + i * 30, Window::Height() - 35);
	}
	//WARNING
	int t = stageManager->getCnt();
	if (t > 2700 && t < 2800) {
		FontAsset(L"waring").drawCenter(L"WARNING", { Window::Width() / 2, Window::Height() / 2 }, { 255, 0, 0, 255 });
	}
	//TODO:HPバー処理
	auto enemies = enemyManager->getEnemies();
	if (!enemies->empty()) {
		//ボスならばHPバー表示
		if (enemies->back()->getIsBoss()) {
			double t = enemies->back()->getPerHp();
			Rect hpBar({ 25, 50 }, { (Window::Width() - 50) * t, 15 });
			//hpBar.draw({ 255, 255, 255, 200 });
			hpBar.draw(HSV(60 * t, 1.0, 1.0));
			hpBar.drawFrame(0.0, 1.5, Palette::White);
		}
	}
	//score
	FontAsset(L"font").draw(Format(L"SCORE:", score), { 10, 10 }, Palette::Black);
	FontAsset(L"font").draw(Format(L"SCORE:", score), { 8, 8 }, Palette::White);
	FontAsset(L"font").draw(Format(L"FPS:", Profiler::FPS()), { Window::Width() - 100, Window::Height() - 50 }, Palette::Black);
	FontAsset(L"font").draw(Format(L"FPS:", Profiler::FPS()), { Window::Width() - 100 - 2, Window::Height() - 50 - 2 }, Palette::White);
	//FontAsset(L"font").draw(Format(bulletManager->getBullets()->size()), { 10, 100 }, Palette::Black);
}

void GameManager::createExplosion(Vec2 pos, double size)
{
	auto e = std::make_shared<Explosion>(pos, size);
	explosions.push_back(e);
}

void GameManager::drawBack() {
	TextureAsset(L"back").draw(0, scrollCnt);
	TextureAsset(L"back").draw(0, -Window::Height() + scrollCnt);
	scrollCnt += 10;
	if (scrollCnt > Window::Height()) scrollCnt = 0;
}