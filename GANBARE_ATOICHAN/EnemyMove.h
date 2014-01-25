#pragma once
#include <Siv3D.hpp>
#include <memory>

class EnemyMove
{
public:
	virtual ~EnemyMove(){};
	virtual void move(Vec2* pos, int cnt) = 0;
};

class EnemyMove1 : public EnemyMove {
	void move(Vec2* pos, int cnt) override;
};

class EnemyMove2 : public EnemyMove {
};

class EnemyMoveFactory
{
public:
	EnemyMoveFactory(){};
	std::shared_ptr<EnemyMove> create(int type);
};


