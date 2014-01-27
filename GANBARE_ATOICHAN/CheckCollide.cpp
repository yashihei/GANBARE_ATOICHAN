#include "CheckCollide.h"

#include <Siv3D.hpp>
#include "Enemy.h"
#include "Shot.h"
#include "Ship.h"
#include "Bullet.h"

CheckCollide::CheckCollide(ShotManager* shotManager, BulletManager* bulletManager, Ship* ship, EnemyManager* enemyManager)
{
	shots = shotManager->getShots();
	bullets = bulletManager->getBullets();
	enemies = enemyManager->getEnemies();
	ship = ship;
}

CheckCollide::CheckCollide(std::tuple<ShotManager*, BulletManager*, EnemyManager*, Ship*> args)
{
	shots = std::get<0>(args)->getShots();
	bullets = std::get<1>(args)->getBullets();
	enemies = std::get<2>(args)->getEnemies();
	ship = std::get<3>(args);
}

void CheckCollide::move()
{
	for (auto s = shots->begin(); s != shots->end(); ++s) {
		for (auto e = enemies->begin(); e != enemies->end(); ++e) {
			//if ((*s)->getPos().intersects( Circle((*e)->getPos(), (*e)->getRad()) )) {
			Line line((*s)->getPos(), (*s)->getPos() + (*s)->getVel());
			Circle circle((*e)->getPos(), (*e)->getRad());
			if (Geometry::Intersect(line, circle)) {
				(*e)->damage();
				(*s)->burn();
			}
		}
	}
	//TODO:Ž©‹@‚Ö‚Ì“–‚½‚è”»’è
	for (auto b = bullets->begin(); b != bullets->end(); ++b) {
		Line line((*b)->getPos(), (*b)->getPos() + (*b)->getVel());
		Circle circle(ship->getPos(), ship->getRad());
		if (Geometry::Intersect(line, circle)) {
			ship->destory();
		}
	}
}
