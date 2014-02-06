#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>
#include <hash_map>
#include <string>

class Ship;
class BulletManager;
class ShotManager;
class GameManager;

/*
 * Enemy.h
 * 敵オブジェクトなの
 */

class Enemy
{
public:
	Enemy(){};
	void setParam(GameManager* gm, Vec2 pos);
	virtual void move() = 0;
	void draw();
	void defalutMove();
	void damage();
	void turnDir();
	//getter
	Vec2 getPos() const { return this->pos; };
	double getRad() const { return this->rad; };
	bool isEnable() const { return this->enable; };
protected:
	GameManager* gm;
	BulletManager* bulletManager;
	Ship* ship;
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	int subCnt = 3;//非ダメ表示用
	int hp;
	int hpMax;
	bool enable = true;
	int dir = 1;
	int score;
	bool isBoss = false;//hpバー表示?
};

class Enemy1 : public Enemy
{
public:
	Enemy1();
	void move() override;
};

//突っ込んでくる
class Tossin : public Enemy
{
public:
	Tossin();
	void move() override;
private:
	Vec2 vel;
	//double rad;
};

//結構ばらまく
class Middle : public Enemy
{
public:
	Middle();
	void move() override;
private:
	double kakudo;
};

//輝針城５面の雑魚風
class Baramaki : public Enemy
{
public:
	Baramaki();
	void move() override;
};

class Chubosu : public Enemy
{
public:
	Chubosu();
	void move() override;
private:
	double kakudo;
};

class EnemyManager
{
public:
	EnemyManager(GameManager* gm);
	void create(Vec2 pos, std::string type);//場所と、タイプ
	void clear();
	void draw();
	void move();
	const std::list<std::shared_ptr<Enemy>>* getEnemies() const { return &enemies; };
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	GameManager* gm;
};
