#pragma once
#include "TypeDef.h"

class GameManager
{
public:
	GameManager();
	void move();
	void draw();
private:
	ShipPtr ship;
	ShotManagerPtr shotManager;
	EnemyManagerPtr enemyManager;
};
