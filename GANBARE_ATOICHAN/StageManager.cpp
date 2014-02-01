#include "StageManager.h"

#include "EnemyMove.h"
#include "Enemy.h"

StageManager::StageManager(EnemyManager* enemyManager)
:enemyManager(enemyManager)
{
	stage = 1;
	cnt = 0;
	const int WIDTH = 450;
	enemiesData = {
		//tossin1
		{ 0, { 30, 0 }, "tossin" },
		{ 20, { 80, 0 }, "tossin" },
		{ 40, { 130, 0 }, "tossin" },
		{ 100, { 420, 0 }, "tossin" },
		{ 120, { 370, 0 }, "tossin" },
		{ 140, { 320, 0 }, "tossin" },
		//tossin2
		{ 200, { 30, 0 }, "tossin" },
		{ 220, { 80, 0 }, "tossin" },
		{ 240, { 130, 0 }, "tossin" },
		{ 300, { 420, 0 }, "tossin" },
		{ 320, { 370, 0 }, "tossin" },
		{ 340, { 320, 0 }, "tossin" },
		//middle
		{ 400, { WIDTH / 2, 0 }, "middle" },
		//baramaki
		{ 600, { 0, 100 }, "baramakiL" },
		{ 640, { 0, 100 }, "baramakiL" },
		{ 680, { 0, 100 }, "baramakiL" },
		{ 600, { WIDTH, 100 }, "baramakiR" },
		{ 640, { WIDTH, 100 }, "baramakiR" },
		{ 680, { WIDTH, 100 }, "baramakiR" },
	};
}

void StageManager::move() {
	for (const auto& enemy : enemiesData) {
		if (enemy.cnt == cnt) {
			enemyManager->create(enemy.pos, enemy.name);
		}
	}
	cnt++;
	if (Input::KeyR.clicked) cnt = 0;//reset
	//if (cnt % 100 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, 0);
}
