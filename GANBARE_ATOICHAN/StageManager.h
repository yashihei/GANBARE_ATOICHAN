#pragma once

#include <Siv3D.hpp>
#include <memory>
#include <string>
#include <vector>
/*
 * StageManager.h
 * �Ƃ肠�����z��ł΁[����
 */

class EnemyManager;

struct EnemiesData {
	int cnt;
	Vec2 pos;
	std::string name;
};

class StageManager
{
public:
	StageManager(EnemyManager* enemyManager);
	//void init();
	void move();
private:
	int cnt = 0;
	int stage;
	EnemyManager* enemyManager;
	std::vector<EnemiesData> enemiesData;
};
