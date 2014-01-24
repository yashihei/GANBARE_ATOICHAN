#pragma once
#include <Siv3D.hpp>
#include <list>

class Shot
{
public:
	Shot();
	void move();
	void draw();
private:
	double speed;
	double rad;//“–‚½‚è”»’è‚Ì”¼Œa
	Vec2 vel;
	Vec2 pos;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
	Vec2 getVel() { return this->vel; };
};

class ShotManager
{
public:
	ShotManager();
	void create(Vec2 pos);
	void clear();
	void move();
	void draw();
	const std::list<std::shared_ptr<Shot>>* getShots() { return &shots; };
private:
	std::list<std::shared_ptr<Shot>> shots;
};
