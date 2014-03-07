#pragma once
#include <Siv3D.hpp>
#include <memory>
#include <list>

class Ship;
class ShotManager;
class EnemyManager;
class BulletManager;
class StageManager;
class Explosion;

class GameManager
{
public:
	enum class State {
		TITLE,
		IN_GAME,
		PAUSE,
		GAME_OVER,
		GAME_CLEAR,
	};

	GameManager();
	void move();
	void draw();
	void addScore(int val) { this->score += val; };
	void startGameOver();
	void startClear();
	void createExplosion(Vec2 pos);
	void drawBack();
	//TODO:getter
	Ship* getShip() { return ship.get(); }
	ShotManager* getShots() { return shotManager.get(); }
	BulletManager* getBullets() { return bulletManager.get(); }
	EnemyManager* getEnemies() { return enemyManager.get(); }
private:
	std::shared_ptr<Ship> ship;
	std::shared_ptr<ShotManager> shotManager;
	std::shared_ptr<EnemyManager> enemyManager;
	std::shared_ptr<BulletManager> bulletManager;
	std::shared_ptr<StageManager> stageManager;
	std::list<std::shared_ptr<Explosion>> explosions;
private:
	void checkHit();
	void drawState();
	void startInGame();
	State state;
	int score;
	int cnt;
	int scrollCnt;
};
