#pragma once
#include <Siv3D.hpp>
#include <list>
#include "TypeDef.h"

class Shot
{
public:
	Shot();
	void move();
	void draw();
private:
	double speed;
	double rad;//“–‚½‚è”»’è‚Ì”¼Œa
	Vec2 pos;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return pos; };
};

class ShotManager
{
public:
	ShotManager();
	void create(const Vec2 pos);
	void clear();
	void move();
	void draw();
private:
	std::list<ShotPtr> shots;
	void autoRemove();
};
