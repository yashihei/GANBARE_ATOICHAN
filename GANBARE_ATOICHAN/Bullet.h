#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>
#include "Actor.h"

class Bullet
{
public:
	Bullet(Vec2 pos, Vec2 vel);
	void move();
	void draw();
	Vec2 getPos() { return this->pos; };
private:
	Vec2 pos;
	Vec2 vel;
	double rad;
	Color color;
	int cnt;
};

class BulletManager
{
public:
	BulletManager(){};
	void clear();
	void draw();
	void move();
	void create(Vec2 pos, Vec2 vel);
private:
	std::list<std::shared_ptr<Bullet>> bullets;
};