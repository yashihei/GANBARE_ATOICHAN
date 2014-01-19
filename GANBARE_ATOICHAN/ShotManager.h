#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>

class Ship;

class Shot
{
public:
	Shot();
	Circle core;
private:
};

class ShotManager
{
public:
	ShotManager();
	void createShot(Ship* ship);
	void clear();
	void move();
	void draw();
private:
	std::list<std::shared_ptr<Shot>> shots;
	void autoRemove();
};
