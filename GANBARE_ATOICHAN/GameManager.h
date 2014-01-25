#pragma once
#include <memory>

class Ship;
class ShotManager;
class EnemyManager;
class BulletManager;
class StageManager;
class CheckCollide;

class GameManager
{
public:
	GameManager();
	void move();
	void draw();
private:
	std::shared_ptr<Ship> ship;
	std::shared_ptr<ShotManager> shotManager;
	std::shared_ptr<EnemyManager> enemyManager;
	std::shared_ptr<BulletManager> bulletManager;
	std::shared_ptr<StageManager> stageManager;
	std::shared_ptr<CheckCollide> checkCollide;
};
