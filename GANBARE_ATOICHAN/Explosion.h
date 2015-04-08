#pragma once
#include <Siv3D.hpp>
#include <vector>

class GameManager;

class Explosion
{
public:
	Explosion(GameManager* gm, const Vec2& pos, double size);
	void move();
	void draw();
	bool isEnable() const { return enable; };
private:
	GameManager* gm;
	bool enable;
	Vec2 pos;
	int cnt;
	double size;
};
