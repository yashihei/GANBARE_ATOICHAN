#include "Explosion.h"

Vec2 randomVector(double maxLength)
{
	const double rad = Random(0.0, TwoPi);
	const double length = Random(0.0, maxLength);
	return Circular(length, rad);
}

Particle::Particle(Vec2 pos, Vec2 vel):
pos(pos), vel(vel)
{
	cnt = 0;
}

void Particle::move() {
	pos.moveBy(vel);
	cnt++;
}

void Particle::draw() {
	const double size = 8.0;
	unsigned int alpha = 200 - cnt * 2;
	Circle(pos, size).draw({ 255, 255, 255 , alpha});
}

Explosion::Explosion(const Vec2& pos, int num):
pos(pos)
{
	for (int i = 0; i < num; i++) {
		particles.emplace_back(pos, Vec2(randomVector(3.0)));
	}
	cnt = 0;
	enable = true;
}

void Explosion::move()
{
	for (auto& particle : particles) {
		particle.move();
	}
	cnt++;
	if (cnt > 100) enable = false;
}

void Explosion::draw()
{
	for (auto& particle : particles) {
		particle.draw();
	}
}
