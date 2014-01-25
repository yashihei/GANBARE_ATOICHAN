#pragma once
#include <list>
#include <memory>
#include <tuple>

class Enemy;
class Shot;
class Bullet;
class ShotManager;
class BulletManager;
class Ship;
class EnemyManager;

class CheckCollide
{
public:
	CheckCollide(ShotManager* shotManager, BulletManager* bulletManager, Ship* ship, EnemyManager* enemyManager);
	CheckCollide(std::tuple<ShotManager*, BulletManager*, EnemyManager*, Ship*> args);//tupletest
	void move();
private:
	const std::list<std::shared_ptr<Enemy>>* enemies;
	const std::list<std::shared_ptr<Shot>>* shots;
	const std::list<std::shared_ptr<Bullet>>* bullets;
	Ship* ship;
};

