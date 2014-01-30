#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"
#include "EnemyPattern.h"
#include "GameManager.h"

void Enemy::setParam(GameManager* gm, Vec2 pos, int dir)
{
	this->gm = gm;
	this->pos = pos;
	this->dir = dir;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(color);
	if (subCnt < 3) c.draw(Palette::White);
	c.drawFrame(2.0, 0.0, Palette::White);
}

void Enemy::damage() {
	hp--;
	subCnt = 0;
}

void Enemy::defalutMove() {
	cnt++;
	subCnt++;
	if (hp < 0) enable = false;
}

Enemy1::Enemy1() {
	hp = 10;
	rad = 15.0;
	color = Color{ 255, 0, 0, 200 };
}

void Enemy1::move() {
	const double rad = Atan2(gm->ship->getPos().x - pos.x, gm->ship->getPos().y - pos.y);
	double sp = 6.5;
	const int interval = 10;
	if (cnt % interval == 0 && cnt > 40) gm->bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp }, Color(255, 0, 255, 200), 5.0);

	if (cnt < 40) {
		pos.moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 250) {
		pos.moveBy({ 0.0, -6.0 });
	}
	Enemy::defalutMove();
}

EnemyManager::EnemyManager(GameManager* gm):
gm(gm) {}

void EnemyManager::create(Vec2 pos, int type, int dir)
{
	std::shared_ptr<Enemy> e;
	//TODO: switchÅ®if else(string)
	switch (type) {
	case 0:
		e = std::make_shared<Enemy1>(); break;
	default:
		LOG(L"defalut");
		e = nullptr;
	}
	e->setParam(gm, pos, dir);
	enemies.push_back(e);
}

void EnemyManager::clear() {
	enemies.clear();
}

void EnemyManager::draw() {
	for (auto& enemy : enemies) {
		enemy->draw();
	}
}

void EnemyManager::move() {
	for (auto it = enemies.begin(); it != enemies.end();) {
		(*it)->move();
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0 ||
			(*it)->getPos().y > Window::Height() || (*it)->getPos().y < 0 ||
			!(*it)->isEnable()) {
			it = enemies.erase(it);
			continue;
		}
		it++;
	}
}
