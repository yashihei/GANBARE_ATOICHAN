#pragma once
#include <Siv3D.hpp>
#include <vector>

class Explosion
{
public:
	Explosion(const Vec2& pos, double size);
	void move();
	void draw();
	bool isEnable() const { return enable; };
private:
	bool enable;
	Vec2 pos;
	int cnt;
	double size;
};
