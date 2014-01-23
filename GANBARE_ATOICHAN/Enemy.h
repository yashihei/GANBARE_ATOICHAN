#pragma once
#include <Siv3D.hpp>
#include <list>

class EnemyMove;
class EnemyMoveFactory;
enum class EnemyMovePtn;

/*
 * Enemy.h
 * 敵オブジェクトなの
 * 敵の種類は継承ではなく、移譲によって表現するの
 */

typedef std::shared_ptr<EnemyMove> EnemyMovePtr;

class Enemy
{
public:
	Enemy();
	void init(Vec2 pos, std::shared_ptr<EnemyMove> enemyMove);
	void move();
	void draw();
private:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	EnemyMovePtr enemyMove;
	//std::shared_ptr<danmakuPattern> hoge;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
};

class EnemyManager
{
public:
	EnemyManager();
	void create(Vec2 pos, EnemyMovePtn movePtn);//場所と、タイプ
	void clear();
	void draw();
	void move();
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<EnemyMoveFactory> enemyMoveFactory;
};
