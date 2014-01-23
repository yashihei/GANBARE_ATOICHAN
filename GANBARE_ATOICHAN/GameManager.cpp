#include "GameManager.h"

#include <Siv3D.hpp>
#include "Ship.h"
#include "Shot.h"
#include "Enemy.h"
#include "Bullet.h"
#include "StageManager.h"

GameManager::GameManager() {
	bulletManager = std::make_shared<BulletManager>();
	shotManager = std::make_shared<ShotManager>();
	ship = std::make_shared<Ship>(shotManager.get());
	enemyManager = std::make_shared<EnemyManager>();
	stageManager = std::make_shared<StageManager>(enemyManager.get());
}

void GameManager::move() {
	ship->move();
	shotManager->move();
	enemyManager->move();
	bulletManager->move();
	stageManager->move();
}

void GameManager::draw() {
	ship->draw();
	shotManager->draw();
	enemyManager->draw();
	bulletManager->draw();
}
