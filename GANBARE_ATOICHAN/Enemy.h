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
 */

class Enemy
{
public:
	//Enemy(Ship* ship, BulletManager* bulletManager);
	Enemy(){};
	void setParam(Vec2 pos, int dir, Ship* ship, BulletManager* bulletManager);
	virtual void move() = 0;
	virtual void draw();
	void defalutMove();
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
	int dir = 1;
	int limit;
	Ship* ship;
	BulletManager* bulletManager;
};

class Enemy1 : public Enemy
{
public:
	Enemy1();
	void move() override;
};

class EnemyManager
{
public:
	EnemyManager(Ship* ship, BulletManager* bulletManager);
	void create(Vec2 pos, int type, int dir);//場所と、タイプ
	void clear();
	void draw();
	void move();
	const std::list<std::shared_ptr<Enemy>>* getEnemies() const { return &enemies; };
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	Ship* ship;
	BulletManager* bulletManager;
};
