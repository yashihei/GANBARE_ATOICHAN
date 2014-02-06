#pragma once
#include <memory>
#include <vector>

class Actor {
public:
	virtual ~Actor(){};
	virtual void draw() = 0;
	virtual void move() = 0;
	bool getEnable() const { return enable; }
	void setEnable(bool val) { enable = val; }
protected:
	bool enable;
};

template <class T>
class ActorPool {
public:
	ActorPool(int num) {
		actors.resize(num);
		for (const auto& actor : actors) {
			actor->setEnable(false);
		}
	}
	std::shared_ptr<T> getInstance() {
		for (const auto& actor : actors) {
			if (!actor->getEnable()) {
				actor->setEnable(true);
				return actor;
			}
			return nullptr;
		}
	}
	void clear() {
		for (const auto& actor : actors) {
			actor->setEnable(false);
		}
	}
	void draw() {
		for (const auto& actor : actors) {
			if (actor->getEnable()) actor->draw();
		}
	}
	void move() {
		for (const auto& actor : actors) {
			if (actor->getEnable()) actor->move();
		}
	}
protected:
	std::vector<std::shared_ptr<T>> actors;
};

