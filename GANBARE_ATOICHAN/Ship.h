#pragma once
#include <Siv3D.hpp>
#include <memory>

class ShotManager;

class Ship
{
public:
	Ship(std::shared_ptr<ShotManager> shotManager);
	void move();
	void draw();
private:
	std::shared_ptr<ShotManager> shotManager;
	double rad;
	Vec2 pos;

	int cnt;//“à•”ƒJƒEƒ“ƒ^
public:
	Vec2 getPos() { return pos; };
};
