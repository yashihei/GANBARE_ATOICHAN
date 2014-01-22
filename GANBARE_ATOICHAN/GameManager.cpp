#include "GameManager.h"

#include <Siv3D.hpp>
#include "Ship.h"
#include "Shot.h"
#include "Enemy.h"
#include "Bullet.h"

GameManager::GameManager() {
	bulletManager = std::make_shared<BulletManager>();
	shotManager = std::make_shared<ShotManager>();
	enemyManager = std::make_shared<EnemyManager>(bulletManager.get());
	ship = std::make_shared<Ship>(shotManager.get());
}

void GameManager::move() {
	ship->move();
	shotManager->move();
	enemyManager->move();
	bulletManager->move();
}

void GameManager::draw() {
	ship->draw();
	shotManager->draw();
	enemyManager->draw();
	bulletManager->draw();
}
