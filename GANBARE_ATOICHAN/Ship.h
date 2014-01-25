#pragma once
#include <Siv3D.hpp>

class ShotManager;

class Ship
{
public:
	Ship(ShotManager*);
	void move();
	void draw();
	void destory();

	Vec2 getPos() { return pos; };
	double getRad() { return rad; };
private:
	ShotManager* shotManager;
	double rad;
	Vec2 pos;

	int cnt;//�����J�E���^
};
