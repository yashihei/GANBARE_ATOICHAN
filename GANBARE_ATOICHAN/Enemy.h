#pragma once
#include <Siv3D.hpp>
#include <list>

class EnemyMove;
class EnemyMoveFactory;
class BarrageFactory;
class Barrage;
class Ship;
class BulletManager;

/*
 * Enemy.h
 * �G�I�u�W�F�N�g�Ȃ�
 * �G�̎�ނ͌p���ł͂Ȃ��A�ڏ��ɂ���ĕ\�������
 */

class Enemy
{
public:
	Enemy(Ship* ship, BulletManager* bulletManager);
	void init(Vec2 pos, std::shared_ptr<EnemyMove> enemyMove, std::shared_ptr<Barrage> barrage);
	void move();
	void draw();
private:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	std::shared_ptr<EnemyMove> enemyMove;
	std::shared_ptr<Barrage> barrage;
	Ship* ship;
	BulletManager* bulletManager;
	//std::shared_ptr<danmakuPattern> hoge;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
};

class EnemyManager
{
public:
	EnemyManager(Ship* ship, BulletManager* bulletManager);
	void create(Vec2 pos, int moveType, int barrageType);//�ꏊ�ƁA�^�C�v
	void clear();
	void draw();
	void move();
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<EnemyMoveFactory> enemyMoveFactory;
	std::shared_ptr<BarrageFactory> barrageFactory;
	Ship* ship;
	BulletManager* bulletManager;
};
