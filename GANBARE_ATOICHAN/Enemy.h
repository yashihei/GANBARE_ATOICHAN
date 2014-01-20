#pragma once
#include <Siv3D.hpp>
#include <list>
#include "TypeDef.h"

class Enemy
{
public:
	Enemy();
	virtual void move();
	virtual void draw();
protected:
	double rad;
	Vec2 pos;
	int cnt;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
};

class EnemyManager
{
public:
	EnemyManager();
	void create(Vec2 pos);//場所と、タイプ
	void clear();
	void draw();
	void move();
private:
	std::list<EnemyPtr> enemies;
};
