#pragma once
#include <Siv3D.hpp>

class ShotManager;
class BulletManager;

class Ship
{
public:
	Ship(ShotManager* shotManager, BulletManager* bulletManager);
	void start();
	void move();
	void draw();
	void destory();
	void moveControl();
	void comeBackControl();

	Vec2 getPos() { return pos; };
	double getRad() { return rad; };
private:
	ShotManager* shotManager;
	BulletManager* bulletManager;
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
