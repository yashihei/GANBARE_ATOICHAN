#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>

class Ship;

class Shot
{
public:
	Shot();
	void move();
	void draw();
private:
	int speed;
	int rad;//“–‚½‚è”»’è‚Ì”¼Œa
	Vec2 pos;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return pos; };
};

class ShotManager
{
public:
	ShotManager();
	void create(Ship* ship);
	void clear();
	void move();
	void draw();
private:
	std::list<std::shared_ptr<Shot>> shots;
	void autoRemove();
};
