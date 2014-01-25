#include "EnemyMove.h"

//MovePtn:NORMAL
//‚Ü‚Á‚·‚®i‚ñ‚Å‚¿‚å‚Á‚Æ‚µ‚½‚çˆø‚Á‚Ş‰Âˆ¤‚¢q
void EnemyMove1::move(Vec2* pos, int cnt) {
	if (cnt < 60) {
		pos->moveBy({ -3.0, 0.0 });
	} else if (cnt > 180) {
		pos->moveBy({ 6.0, 0.0 });
	}
}

std::shared_ptr<EnemyMove> EnemyMoveFactory::create(int type)
{
	switch (type) {
	case 0:
		return std::make_shared<EnemyMove1>();
		break;
	default:
		return nullptr;
	}
}

