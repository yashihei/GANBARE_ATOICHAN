#include <Siv3D.hpp>
#include "GameManager.h"

void Main()
{
	auto gm = std::make_shared<GameManager>();
	while (System::Update())
	{
		gm->move();
		gm->draw();
	}
}