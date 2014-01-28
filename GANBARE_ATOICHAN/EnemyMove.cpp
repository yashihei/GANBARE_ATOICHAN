#include "EnemyMove.h"

//MovePtn:NORMAL
//�܂������i��ł�����Ƃ�����������މ����q
void EnemyMove1::move(Vec2* pos, int cnt) {
	if (cnt < 40) {
		pos->moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 200) {
		pos->moveBy({ 0.0, -6.0 });
	}
}

void EnemyMove2::move(Vec2* pos, int cnt) {
	pos->moveBy({ 2.0 * dir, 0.0 });
}

EnemyMoveFactory::EnemyMoveFactory() {
	moveList["Normal"] = std::make_shared<EnemyMove1>();
	moveList["slowL"] = std::make_shared<EnemyMove2>();
	auto t = std::make_shared<EnemyMove2>();
	t->turnDir();
	moveList["slowR"] = t;
}

std::shared_ptr<EnemyMove> EnemyMoveFactory::create(std::string type)
{
	if (moveList[type].get() == nullptr);
	return moveList[type];
}

