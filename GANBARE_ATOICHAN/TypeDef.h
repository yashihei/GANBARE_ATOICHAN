#pragma once
#include <memory>

/*
1箇所でしか呼ばれないshared_ptrについては、typedefしないかも
*/

class Ship;
class Enemy;
class EnemyManager;
class Shot;
class ShotManager;

typedef std::shared_ptr<Ship> ShipPtr;
typedef std::shared_ptr<EnemyManager> EnemyManagerPtr;
typedef std::shared_ptr<Enemy> EnemyPtr;
typedef std::shared_ptr<Shot> ShotPtr;
typedef std::shared_ptr<ShotManager> ShotManagerPtr;
