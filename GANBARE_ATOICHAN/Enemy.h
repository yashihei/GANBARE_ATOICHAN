#pragma once
#include <Siv3D.hpp>
#include <list>

class Ship;
class BulletManager;
class ShotManager;

/*
 * Enemy.h
 * �G�I�u�W�F�N�g�Ȃ�
 * �G�̎�ނ͌p���ł͂Ȃ��A�ڏ��ɂ���ĕ\�������
 * �Ȃ�Ă������ȁA����͉R��
 */

class Enemy
{
public:
	Enemy(){};
	void init(Vec2 pos, Ship* ship, BulletManager* bulletManager);
	virtual void move() = 0;
	virtual void draw() = 0;
protected:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	Ship* ship;
	BulletManager* bulletManager;
public:
	//void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() { return this->pos; };
	double getRad() { return this->rad; };
};

class Enemy1 : public Enemy
{
public:
	Enemy1();
	void move() override;
	void draw() override;
};

class EnemyManager
{
public:
	EnemyManager(Ship* ship, BulletManager* bulletManager);
	void create(Vec2 pos, int type);//�ꏊ�ƁA�^�C�v
	void clear();
	void draw();
	void move();
	std::list<std::shared_ptr<Enemy>>* getEnemies() { return &enemies; };
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	Ship* ship;
	BulletManager* bulletManager;
	ShotManager* shotManager;
};
