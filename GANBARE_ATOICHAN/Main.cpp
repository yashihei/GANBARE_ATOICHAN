#include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font.draw(L"ようこそ、Siv3D の世界へ！");

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
