#include "StageManager.h"

#include <Siv3D.hpp>
#include <string>
#include "EnemyMove.h"
#include "Enemy.h"

StageManager::StageManager(EnemyManager* enemyManager)
:enemyManager(enemyManager)
{
	stage = 1;
	cnt = 0;
}

void StageManager::move() {
	switch (stage)
	{
	case 1:
		if (cnt == 0) enemyManager->create({ 0, 50 }, "zako", "slowR", "Barrage1");
		//if (cnt == 0) enemyManager->create({ 400, 0 }, 0, 0, 1);
		//if (cnt == 30) enemyManager->create({ 0, 50 }, 0, 1, 0);
		//if (cnt == 50) enemyManager->create({ 0, 50 }, 0, 1, 0);
		//if (cnt == 80) enemyManager->create({ 0, 50 }, 0, 1, 0);
	default:
		break;
	}
	cnt++;
	if (Input::KeyR.clicked) cnt = 0;//reset
	//if (cnt % 100 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, 0);
}
