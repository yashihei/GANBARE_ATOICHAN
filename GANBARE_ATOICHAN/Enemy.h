#pragma once
#include <Siv3D.hpp>
#include <list>

class BulletManager;
class Ship;

class Enemy
{
public:
	//Enemy(){};
	Enemy(BulletManager* bulletManager, Ship* ship);
	virtual void move() = 0;
	void draw();
protected:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt;
	BulletManager* bulletManager;
	Ship* ship;
public:
	void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
};

class Enemy1 : public Enemy {
public:
	Enemy1(BulletManager*, Ship*);
	void move() override;
};

class EnemyManager
{
public:
	EnemyManager(BulletManager* bulletManager, Ship* ship);
	void create(Vec2 pos, int type);//場所と、タイプ
	void clear();
	void draw();
	void move();
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	BulletManager* bulletManager;
	Ship* ship;
};
