#pragma once
#include <memory>

/*
1‰ÓŠ‚Å‚µ‚©ŒÄ‚Î‚ê‚È‚¢shared_ptr‚É‚Â‚¢‚Ä‚ÍAtypedef‚µ‚È‚¢‚©‚à
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
