#include "EnemyData.h"

EnemyDataFactory::EnemyDataFactory() {
	dataList.insert(std::pair<std::string, EnemyData>("zako", { 10, Palette::Red, 10.0, 100, 0 }));
	dataList.insert(std::pair<std::string, EnemyData>("zakod", { 10, Palette::Red, 10.0, 100, 40 }));
	dataList.insert(std::pair<std::string, EnemyData>("futu", { 20, Palette::Blue, 20.0, 200, 40 }));
	//dataList["zako"] = {10, Palette::Red, 10.0, 100};//ƒRƒ“ƒpƒCƒ‰‚ªŽ€‚Ê
}

EnemyData EnemyDataFactory::create(std::string type)
{
	return dataList[type];
}

