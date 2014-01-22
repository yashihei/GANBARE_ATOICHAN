#include "Enemy.h"

#include "Bullet.h"
#include "Ship.h"

Enemy::Enemy(BulletManager* bulletManager, Ship* ship) :
bulletManager(bulletManager), ship(ship)
{
	rad = 15.0;
	cnt = 0;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(color);
	c.drawFrame(2.0, 0.0, Palette::White);
}

Enemy1::Enemy1(BulletManager* bm, Ship* ship) : Enemy(bm, ship) {
	rad = 20;
	color = Color(100, 100, 100, 127);
}

void Enemy1::move() {
	if (cnt < 60) {
		pos.moveBy({ -3.0, 0.0 });
	} else if (cnt > 180) {
		pos.moveBy({ 6.0, 0.0 });
	}
	if (cnt > 60 && cnt % 10 == 0 && cnt < 180) {
		const double rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
		const double sp = 10.0;
		bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp });
	}
	cnt++;
}

EnemyManager::EnemyManager(BulletManager* bulletManager, Ship* ship) :
bulletManager(bulletManager), ship(ship)
{
}

void EnemyManager::create(Vec2 pos, int type)
{
	//TODO: åpè≥ÇÊÇËàŸèÛÇ≈
	std::shared_ptr<Enemy> e;
	switch (type) {
	case 1:
		e = std::make_shared<Enemy1>(bulletManager, ship);
		break;
	}
	e->setPos(pos);
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
		//ébíËÅAÇÕÇ›èoÇ∑ÇÃÇ…è≠Çµó]óTéùÇΩÇπ
		if ((*it)->getPos().x > Window::Width() || (*it)->getPos().x < 0) {
			it = enemies.erase(it);
			//LOG(L"éÄÇÒÇæ");
			continue;
		}
		it++;
	}
	if (Random(0, 50) == 0) create({ Window::Width(), Random(0, Window::Height()) }, 1);
}
