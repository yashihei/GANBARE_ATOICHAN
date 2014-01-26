#include "EnemyMove.h"

//MovePtn:NORMAL
//‚Ü‚Á‚·‚®i‚ñ‚Å‚¿‚å‚Á‚Æ‚µ‚½‚çˆø‚Á‚Ş‰Âˆ¤‚¢q
void EnemyMove1::move(Vec2* pos, int cnt) {
	if (cnt < 40) {
		pos->moveBy({ 0.0, 3.0 });
	}
	else if (cnt > 180) {
		pos->moveBy({ 0.0, -6.0 });
	}
}

void EnemyMove2::move(Vec2* pos, int cnt) {
	pos->moveBy({ 2.0, 0.0 });
}

std::shared_ptr<EnemyMove> EnemyMoveFactory::create(int type)
{
	switch (type) {
	case 0:
		return std::make_shared<EnemyMove1>(); break;
	case 1:
		return std::make_shared<EnemyMove2>(); break;
	default:
		LOG(L"defalut");
		return nullptr;
	}
}

