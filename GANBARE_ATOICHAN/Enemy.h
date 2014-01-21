#pragma once
#include <Siv3D.hpp>
#include <list>
#include "TypeDef.h"

// Strategy Pattern
class EnemyMove {
public:
	virtual ~EnemyMove(){};
	virtual void move(Vec2* pos, int cnt) = 0;
};

class EnemyMove1 : public EnemyMove {
	void move(Vec2* pos, int cnt) override;
};

class Enemy
{
public:
	Enemy(Vec2 pos);
	void move();
	void draw();
protected:
	Vec2 pos;
	double rad;
	Palette palette;
	std::shared_ptr<EnemyMove> enemyMove;
	int cnt;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
};

//�G�̏W���́A�ʂ̃f�U�p�^���K�p�o���Ȃ����͍�
class EnemyManager
{
public:
	EnemyManager();
	void create(Vec2 pos);//�ꏊ�ƁA�^�C�v
	void clear();
	void draw();
	void move();
private:
	std::list<EnemyPtr> enemies;
};
