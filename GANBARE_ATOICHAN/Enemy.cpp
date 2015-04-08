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
	texure.drawAt(pos);
	if (subCnt < 3) texure.drawAt(pos, { 255, 0, 0 });
}

void Enemy::damage() {
	hp--;
	subCnt = 0;
}

void Enemy::defalutMove() {
	cnt++;
	subCnt++;
	//Ž€‚ñ‚¾Œã“G‚ÉŠÖ‚·‚éˆ—‚ðŒp‘±‚³‚¹‚é‚Æ‚«‚±‚ê‚¾‚Æ•s•Ö
	if (hp < 0) {
		enable = false;
		gm->addScore(score);
		double t;
		if (maxHp <= 15) t = 0.35;
		else if (maxHp <= 50) t = 0.5;
		else if (maxHp <= 100) t = 0.75;
		else t = 1.0;
		gm->createExplosion(pos, t);
		SoundAsset(L"burn").playMulti(0.3);
	}
	if (pos.x > Window::Height() || pos.x < 0 || pos.y > Window::Height() || pos.y < 0) {
		enable = false;
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
	if (cnt % interval == 0 && cnt > 40) bulletManager->create(pos, { Sin(rad)*sp, Cos(rad)*sp }, 0, 0);

	if (cnt < 40) {
		pos.moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 250) {
		pos.moveBy({ 0.0, -6.0 });
	}
	Enemy::defalutMove();
}

Tossin::Tossin() {
	hp = maxHp = 5;
	rad = 15.0;
	color = Color{ 255, 255, 255, 200 };
	score = 3939;
	texure = TextureAsset(L"enemy")(0, 0, 64, 64);
}

void Tossin::move() {
	//TODO:ˆê’è‚ÌU‚ê•‚É
	double radian = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	radian += Random(-0.2, 0.2);
	double sp = 7.0;
	int interval = 5;
	double moveSp = 5.0;
	//easymode
	if (gm->isEasy()) {
		sp = 5.0;
		interval = 10;
		moveSp = 3.0;
	}
	if (cnt % interval == 0) bulletManager->create(pos, { Sin(radian)*sp, Cos(radian)*sp }, 1, 0);
	radian = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	if (pos.y + 100 < ship->getPos().y) vel = { Sin(radian)*moveSp, Cos(radian)*moveSp };
	pos.moveBy(vel);

	Enemy::defalutMove();
}

Middle::Middle() {
	hp = maxHp = 100;
	rad = 25.0;
	color = Color{ 0, 0, 255, 200 };
	kakudo = 0.0;
	score = 30000;
	texure = TextureAsset(L"enemy")(64, 0, 64, 64).scale(1.3);
}

void Middle::move() {
	//‚®‚é‚®‚é‚Ü‚í‚·’e–‹
	const double PI2 = 6.28;
	double radian = Radians(kakudo);
	double sp = 5.0;
	int interval = 3;
	int sep = 10;

	if (gm->isEasy()) {
		sp = 3.0;
		interval = 5;
	}

	if (cnt > 30 && cnt % interval == 0) {
		kakudo += 15.0;
		for (int i = 0; i < sep; i++) {
			bulletManager->create(pos, { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, 0, 0);
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
	hp = maxHp = 10;
	rad = 15.0;
	color = Color{ 255, 255, 255, 200 };
	score = 5000;
	texure = TextureAsset(L"enemy")(0, 0, 64, 64);
}

void Baramaki::move() {
	int interval = 15;

	if (gm->isEasy()) {
		interval = 30;
	}

	//TODO:Šp“x­‚È‚­
	if (cnt % interval == 0) {
		bulletManager->create(pos, { Random(-1.5, 1.5), -2.0 }, 1, 1);
	}

	pos.moveBy({ 1.0 * dir, 0.0 });
	Enemy::defalutMove();
}

Chubosu::Chubosu() {
	hp = maxHp = 1000;
	rad = 30.0;
	color = Color{ 255, 255, 0, 200 };
	isBoss = true;
	score = 100000;
	shotCnt = 0;
	kakudo = 0;
	texure = TextureAsset(L"enemy")(128, 0, 64, 64).scale(1.5);
}

void Chubosu::move() {
	const double PI2 = 6.28;
	double radian = Radians(kakudo);
	double sp = 3.0;
	int sep = 10;
	int interval = (int)(8 * ((double)hp/maxHp));//HPŽc‚è’l‚É‚æ‚è”­‹¶
	if (interval <= 1) interval = 1;

	if (gm->isEasy()) {
		//sep = 5;
		sp = 2.0;
		interval = (int)(15 * ((double)hp / maxHp));//HPŽc‚è’l‚É‚æ‚è”­‹¶
		if (interval <= 3) interval = 3;
	}

	if (cnt > 30 && cnt % interval == 0) {
		kakudo += 5.0;
		for (int i = 0; i < sep; i++) {
			bulletManager->create(pos + Vec2(20.0, 0.0), { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, 0, 0);
			bulletManager->create(pos + Vec2(-20.0, 0.0), { Sin(-radian + PI2 / sep * i)*sp, Cos(-radian + PI2 / sep * i)*sp }, 1, 0);
		}
	}
	/*
	if (cnt > 30 && cnt % interval == 0) {
		if (shotCnt % 5 == 0) kakudo += 10;
		if (shotCnt % 10 < 5) {
			kakudo += 1;
			for (int i = 0; i < sep; i++) {
				bulletManager->create(pos, { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, 0, 0);
			}
		} else {
			kakudo -= 1;
			for (int i = 0; i < sep; i++) {
				bulletManager->create(pos, { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, 1, 0);
			}
		}
		shotCnt++;
	}
	*/

	if (cnt < 30) {
		pos.moveBy({ 0.0, 3.0 });
	}
	if (hp < 0) gm->startClear();//“|‚µ‚½‚çƒQ[ƒ€ƒNƒŠƒA

	Enemy::defalutMove();
}

Nerai::Nerai() {
	hp = maxHp = 30;
	rad = 20.0;
	color = Color{ 255, 0, 0, 200 };
	score = 10000;
	texure = TextureAsset(L"enemy")(64, 0, 64, 64);
}

void Nerai::move() {
	const double radian = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	double sp = 2.0 + (cnt - 30) / 10;
	if (sp > 10.0) sp = 10.0;
	int interval = 5;

	if (gm->isEasy()) {
		sp = 2.0 + (cnt - 30) / 20;
		if (sp > 5.0) sp = 5.0;
		interval = 7;
	}

	if (cnt % interval == 0 &&
		cnt > 30 && cnt < 150)
		bulletManager->create(pos, { Sin(radian)*sp, Cos(radian)*sp }, 0, 0);

	if (cnt < 30) {
		pos.moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 200) {
		pos.moveBy({ 0.0, -6.0 });
	}
	Enemy::defalutMove();
}

ThreeWay::ThreeWay() {
	hp = maxHp = 10;
	rad = 15.0;
	color = Color{ 255, 255, 255, 200 };
	score = 10000;
	texure = TextureAsset(L"enemy")(0, 0, 64, 64);
}

void ThreeWay::move() {
	const double PI = 3.14;
	const double radian = Atan2(ship->getPos().x - pos.x, ship->getPos().y - pos.y);
	double sp = 6.0;
	int interval = 5;

	if (gm->isEasy()) {
		sp = 5.0;
	}

	if (cnt % interval == 0 &&
		cnt % 50 < 25) {
		for (int i = -1; i < 2; i++) {
			bulletManager->create(pos, { Sin(radian + (PI/3) / 3 * i)*sp, Cos(radian + (PI/3) / 3 * i)*sp }, 0, 0);
		}
	}

	pos.moveBy({ 2.0 * dir, 0.0 });
	Enemy::defalutMove();
}

Galaxy::Galaxy() {
	hp = maxHp = 30;
	rad = 20.0;
	color = Color{ 255, 0, 0, 200 };
	kakudo = 0;
	score = 20000;
	texure = TextureAsset(L"enemy")(64, 0, 64, 64);
}

void Galaxy::move() {
	const double PI2 = 6.28;
	double radian = Radians(kakudo);
	double sp = 4.0;
	int interval = 1;
	int sep = 5;

	if (gm->isEasy()) {
		interval = 4;
		sp = 2.0;
	}

	if (cnt > 30 && cnt % interval == 0) {
		if ((cnt - 30) % 100 < 50) kakudo += 10;
		else kakudo -= 10;
		for (int i = 0; i < sep; i++) {
			bulletManager->create(pos, { Sin(radian + PI2 / sep * i)*sp, Cos(radian + PI2 / sep * i)*sp }, 1, 0);
		}
	}

	if (cnt < 30) {
		pos.moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 250) {
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
	} else if (type == "nerai") {
		e = std::make_shared<Nerai>();
	} else if (type == "threewayL") {
		e = std::make_shared<ThreeWay>();
	} else if (type == "threewayR") {
		e = std::make_shared<ThreeWay>();
		e->turnDir();
	} else if (type == "galaxy") {
		e = std::make_shared<Galaxy>();
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
	for (auto& enemy : enemies) {
		enemy->move();
	}
	Erase_if(enemies, [](std::shared_ptr<Enemy> enemy) { return !enemy->isEnable(); });
}
