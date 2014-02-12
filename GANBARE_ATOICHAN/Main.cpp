#include <Siv3D.hpp>
#include "GameManager.h"

void Main()
{
	const Point targetSize(480, 640);
	//const Point targetSize(1280, 720);
	//const Point targetSize(1920, 1080);

	// �t���X�N���[���\�ȉ𑜓x�ꗗ���擾
	std::vector<Point> resolutions = Graphics::GetFullScreenSize();

	//if (std::find(resolutions.begin(), resolutions.end(), targetSize) == resolutions.end()) {
	//	LOG(L"�f�B�X�v���C�T�C�Y�����ĂȂ��[");
	//	return; // targetSize ���܂܂�Ă��Ȃ��ꍇ�I��
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