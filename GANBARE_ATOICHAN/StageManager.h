#pragma once
#include <memory>
/*
 * StageManager.h
 * �G�I�u�W�F�N�g�̔z�u�Ƃ��s����
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
