#pragma once

#include <Siv3D.hpp>
#include <memory>
#include <string>
#include <vector>
/*
 * StageManager.h
 * �Ƃ肠�����z��ł΁[����
 */

class GameManager;

struct EnemiesData {
	int cnt;
	Vec2 pos;
	std::string name;
};

class StageManager
{
public:
	StageManager(GameManager* gm);
	//void init();
	void move();
private:
	int cnt = 0;
	int stage;
	GameManager* gm;
	std::vector<EnemiesData> enemiesData;
};
