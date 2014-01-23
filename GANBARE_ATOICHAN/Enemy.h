#pragma once
#include <Siv3D.hpp>
#include <list>

class EnemyMove;
class EnemyMoveFactory;
enum class EnemyMovePtn;

/*
 * Enemy.h
 * �G�I�u�W�F�N�g�Ȃ�
 * �G�̎�ނ͌p���ł͂Ȃ��A�ڏ��ɂ���ĕ\�������
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
	void create(Vec2 pos, EnemyMovePtn movePtn);//�ꏊ�ƁA�^�C�v
	void clear();
	void draw();
	void move();
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<EnemyMoveFactory> enemyMoveFactory;
};
