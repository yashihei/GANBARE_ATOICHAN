#pragma once

#include <Siv3D.hpp>
#include <string>
#include <hash_map>

struct EnemyData {
	int hp;
	Color color;
	double rad;
	int score;
	int limit;
};

class EnemyDataFactory
{
public:
	EnemyDataFactory();
	EnemyData create(std::string type);
private:
	std::hash_map<std::string, EnemyData> dataList;
};
