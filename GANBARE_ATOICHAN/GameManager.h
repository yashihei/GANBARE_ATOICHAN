#pragma once
#include <memory>

class Ship;
class ShotManager;
class EnemyManager;
class BulletManager;
class StageManager;

class GameManager
{
public:
	enum class State {
		TITLE,
		IN_GAME,
		PAUSE,
		GAME_OVER,
	};

	GameManager();
	void move();
	void draw();
public://�n���̂��邢�̂�
	std::shared_ptr<Ship> ship;
	std::shared_ptr<ShotManager> shotManager;
	std::shared_ptr<EnemyManager> enemyManager;
	std::shared_ptr<BulletManager> bulletManager;
	std::shared_ptr<StageManager> stageManager;
private:
	void checkHit();
	State state;
};
