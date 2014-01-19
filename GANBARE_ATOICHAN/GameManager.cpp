#include "GameManager.h"
#include "Ship.h"
#include "ShotManager.h"
#include <Siv3D.hpp>

GameManager::GameManager() {
	shotManager = std::make_shared<ShotManager>();
	ship = std::make_shared<Ship>(shotManager);
}

void GameManager::move() {
	ship->move();
	shotManager->move();
}

void GameManager::draw() {
	ship->draw();
	shotManager->draw();
}
