#pragma once
#include <Siv3D.hpp>
#include <memory>

class ShotManager;

class Ship
{
public:
	//using Circle::draw;
	Ship(std::shared_ptr<ShotManager> shotManager);
	void move();
	void draw();

	Circle core;//hitpoint and movecontrol
private:
	std::shared_ptr<ShotManager> shotManager;
	int cnt;
public:
	//Circle getCore() { return core; };
};
