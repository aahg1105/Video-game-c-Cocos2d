#include "Girlfriend.h"

USING_NS_CC;

Girlfriend::Girlfriend() :
	life(100), girlfriend(nullptr), defaultAnimate(nullptr){}

Girlfriend::~Girlfriend() {
	CC_SAFE_RELEASE(defaultAnimate);
}

bool Girlfriend::init() {
	if (!Sprite::init()) {
		return false;
	}

	girlfriend = SpriteFrame::create("girlfriend/girlfriend.png", Rect(0, 0, 80, 110));

	if (!girlfriend) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(girlfriend);

	defaultAnimation();

	return true;
}

void Girlfriend::defaultAnimation() {
	auto normal1 = SpriteFrame::create("girlfriend/girlfriend.png", Rect(0, 0, 80, 110));
	auto normal2 = SpriteFrame::create("girlfriend/girlfriendDefault.png", Rect(0, 0, 80, 110));

	defaultVector.pushBack(normal1);
	defaultVector.pushBack(normal2);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Girlfriend::runDefaultAnimation() {
	if (defaultAnimate) {
		auto action = cocos2d::RepeatForever::create(defaultAnimate);
		this->runAction(action);
	}
}

cocos2d::SpriteFrame* Girlfriend::getSprite() const {
	return girlfriend;
}