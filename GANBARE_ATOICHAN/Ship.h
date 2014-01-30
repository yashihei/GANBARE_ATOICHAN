#pragma once
#include <Siv3D.hpp>

class ShotManager;
class BulletManager;

class Ship
{
public:
	Ship(ShotManager* shotManager, BulletManager* bulletManager);
	void move();
	void draw();
	void destory();

	Vec2 getPos() { return pos; };
	double getRad() { return rad; };
private:
	ShotManager* shotManager;
	BulletManager* bulletManager;
	double rad;
	Vec2 pos;
	int life;
	bool slowMove;

	int cnt;//�V���b�g�Ԋu�p
};
