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
		if (cnt == 0) enemyManager->create({ 50, 0 }, "futu", "Normal", "wayway");
		if (cnt == 0) enemyManager->create({ 400, 0 }, "futu", "Normal", "wayway");
		if (cnt == 0) enemyManager->create({ 0, 100 }, "zako", "slowL", "jikinerai");
		if (cnt == 30) enemyManager->create({ 0, 100 }, "zako", "slowL", "jikinerai");
		if (cnt == 60) enemyManager->create({ 0, 100 }, "zako", "slowL", "jikinerai");
		if (cnt == 0) enemyManager->create({ Window::Width(), 100 }, "zako", "slowR", "jikinerai");
		if (cnt == 30) enemyManager->create({ Window::Width(), 100 }, "zako", "slowR", "jikinerai");
		if (cnt == 60) enemyManager->create({ Window::Width(), 100 }, "zako", "slowR", "jikinerai");
	default:
		break;
	}
	cnt++;
	if (Input::KeyR.clicked) cnt = 0;//reset
	//if (cnt % 100 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, 0);
}
