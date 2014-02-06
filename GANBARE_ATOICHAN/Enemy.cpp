#include "Enemy.h"

#include "Ship.h"
#include "Bullet.h"
#include "Shot.h"
#include "GameManager.h"

void Enemy::setParam(GameManager* gm, Vec2 pos)
{
	this->gm = gm;
	this->ship = gm->getShip();
	this->bulletManager = gm->getBullets();
	this->pos = pos;
}

void Enemy::draw() {
	Circle c(pos, rad);
	c.draw(color);
	if (subCnt < 3) c.draw(Palette::White);
	c.drawFrame(2.0, 0.0, Palette::White);
	if (isBoss) {
		double t = (double)hp / (double)hpMax;
		Rect hpBar({ 25, 50 }, { 400 * t, 15 });
		//hpBar.draw({ 255, 255, 255, 200 });
		hpBar.draw(HSV(60 * t, 1.0, 1.0));
		hpBar.drawFrame(0.0, 1.5, Palette::White);
	}
}

void Enemy::damage() {
	hp--;
	subCnt = 0;
}

void Enemy::defalutMove() {
	cnt++;
	subCnt++;
	if (hp < 0) {
		enable = false;
		gm->addScore(score);
	}
}

void Enemy::turnDir() {
	dir *= -1;
}

Enemy1::Enemy1() {
	hp = 10;
	rad = 15.0;
	color = Color{ 255, 0, 0, 200 };
}

void Enemy1::move() {
	const double rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	double sp = 6.5;
	const int interval = 10;
	if (cnt % interval == 0 && cnt > 40) bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp }, Color(255, 0, 255, 200), 5.0, 0);

	if (cnt < 40) {
		pos.moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 250) {
		pos.moveBy({ 0.0, -6.0 });
	}
	Enemy::defalutMove();
}

Tossin::Tossin() {
	hp = 5;
	rad = 15.0;
	color = Color{ 255, 255, 255, 200 };
	score = 3939;
}

void Tossin::move() {
	//TODO:ˆê’è‚ÌU‚ê•‚É
	double rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	rad += Random(-0.2, 0.2);
	double sp = 7.0;
	const int interval = 5;
	if (cnt % interval == 0) bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp }, { 0, 255, 255, 200 }, 5.0, 0);

	sp = 5.0;
	rad = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	if (pos.y + 100 < ship->getPos().y) vel = { Sin(rad)*sp, Cos(rad)*sp };
	pos.moveBy(vel);

	Enemy::defalutMove();
}

Middle::Middle() {
	hp = hpMax = 100;
	rad = 25.0;
	color = Color{ 0, 0, 255, 200 };
	kakudo = 0.0;
	score = 50000;
}

void Middle::move() {
	//‚®‚é‚®‚é‚Ü‚í‚·’e–‹
	const double PI2 = 6.28;
	double radian = Radians(kakudo);
	double sp = 5.0;
	const int interval = 3;
	const int sep = 10;
	if (cnt > 30 && cnt % interval == 0) {
		kakudo += 15.0;
		for (int i = 0; i < sep; i++) {
			bulletManager->create(pos, { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, {255, 0, 200, 200}, 5.0, 0);
		}
	}

	if (cnt < 30) {
		pos.moveBy({ 0.0, 3.0 });
	} else if (cnt > 300) {
		pos.moveBy({ 0.0, -6.0 });
	}
	Enemy::defalutMove();
}

Baramaki::Baramaki() {
	hp = 10;
	rad = 15.0;
	color = Color{ 255, 255, 255, 200 };
	score = 5000;
}

void Baramaki::move() {
	const int interval = 10;
	//TODO:Šp“x­‚È‚­
	if (cnt % interval == 0) {
		bulletManager->create(pos, { Random(-1.5, 1.5), -2.0 }, { 0, 255, 255, 200 }, 5.0, 1);
	}

	pos.moveBy({ 1.0 * dir, 0.0 });
	Enemy::defalutMove();
}

Chubosu::Chubosu() {
	hp = hpMax = 500;
	rad = 30.0;
	color = Color{ 255, 255, 0, 200 };
	isBoss = true;
	score = 100000;
	kakudo = 0;
}

void Chubosu::move() {
	const double PI2 = 6.28;
	double radian = Radians(kakudo);
	double sp = 5.0;
	const int interval = 8;
	const int sep = 10;
	if (cnt > 30 && cnt % interval == 0) {
		kakudo += 5.0;
		for (int i = 0; i < sep; i++) {
			bulletManager->create(pos + Vec2(20.0, 0.0), { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, {255, 0, 200, 200}, 5.0, 0);
			bulletManager->create(pos + Vec2(-20.0, 0.0), { Sin(-radian + PI2 / sep * i)*sp, Cos(-radian + PI2 / sep * i)*sp }, {0, 255, 255, 200}, 5.0, 0);
		}
	}

	if (cnt < 30) {
		pos.moveBy({ 0.0, 3.0 });
	} else if (cnt > 750) {
		pos.moveBy({ 0.0, -6.0 });
	}

	Enemy::defalutMove();
}

EnemyManager::EnemyManager(GameManager* gm):
gm(gm)
{
}

void EnemyManager::create(Vec2 pos, std::string type)
{
	std::shared_ptr<Enemy> e;
	if (type == "zako") {
		e = std::make_shared<Enemy1>();
	} else if (type == "tossin") {
		e = std::make_shared<Tossin>();
	} else if (type == "middle") {
		e = std::make_shared<Middle>();
	} else if (type == "baramakiL") {
		e = std::make_shared<Baramaki>();
	} else if (type == "baramakiR") {
		e = std::make_shared<Baramaki>();
		e->turnDir();
	} else if (type == "chubosu") {
		e = std::make_shared<Chubosu>();
	} else {
		LOG(L"name miss");
		return;
	}
	e->setParam(gm, pos);
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
