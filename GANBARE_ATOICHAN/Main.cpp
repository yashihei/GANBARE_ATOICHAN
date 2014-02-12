#include <Siv3D.hpp>
#include "GameManager.h"

void Main()
{
	const Point targetSize(480, 640);
	//const Point targetSize(1280, 720);
	//const Point targetSize(1920, 1080);

	// フルスクリーン可能な解像度一覧を取得
	std::vector<Point> resolutions = Graphics::GetFullScreenSize();

	//if (std::find(resolutions.begin(), resolutions.end(), targetSize) == resolutions.end()) {
	//	LOG(L"ディスプレイサイズあってないー");
	//	return; // targetSize が含まれていない場合終了
	//}
	//Window::SetFullscreen(true, targetSize);

	Window::Resize(450, 600);
	Graphics::Set2DBlendState(BlendState::Additive());

	auto gm = std::make_shared<GameManager>();
	while (System::Update())
	{
		gm->move();
		gm->draw();
	}
}