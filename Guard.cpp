#include "HelloWorldScene.h"
#include "Guard.h"

USING_NS_CC;

Guard::Guard() :
	life(140), attack(15), bullet(20), guard(nullptr), defaultAnimate(nullptr), punchRightAnimate(nullptr), punchLeftAnimate(nullptr), moveAnimate(nullptr), fireAnimate(nullptr) {}

bool Guard::init() {
	if (!Sprite::init()) {
		return false;
	}

	guard = SpriteFrame::create("guard/guard.png", Rect(0, 0, 90, 110));

	if (!guard) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(guard);

	defaultAnimation();
	punchRightAnimation();
	punchLeftAnimation();
	moveAnimation();
	fireAnimation();

	return true;
}
	

Guard::~Guard() {
	CC_SAFE_RELEASE(defaultAnimate);
	CC_SAFE_RELEASE(punchRightAnimate);
	CC_SAFE_RELEASE(moveAnimate);
	CC_SAFE_RELEASE(punchLeftAnimate);
	CC_SAFE_RELEASE(punchLeftAnimate);
	CC_SAFE_RELEASE(fireAnimate);
}

void Guard::defaultAnimation() {
	auto normalGSF = SpriteFrame::create("guard/guard.png", Rect(0, 0, 80, 110));
	guardData[normalGSF].insert(std::pair<float, float>(55, 55));
	guardData[normalGSF].insert(std::pair<float, float>(55, 80));
	customerTags[normalGSF] = "normal";

	auto normal1GSF = SpriteFrame::create("guard/guardDefault.png", Rect(0, 0, 80, 110));
	guardData[normal1GSF].insert(std::pair<float, float>(55, 55));
	guardData[normal1GSF].insert(std::pair<float, float>(55, 80));
	customerTags[normal1GSF] = "normal1";

	defaultVector.pushBack(normalGSF);
	defaultVector.pushBack(normal1GSF);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Guard::punchRightAnimation() {
	auto rightGSF = SpriteFrame::create("guard/guardRight.png", Rect(0, 0, 80, 110));
	guardData[rightGSF].insert(std::pair<float, float>(32, 65));
	customerTags[rightGSF] = "punchR";

	punchRightVector.pushBack(rightGSF);

	auto defAnimation = Animation::createWithSpriteFrames(punchRightVector, 0.15f);
	punchRightAnimate = Animate::create(defAnimation);
	punchRightAnimate->retain();

}

void Guard::punchLeftAnimation() {
	auto leftGSF = SpriteFrame::create("guard/guardLeft.png", Rect(0, 0, 80, 110));
	guardData[leftGSF].insert(std::pair<float, float>(36, 62));
	customerTags[leftGSF] = "punchL";

	punchLeftVector.pushBack(leftGSF);

	auto defAnimation = Animation::createWithSpriteFrames(punchLeftVector, 0.15f);
	punchLeftAnimate = Animate::create(defAnimation);
	punchLeftAnimate->retain();

}

void Guard::moveAnimation() {
	auto moveGSF = SpriteFrame::create("guard/guardMove.png", Rect(0, 0, 80, 110));
	guardData[moveGSF].insert(std::pair<float, float>(55, 55));
	guardData[moveGSF].insert(std::pair<float, float>(55, 80));
	customerTags[moveGSF] = "move";

	moveVector.pushBack(moveGSF);

	auto defAnimation = Animation::createWithSpriteFrames(moveVector, 0.15f);
	moveAnimate = Animate::create(defAnimation);
	moveAnimate->retain();

}

void Guard::fireAnimation() {
	auto fireGSF = SpriteFrame::create("guard/guardGun.png", Rect(0, 0, 80, 110));
	guardData[fireGSF].insert(std::pair<float, float>(55, 55));
	guardData[fireGSF].insert(std::pair<float, float>(55, 80));
	customerTags[fireGSF] = "fire";

	fireVector.pushBack(fireGSF);

	auto defAnimation = Animation::createWithSpriteFrames(fireVector, 0.10f);
	fireAnimate = Animate::create(defAnimation);
	fireAnimate->retain();

}

void Guard::againDefault(cocos2d::Animate* temp) {
	auto delay = DelayTime::create(temp->getDuration());
	auto revert = CallFunc::create([=]() {
			runDefaultAnimation();
		});

	this->runAction(Sequence::create(delay, revert, nullptr));
}

void Guard::runDefaultAnimation() {
	auto action = cocos2d::RepeatForever::create(defaultAnimate);
	this->runAction(action);
}

void Guard::runPunchRightAnimation() {
	this->stopAllActions();
	this->runAction(punchRightAnimate);

	againDefault(punchRightAnimate);
}

void Guard::runPunchLeftAnimation() {
	this->stopAllActions();
	this->runAction(punchLeftAnimate);

	againDefault(punchLeftAnimate);
}

void Guard::runMoveAnimation() {
	this->stopAllActions();
	this->runAction(moveAnimate);
	this->setPosition(this->getPositionX() - 15, this->getPositionY());

	againDefault(moveAnimate);
}

void Guard::runFireAnimation() {
	this->stopAllActions();
	this->runAction(fireAnimate);

	againDefault(fireAnimate);
}

float Guard::getLive() const {
	return life;
}

void Guard::setLive(float live) {
	this->life = live;
}

float Guard::getAttack() const {
	return attack;
}

void Guard::setAttack(float att) {
	this->attack = att;
}

float Guard::getBullet() const {
	return bullet;
}

void Guard::setBullet(float bull) {
	this->bullet = bull;
}

cocos2d::SpriteFrame* Guard::getSprite() const {
	return guard;
}