#include "GameManager.h"
#include "Ship.h"
#include "ShotManager.h"
#include "EnemyManager.h"
#include <Siv3D.hpp>

GameManager::GameManager() {
	shotManager = std::make_shared<ShotManager>();
	enemyManager = std::make_shared<EnemyManager>();
	ship = std::make_shared<Ship>(shotManager);
}

void GameManager::move() {
	ship->move();
	shotManager->move();
	enemyManager->move();
}

void GameManager::draw() {
	ship->draw();
	shotManager->draw();
	enemyManager->draw();
}
