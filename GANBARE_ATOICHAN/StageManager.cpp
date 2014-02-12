#include "StageManager.h"

#include "Enemy.h"
#include "GameManager.h"

StageManager::StageManager(GameManager* gm):
gm(gm)
{
	const int WIDTH = Window::Width();
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
		{ 100, { WIDTH - 30, 0 }, "tossin" },
		{ 120, { WIDTH - 80, 0 }, "tossin" },
		{ 140, { WIDTH - 130, 0 }, "tossin" },
		//tossin2
		{ 200, { 30, 0 }, "tossin" },
		{ 220, { 80, 0 }, "tossin" },
		{ 240, { 130, 0 }, "tossin" },
		{ 300, { WIDTH - 30, 0 }, "tossin" },
		{ 320, { WIDTH - 80, 0 }, "tossin" },
		{ 340, { WIDTH - 130, 0 }, "tossin" },
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
		{ 650, { WIDTH - 100, 0 }, "nerai" },
		{ 850, { 100, 0 }, "nerai" },
		{ 850, { WIDTH - 100, 0 }, "nerai" },
		{ 1050, { 100, 0 }, "nerai" },
		{ 1050, { WIDTH - 100, 0 }, "nerai" },
		{ 1250, { 100, 0 }, "nerai" },
		{ 1250, { WIDTH - 100, 0 }, "nerai" },
		//tossin+middle
		{ 1550, { 100, 0 }, "tossin" },
		{ 1570, { 100, 0 }, "tossin" },
		{ 1550, { WIDTH - 100, 0 }, "tossin" },
		{ 1570, { WIDTH - 100, 0 }, "tossin" },
		{ 1650, { WIDTH/2, 0 }, "middle" },
		//galaxy
		{ 1900, { 100, 0 }, "galaxy" },
		{ 1900, { WIDTH - 100, 0 }, "galaxy" },
		{ 2150, { 100, 0 }, "galaxy" },
		{ 2150, { WIDTH - 100, 0 }, "galaxy" },
		////threewayL
		{ 2400, { 0, 100 }, "threewayL" },
		{ 2420, { 0, 100 }, "threewayL" },
		{ 2440, { 0, 100 }, "threewayL" },
		{ 2480, { 0, 100 }, "threewayL" },
		{ 2500, { 0, 100 }, "threewayL" },
		{ 2520, { 0, 100 }, "threewayL" },
		////threewayR
		{ 2400, { WIDTH, 100 }, "threewayR" },
		{ 2420, { WIDTH, 100 }, "threewayR" },
		{ 2440, { WIDTH, 100 }, "threewayR" },
		{ 2480, { WIDTH, 100 }, "threewayR" },
		{ 2500, { WIDTH, 100 }, "threewayR" },
		{ 2520, { WIDTH, 100 }, "threewayR" },

		//chubosu(‚±‚ê‚³‚¢‚²
		{ 2800, { WIDTH / 2, 0 }, "chubosu" },
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
	if (cnt > 2700 && cnt < 2800) {
		FontAsset(L"waring").drawCenter(L"WARING", { Window::Width() / 2, Window::Height() / 2 }, { 255, 0, 0, 255 });
	}
	if (Input::KeyR.clicked) cnt = 0;//reset
	if (Input::KeyT.clicked) cnt = 1600;//reset
}
