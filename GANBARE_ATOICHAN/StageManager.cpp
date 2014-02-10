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
		//baramakiL1
		{ 550, { 0, 100 }, "baramakiL" },
		{ 590, { 0, 100 }, "baramakiL" },
		{ 630, { 0, 100 }, "baramakiL" },
		{ 670, { 0, 100 }, "baramakiL" },
		{ 710, { 0, 100 }, "baramakiL" },
		{ 750, { 0, 100 }, "baramakiL" },
		//bramakiR1
		{ 550, { WIDTH, 100 }, "baramakiR" },
		{ 590, { WIDTH, 100 }, "baramakiR" },
		{ 630, { WIDTH, 100 }, "baramakiR" },
		{ 670, { WIDTH, 100 }, "baramakiR" },
		{ 710, { WIDTH, 100 }, "baramakiR" },
		{ 750, { WIDTH, 100 }, "baramakiR" },
		//baranmakiL2
		{ 950, { 0, 100 }, "baramakiL" },
		{ 990, { 0, 100 }, "baramakiL" },
		{ 1030, { 0, 100 }, "baramakiL" },
		{ 1070, { 0, 100 }, "baramakiL" },
		{ 1110, { 0, 100 }, "baramakiL" },
		{ 1150, { 0, 100 }, "baramakiL" },
		//baranakiR2
		{ 950, { WIDTH, 100 }, "baramakiR" },
		{ 990, { WIDTH, 100 }, "baramakiR" },
		{ 1030, { WIDTH, 100 }, "baramakiR" },
		{ 1070, { WIDTH, 100 }, "baramakiR" },
		{ 1110, { WIDTH, 100 }, "baramakiR" },
		{ 1150, { WIDTH, 100 }, "baramakiR" },
		//nerai
		{ 650, { 100, 0 }, "nerai" },
		{ 650, { 350, 0 }, "nerai" },
		{ 850, { 100, 0 }, "nerai" },
		{ 850, { 350, 0 }, "nerai" },
		{ 1050, { 100, 0 }, "nerai" },
		{ 1050, { 350, 0 }, "nerai" },
		{ 1250, { 100, 0 }, "nerai" },
		{ 1250, { 350, 0 }, "nerai" },
		//tossin+middle
		{ 1550, { 100, 0 }, "tossin" },
		{ 1570, { 100, 0 }, "tossin" },
		{ 1550, { 350, 0 }, "tossin" },
		{ 1570, { 350, 0 }, "tossin" },
		{ 1650, { WIDTH/2, 0 }, "middle" },
		//galaxy
		//{ 1900, { 100, 0 }, "galaxy" },
		//{ 1900, { 350, 0 }, "galaxy" },
		//{ 2150, { 100, 0 }, "galaxy" },
		//{ 2150, { 350, 0 }, "galaxy" },
		//{ 2400, { 100, 0 }, "galaxy" },
		//{ 2400, { 350, 0 }, "galaxy" },
		//{ 2650, { 100, 0 }, "galaxy" },
		//{ 2650, { 350, 0 }, "galaxy" },
		////threewayL
		{ 1850, { 0, 100 }, "threewayL" },
		{ 1870, { 0, 100 }, "threewayL" },
		{ 1890, { 0, 100 }, "threewayL" },
		{ 1910, { 0, 100 }, "threewayL" },
		{ 1930, { 0, 100 }, "threewayL" },
		{ 1950, { 0, 100 }, "threewayL" },
		{ 1970, { 0, 100 }, "threewayL" },
		{ 1990, { 0, 100 }, "threewayL" },
		////threewayR
		{ 1850, { WIDTH, 100 }, "threewayR" },
		{ 1870, { WIDTH, 100 }, "threewayR" },
		{ 1890, { WIDTH, 100 }, "threewayR" },
		{ 1910, { WIDTH, 100 }, "threewayR" },
		{ 1930, { WIDTH, 100 }, "threewayR" },
		{ 1950, { WIDTH, 100 }, "threewayR" },
		{ 1970, { WIDTH, 100 }, "threewayR" },
		{ 1990, { WIDTH, 100 }, "threewayR" },

		//chubosu(‚±‚ê‚³‚¢‚²
		{ 3600, { WIDTH / 2, 0 }, "chubosu" },
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
	if (Input::KeyR.clicked) cnt = 0;//reset
	if (Input::KeyT.clicked) cnt = 1600;//reset
}
