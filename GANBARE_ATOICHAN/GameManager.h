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
	void addScore(int val) { this->score += val; };
	//TODO:getter
private:
	std::shared_ptr<Ship> ship;
	std::shared_ptr<ShotManager> shotManager;
	std::shared_ptr<EnemyManager> enemyManager;
	std::shared_ptr<BulletManager> bulletManager;
	std::shared_ptr<StageManager> stageManager;
private:
	void checkHit();
	void drawState();
	State state;
	int score;
};
