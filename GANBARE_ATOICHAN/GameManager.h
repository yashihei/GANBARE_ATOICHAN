#pragma once
#include <memory>

class Ship;
class ShotManager;

class GameManager
{
public:
	GameManager();
	void move();
	void draw();
private:
	std::shared_ptr<Ship> ship;
	std::shared_ptr<ShotManager> shotManager;
};
