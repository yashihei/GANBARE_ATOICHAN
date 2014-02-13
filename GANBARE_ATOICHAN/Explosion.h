#pragma once
#include <Siv3D.hpp>
#include <vector>

//éQçl:
//http://qiita.com/hamukun8686/items/ff9a06dbb242c36c1e85

class Particle {
public:
	Particle(Vec2 pos, Vec2 vel);
	void move();
	void draw();
private:
	Vec2 pos;
	Vec2 vel;
	Color color;
	Texture texure;
	int cnt;
};

class Explosion
{
public:
	Explosion(const Vec2& pos, int num);
	void move();
	void draw();
	bool isEnable() const { return enable; };
private:
	std::vector<Particle> particles;
	bool enable;
	Vec2 pos;
	int cnt;
};
