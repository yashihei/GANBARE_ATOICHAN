#include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font.draw(L"�悤�����ASiv3D �̐��E�ցI");

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
