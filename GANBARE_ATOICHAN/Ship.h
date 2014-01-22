#pragma once
#include <Siv3D.hpp>
#include "TypeDef.h"

class Ship
{
public:
	Ship(ShotManager*);
	void move();
	void draw();
private:
	ShotManager* shotManager;
	double rad;
	Vec2 pos;

	int cnt;//“à•”ƒJƒEƒ“ƒ^
public:
	Vec2 getPos() { return pos; };
};
