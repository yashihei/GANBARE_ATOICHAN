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
	virtual void move();
	virtual void draw() = 0;
	virtual void damage();
protected:
	Vec2 pos;
	//Vec2 vel;
	double rad;
	Color color;
	int cnt = 0;
	int subCnt = 3;//��_���\���p
	int hp;
	bool enable = true;
	Ship* ship;
	BulletManager* bulletManager;
public:
	//void setPos(Vec2 pos) { this->pos = pos; };
	Vec2 getPos() const { return this->pos; };
	double getRad() const { return this->rad; };
	bool isEnable() const { return this->enable; };
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
	const std::list<std::shared_ptr<Enemy>>* getEnemies() const { return &enemies; };
private:
	std::list<std::shared_ptr<Enemy>> enemies;
	Ship* ship;
	BulletManager* bulletManager;
	ShotManager* shotManager;
};
