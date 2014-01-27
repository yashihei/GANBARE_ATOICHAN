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
	ship = std::make_shared<Ship>(shotManager.get());
	enemyManager = std::make_shared<EnemyManager>(ship.get(), bulletManager.get());
	stageManager = std::make_shared<StageManager>(enemyManager.get());
	checkCollide = std::make_shared<CheckCollide>(std::make_tuple(shotManager.get(), bulletManager.get(), enemyManager.get(), ship.get()));
}

void GameManager::move() {
	ship->move();
	shotManager->move();
	enemyManager->move();
	bulletManager->move();
	stageManager->move();
	checkCollide->move();
}

void GameManager::draw() {
	ship->draw();
	shotManager->draw();
	enemyManager->draw();
	bulletManager->draw();
}
