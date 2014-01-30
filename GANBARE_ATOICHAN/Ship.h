#pragma once
#include <Siv3D.hpp>

class GameManager;

class Ship
{
public:
	Ship(GameManager* gm);
	void move();
	void draw();
	void destory();

	Vec2 getPos() { return pos; };
	double getRad() { return rad; };
private:
	GameManager* gm;
	double rad;
	Vec2 pos;
	int life;
	bool slowMove;

	int cnt;//ショット間隔用
};
