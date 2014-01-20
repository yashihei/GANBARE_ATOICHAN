#pragma once
#include <Siv3D.hpp>
#include <list>
#include "TypeDef.h"

class Enemy
{
public:
	Enemy();
	void move();
	void draw();
private:
	double rad;
	Vec2 pos;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
};

class EnemyManager
{
public:
	EnemyManager();
	void create(Vec2 pos);
	void clear();
	void draw();
	void move();
private:
	std::list<EnemyPtr> enemies;
};
