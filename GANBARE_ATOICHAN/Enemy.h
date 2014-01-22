#pragma once
#include <Siv3D.hpp>
#include <list>
#include "TypeDef.h"

class Enemy
{
public:
	Enemy();
	virtual void move() = 0;
	void draw();
protected:
	Vec2 pos;
	double rad;
	Color color;
	int cnt;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
};

class Enemy1 : public Enemy {
public:
	Enemy1();
	void move() override;
};

//敵の集合体、別のデザパタが適用出来ないか模索
class EnemyManager
{
public:
	EnemyManager();
	void create(Vec2 pos, int type);//場所と、タイプ
	void clear();
	void draw();
	void move();
private:
	std::list<EnemyPtr> enemies;
};
