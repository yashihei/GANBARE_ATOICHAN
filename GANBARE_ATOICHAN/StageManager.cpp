#include "StageManager.h"

#include "EnemyMove.h"
#include "Enemy.h"

StageManager::StageManager(EnemyManager* enemyManager)
:enemyManager(enemyManager)
{
}

void StageManager::move() {
	cnt++;
	if (cnt % 100 == 0) enemyManager->create({ Window::Width(), Random(0, Window::Height()) }, 1);
}
