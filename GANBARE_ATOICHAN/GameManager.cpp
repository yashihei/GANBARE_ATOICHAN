#include "GameManager.h"

#include <Siv3D.hpp>
#include "Ship.h"
#include "Shot.h"
#include "Enemy.h"

GameManager::GameManager() {
	shotManager = std::make_shared<ShotManager>();
	enemyManager = std::make_shared<EnemyManager>();
	ship = std::make_shared<Ship>(shotManager.get());
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
