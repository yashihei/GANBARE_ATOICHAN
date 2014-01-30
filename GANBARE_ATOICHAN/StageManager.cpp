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
		if (cnt == 0) enemyManager->create({ 30, 0 }, "zako", 1);
		if (cnt == 10) enemyManager->create({ 80, 0 }, "zako", 1);
		if (cnt == 20) enemyManager->create({ 130, 0 }, "zako", 1);

		if (cnt == 100) enemyManager->create({ 420, 0 }, "zako", 1);
		if (cnt == 110) enemyManager->create({ 370, 0 }, "zako", 1);
		if (cnt == 120) enemyManager->create({ 320, 0 }, "zako", 1);
	default:
		break;
	}
	cnt++;
	if (Input::KeyR.clicked) cnt = 0;//reset
	//if (cnt % 100 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, 0);
}
