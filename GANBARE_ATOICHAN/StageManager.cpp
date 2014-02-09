#include "StageManager.h"

#include "Enemy.h"
#include "GameManager.h"

StageManager::StageManager(GameManager* gm):
gm(gm)
{
	const int WIDTH = 450;
	//CSVReader csv(L"dat/stage.csv");
	//for (int i = 0; i < csv.rows; i++) {
	//	EnemiesData e;
	//	e.cnt = csv.get<int>(i, 0, 0);
	//	e.pos = csv.get<Vec2>(i, 1, { 0, 0 });
	//	e.name = csv.get<std::string>(i, 2, "zako");
	//	enemiesData.push_back(e);
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
		{ 550, { 0, 100 }, "baramakiL" },
		{ 590, { 0, 100 }, "baramakiL" },
		{ 630, { 0, 100 }, "baramakiL" },
		{ 670, { 0, 100 }, "baramakiL" },
		{ 710, { 0, 100 }, "baramakiL" },
		{ 750, { 0, 100 }, "baramakiL" },
		//bramaki2
		{ 550, { WIDTH, 100 }, "baramakiR" },
		{ 590, { WIDTH, 100 }, "baramakiR" },
		{ 630, { WIDTH, 100 }, "baramakiR" },
		{ 670, { WIDTH, 100 }, "baramakiR" },
		{ 710, { WIDTH, 100 }, "baramakiR" },
		{ 750, { WIDTH, 100 }, "baramakiR" },
		//nerai
		{ 650, { 100, 0 }, "nerai" },
		{ 650, { 350, 0 }, "nerai" },
		{ 850, { 100, 0 }, "nerai" },
		{ 850, { 350, 0 }, "nerai" },
		//tossin+middle
		{ 1150, { 100, 0 }, "tossin" },
		{ 1170, { 100, 0 }, "tossin" },
		{ 1150, { 350, 0 }, "tossin" },
		{ 1170, { 350, 0 }, "tossin" },
		{ 1250, { WIDTH/2, 0 }, "middle" },
		//threeway
		{ 1450, { 0, 100 }, "threewayL" },
		{ 1470, { 0, 100 }, "threewayL" },
		{ 1490, { 0, 100 }, "threewayL" },
		{ 1550, { 0, 100 }, "threewayL" },
		{ 1570, { 0, 100 }, "threewayL" },
		{ 1590, { 0, 100 }, "threewayL" },
		//threewayR
		{ 1650, { WIDTH, 100 }, "threewayR" },
		{ 1670, { WIDTH, 100 }, "threewayR" },
		{ 1690, { WIDTH, 100 }, "threewayR" },
		{ 1750, { WIDTH, 100 }, "threewayR" },
		{ 1770, { WIDTH, 100 }, "threewayR" },
		{ 1790, { WIDTH, 100 }, "threewayR" },
		//chubosu(‚±‚ê‚³‚¢‚²
		//{ 1000, { WIDTH / 2, 0 }, "chubosu" },
	};
}

void StageManager::init() {
	cnt = -100;//delay
}

void StageManager::move() {
	for (const auto& enemy : enemiesData) {
		if (enemy.cnt == cnt) {
			gm->getEnemies()->create(enemy.pos, enemy.name);
		}
	}
	cnt++;
	if (Input::KeyR.clicked) cnt = 1400;//reset
}
