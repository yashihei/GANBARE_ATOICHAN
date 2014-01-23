#pragma once
#include <Siv3D.hpp>

class BulletManager;

class Barrage {
public:
	Barrage(){};
	virtual void move(Vec2 ownerPos, Vec2 targetPos) = 0;
private:
	BulletManager* bulletManager;
};

class Barrage1 : Barrage {
	void move(Vec2 ownerPos, Vec2 targetPos) override;
};

class BarrageFactory {
	BarrageFactory(){};
	void create();
};
