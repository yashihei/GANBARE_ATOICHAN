#include "StageManager.h"

#include "EnemyMove.h"
#include "Enemy.h"

StageManager::StageManager(EnemyManager* enemyManager)
:enemyManager(enemyManager)
{
	stage = 1;
}

void StageManager::move() {
	switch (stage)
	{
	default:
		break;
	}
	cnt++;
	if (cnt % 100 == 0) enemyManager->create({ Random(0, Window::Width()), 0 }, 0);
}
