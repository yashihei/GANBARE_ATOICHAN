#pragma once
#include <Siv3D.hpp>
#include <memory>

class BulletManager;

class Barrage {
public:
	Barrage(){};
	virtual void move(Vec2 ownerPos, Vec2 targetPos, BulletManager* bulletManager) = 0;
};

class Barrage1 : public Barrage {
	void move(Vec2 ownerPos, Vec2 targetPos, BulletManager* bulletManager) override;
};

class BarrageFactory {
public:
	BarrageFactory(){};
	std::shared_ptr<Barrage> create(int type);
};
