#pragma once
#include <Siv3D.hpp>
#include <memory>
#include <hash_map>
#include <string>

class EnemyMove
{
public:
	EnemyMove(){};
	virtual ~EnemyMove(){};
	virtual void move(Vec2* pos, int cnt) = 0;
	void turnDir() { dir *= -1; };
protected:
	int cnt;
	int dir=1;
};

class EnemyMove1 : public EnemyMove {
	void move(Vec2* pos, int cnt) override;
};

class EnemyMove2 : public EnemyMove {
	void move(Vec2* pos, int cnt) override;
};

class EnemyMoveFactory
{
public:
	EnemyMoveFactory();
	std::shared_ptr<EnemyMove> create(std::string type);
private:
	std::hash_map<std::string, std::shared_ptr<EnemyMove>> moveList;
};
