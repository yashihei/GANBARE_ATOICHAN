#pragma once
#include <Siv3D.hpp>
#include <list>
#include <memory>
#include <hash_map>
#include <string>

class Ship;
class BulletManager;
class ShotManager;

/*
 * Enemy.h
 * �G�I�u�W�F�N�g�Ȃ�
 */

class Enemy
{
public:
	Enemy(){};
	void setParam(Ship* ship, BulletManager* bulletManager, Vec2 pos);
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
	BulletManager* bulletManager;
	Ship* ship;
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	int subCnt = 3;//��_���\���p
	int hp;
	bool enable = true;
	int dir = 1;
};

class Enemy1 : public Enemy
{
public:
	Enemy1();
	void move() override;
};

//�˂�����ł���
class Tossin : public Enemy
{
public:
	Tossin();
	void move() override;
private:
	Vec2 vel;
};

//���\�΂�܂�
class Middle : public Enemy
{
public:
	Middle();
	void move() override;
private:
	double kakudo;
};

//�x���e�΂�T��
class Baramaki : public Enemy
{
public:
	Baramaki();
};

class EnemyManager
{
public:
	EnemyManager(Ship* ship, BulletManager* bulletManager);
	void create(Vec2 pos, std::string type);//�ꏊ�ƁA�^�C�v
	void clear();
	void draw();
	void move();
	const std::list<std::shared_ptr<Enemy>>* getEnemies() const { return &enemies; };
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	BulletManager* bulletManager;
	Ship* ship;
};
