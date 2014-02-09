#pragma once
#include <Siv3D.hpp>

class GameManager;

class Ship
{
public:
	Ship(GameManager* gm);
	void init();
	void move();
	void draw();
	void destory();
	void moveControl();
	void comeBackControl();

	Vec2 getPos() { return pos; };
	double getRad() { return rad; };
	int getLife() { return life; };
private:
	GameManager* gm;
	double rad;
	Vec2 pos;
	int life;
	int cnt;//ショット間隔用
	bool slowMove;
	bool comeBack;
	int comeBackCnt;
	bool muteki;
	int mutekiCnt;
};
