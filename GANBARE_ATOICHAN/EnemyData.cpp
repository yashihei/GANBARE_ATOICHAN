#include "EnemyData.h"

EnemyDataFactory::EnemyDataFactory() {
	dataList.insert(std::pair<std::string, EnemyData>("zako", { 10, Palette::Red, 10.0, 100 }));
	//dataList["zako"] = {10, Palette::Red, 10.0, 100};//ƒRƒ“ƒpƒCƒ‰‚ªŽ€‚Ê
}

EnemyData EnemyDataFactory::create(std::string type)
{
	return dataList[type];
}

