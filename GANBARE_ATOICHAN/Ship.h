#pragma once
#include <Siv3D.hpp>
#include "TypeDef.h"

class Ship
{
public:
	Ship(ShotManagerPtr shotManager);
	void move();
	void draw();
private:
	ShotManagerPtr shotManager;
	double rad;
	Vec2 pos;

	int cnt;//“à•”ƒJƒEƒ“ƒ^
public:
	Vec2 getPos() { return pos; };
};
