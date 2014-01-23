#pragma once
#include <memory>
/*
 * StageManager.h
 * 敵オブジェクトの配置とか行うの
 */

class EnemyManager;

class StageManager
{
public:
	StageManager(EnemyManager* enemyManager);
	//void init();
	void move();
private:
	int cnt = 0;
	EnemyManager* enemyManager;
};
