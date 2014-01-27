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
	pos->moveBy({ 2.0 * dir, 0.0 });
}

EnemyMoveFactory::EnemyMoveFactory() {
	moveList["Normal"] = std::make_shared<EnemyMove1>();
	moveList["slowR"] = std::make_shared<EnemyMove2>();
	auto t = std::make_shared<EnemyMove2>();
	t->turnDir();
	moveList["slowL"] = t;
}

std::shared_ptr<EnemyMove> EnemyMoveFactory::create(std::string type)
{
	if (moveList[type].get() == nullptr);
	return moveList[type];
}

