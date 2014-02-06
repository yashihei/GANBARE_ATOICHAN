#include "StageManager.h"

#include "Enemy.h"
#include "GameManager.h"

StageManager::StageManager(GameManager* gm):
gm(gm)
{
	stage = 1;
	cnt = 0;
	const int WIDTH = 450;
	//CSVReader csv(L"dat/stage.csv");
	//for (int i = 0; i < csv.rows; i++) {
	//}
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
		{ 400, { WIDTH/2, 0 }, "middle" },
		//baramaki
		{ 500, { 0, 100 }, "baramakiL" },
		{ 540, { 0, 100 }, "baramakiL" },
		{ 580, { 0, 100 }, "baramakiL" },
		{ 500, { WIDTH, 100 }, "baramakiR" },
		{ 540, { WIDTH, 100 }, "baramakiR" },
		{ 580, { WIDTH, 100 }, "baramakiR" },
		//bramaki2
		{ 650, { 0, 100 }, "baramakiL" },
		{ 690, { 0, 100 }, "baramakiL" },
		{ 720, { 0, 100 }, "baramakiL" },
		{ 650, { WIDTH, 100 }, "baramakiR" },
		{ 690, { WIDTH, 100 }, "baramakiR" },
		{ 720, { WIDTH, 100 }, "baramakiR" },
		//chubosu
		{ 1000, { WIDTH / 2, 0 }, "chubosu" },
	};
}
void StageManager::move() {
	for (const auto& enemy : enemiesData) {
		if (enemy.cnt == cnt) {
			gm->getEnemies()->create(enemy.pos, enemy.name);
		}
	}
	cnt++;
	if (Input::KeyR.clicked) cnt = 1000;//reset
	//if (cnt % 100 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, 0);
}
