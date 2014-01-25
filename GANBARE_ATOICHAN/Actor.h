#pragma once
#include <memory>
#include <list>

class Actor {
public:
	virtual ~Actor(){};
	virtual void draw() = 0;
	virtual void move() = 0;
};

class ActorManager {
public:
	void clear() {
		actors.clear();
	}
	void draw() {
		for (const auto& actor : actors) {
			actor->draw();
		}
	}
	void move() {
		for (const auto& actor : actors) {
			actor->move();
		}
	}
protected:
	std::list<std::shared_ptr<Actor>> actors;
};

