#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>

class Ship;
class BulletManager;
class ShotManager;
class EnemyMove;
class Barrage;
class EnemyMoveFactory;
class BarrageFactory;

/*
 * Enemy.h
 * 敵オブジェクトなの
 * 敵の行動は継承ではなく、移譲によって表現するの
 */

class Enemy
{
public:
	Enemy(Vec2 pos, Ship* ship, BulletManager* bulletManager, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage);
	//void init(Vec2 pos, Ship* ship, BulletManager* bulletManager, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage);
	void move();
	void draw();
	void damage();
protected:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	int subCnt = 3;//非ダメ表示用
	int hp;
	bool enable = true;
	Ship* ship;
	BulletManager* bulletManager;
	std::shared_ptr<EnemyMove> enemyMove;
	std::shared_ptr<Barrage> barrage;
public:
	//void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() const { return this->pos; };
	double getRad() const { return this->rad; };
	bool isEnable() const { return this->enable; };
};

class EnemyManager
{
public:
	EnemyManager(Ship* ship, BulletManager* bulletManager);
	void create(Vec2 pos, int enemyType, int moveType, int barrageType);//場所と、タイプ
	void clear();
	void draw();
	void move();
	const std::list<std::shared_ptr<Enemy>>* getEnemies() const { return &enemies; };
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	Ship* ship;
	BulletManager* bulletManager;
	ShotManager* shotManager;
	std::shared_ptr<EnemyMoveFactory> enemyMoveFactory;
	std::shared_ptr<BarrageFactory> barrageFactory;
};
