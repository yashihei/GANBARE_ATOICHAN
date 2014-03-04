#include <Siv3D.hpp>
#include "GameManager.h"

void Main()
{
	const Point targetSize(480, 640);
	//const Point targetSize(1280, 720);
	//const Point targetSize(1920, 1080);

	// �t���X�N���[���\�ȉ𑜓x�ꗗ���擾
	//std::vector<Point> resolutions = Graphics::GetFullScreenSize();
	//for (auto& res : resolutions) {
	//	LOG(Format(res.x, L" ", res.y));
	//}

	//if (std::find(resolutions.begin(), resolutions.end(), targetSize) == resolutions.end()) {
	//	LOG(L"�f�B�X�v���C�T�C�Y�����ĂȂ��[");
	//	return; // targetSize ���܂܂�Ă��Ȃ��ꍇ�I��
	//}
	Window::SetFullscreen(true, targetSize);

	Window::Resize(480, 640);
	Window::SetTitle(L"DANMAKU");

	auto gm = std::make_shared<GameManager>();
	while (System::Update())
	{
		gm->move();
		gm->draw();
	}
}