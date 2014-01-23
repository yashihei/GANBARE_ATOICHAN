#include "StageManager.h"

#include "EnemyMove.h"
#include "Enemy.h"

StageManager::StageManager(EnemyManager* enemyManager)
:enemyManager(enemyManager)
{
}

void StageManager::move() {
	cnt++;
	if (cnt % 10 == 0) enemyManager->create({ Window::Width(), Random(0, Window::Height()) }, EnemyMovePtn::NORMAL);
}
