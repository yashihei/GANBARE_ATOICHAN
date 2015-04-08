#include "Bullet.h"

namespace EnemyMove {
	void tokasoku(Vec2* pos, Vec2* vel) {
		pos->moveBy(*vel);
	}

	void juryoku(Vec2* pos, Vec2* vel) {
		const double G = 0.025;
		*vel += {0, G};
		pos->moveBy(*vel);
	}
}

void Bullet::init(Vec2 pos, Vec2 vel, int colorType, int moveType) {
	this->pos = pos;
	this->vel = vel;
	if (colorType == 0) {
		texture = TextureAsset(L"bullet")(0, 0, 16, 16);
	} else {
		texture = TextureAsset(L"bullet")(16, 16, 16, 16);
	}
	if (moveType == 0) bulletMove = EnemyMove::tokasoku;
	else if (moveType == 1) bulletMove = EnemyMove::juryoku;
	cnt = 0;
	rad = 1.0;
	enable = true;
}

void Bullet::move() {
	bulletMove(&pos, &vel);
	cnt++;
	if (pos.x > Window::Width() + 30 || pos.x < 0 - 30 ||
		pos.y > Window::Height() + 30 || pos.y < 0 - 30) {
		burn();
	}
}

void Bullet::draw() {
	//Graphics::Set2DBlendState(BlendState::Additive());
	texture.scale(1.3).drawAt(pos);
	Graphics2D::SetBlendState(BlendState::Default);
}

void Bullet::burn() {
	enable = false;
}

BulletManager::BulletManager() {}

void BulletManager::create(Vec2 pos, Vec2 vel, int colorType, int moveType)
{
	auto b = std::make_shared<Bullet>();
	b->init(pos, vel, colorType, moveType);
	bullets.push_back(b);
}

void BulletManager::clear() {
	bullets.clear();
}

void BulletManager::draw() {
	for (const auto& bullet : bullets) {
		bullet->draw();
	}
}

void BulletManager::move() {
	for (const auto& bullet : bullets) {
		 bullet->move();
	}
	Erase_if(bullets, [](std::shared_ptr<Bullet> bullet) {return !bullet->getEnable(); });
}
