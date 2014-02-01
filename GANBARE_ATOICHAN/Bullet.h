#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>
#include <functional>
#include "Actor.h"

class BulletMove
{
public:
	BulletMove(){};
	virtual void move(Vec2* pos, Vec2* vel) = 0;
};

class Tokasoku : public BulletMove {
	void move(Vec2* pos, Vec2* vel) override;
};

class Juryoku : public BulletMove {
	void move(Vec2* pos, Vec2* vel) override;
};

class Bullet
{
public:
	Bullet(Vec2 pos, Vec2 vel, Color color, double rad, int moveType);
	void move();
	void draw();
	Vec2 getPos() const { return this->pos; };
	double getRad() const { return this->rad; };
	Vec2 getVel() const { return this->vel; }
private:
	Vec2 pos;
	Vec2 vel;
	double rad;
	Color color;
	int cnt;
	std::shared_ptr<BulletMove> bulletMove;
};

class BulletManager
{
public:
	BulletManager(){};
	void clear();
	void draw();
	void move();
	void create(Vec2 pos, Vec2 vel, Color color, double rad, int moveType);
	const std::list<std::shared_ptr<Bullet>>* getBullets() const { return &bullets; };
private:
	std::list<std::shared_ptr<Bullet>> bullets;
};
