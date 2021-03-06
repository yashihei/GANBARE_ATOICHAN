#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>
#include <functional>

class Bullet
{
public:
	Bullet(){};
	void init(Vec2 pos, Vec2 vel, int colorType, int moveType);
	void move();
	void draw();
	void burn();
	Vec2 getPos() const { return this->pos; }
	double getRad() const { return this->rad; }
	Vec2 getVel() const { return this->vel; }
	bool getEnable() const { return this->enable; }
private:
	Vec2 pos;
	Vec2 vel;
	double rad;
	int cnt;
	bool enable=false;
	std::function<void(Vec2* pos, Vec2* vel)> bulletMove;
	TextureRegion texture;
};

class BulletManager
{
public:
	BulletManager();
	void clear();
	void draw();
	void move();
	void create(Vec2 pos, Vec2 vel, int colorType, int moveType);
	const std::list<std::shared_ptr<Bullet>>* getBullets() const { return &bullets; };
private:
	std::list<std::shared_ptr<Bullet>> bullets;
};
