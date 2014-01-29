#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>
#include <hash_map>
#include <string>
#include <tuple>

class Ship;
class BulletManager;
class ShotManager;
class EnemyMove;
class Barrage;
class EnemyMoveFactory;
class BarrageFactory;
class EnemyDataFactory;
struct EnemyData;

/*
 * Enemy.h
 * 敵オブジェクトなの
 * 敵の行動は継承ではなく、移譲によって表現するの
 */

class Enemy
{
public:
	Enemy(Ship* ship, BulletManager* bulletManager);
	void setParam(Vec2 pos, EnemyData enemyData, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage);
	void move();
	void draw();
	void damage();
	//getter
	Vec2 getPos() const { return this->pos; };
	double getRad() const { return this->rad; };
	bool isEnable() const { return this->enable; };
protected:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	int subCnt = 3;//非ダメ表示用
	int hp;
	bool enable = true;
	int limit;
	Ship* ship;
	BulletManager* bulletManager;
	std::shared_ptr<EnemyMove> enemyMove;
	std::shared_ptr<Barrage> barrage;
};

class EnemyManager
{
public:
	EnemyManager(Ship* ship, BulletManager* bulletManager);
	void create(Vec2 pos, std::string enemyType, std::string moveType, std::string barrageType);//場所と、タイプ
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
	std::shared_ptr<EnemyDataFactory> enemyDataFactory;
};
