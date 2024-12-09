#include "HelloWorldScene.h"
#include "Secta.h"

USING_NS_CC;

Secta::Secta() :
	life(20), shadow(15), attack(10),sect(nullptr),defaultAnimate(nullptr),attackAnimate(nullptr),superAnimate(nullptr) {}

Secta::~Secta() {
	CC_SAFE_RELEASE(defaultAnimate);
	CC_SAFE_RELEASE(attackAnimate);
	CC_SAFE_RELEASE(superAnimate);
}

bool Secta::init() {
	if (!Sprite::init()) {
		return false;
	}

	sect = SpriteFrame::create("sect/sect.png", Rect(0, 0, 80, 110));

	if (!sect) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(sect);

	defaultAnimation();
	attackAnimation();
	superAnimation();

	return true;
}

void Secta::defaultAnimation() {
	auto normalSF = SpriteFrame::create("sect/sect.png", Rect(0, 0, 90, 110));
	sectData[normalSF].insert(std::pair<float, float>(70, 60));
	secttags[normalSF] = "normalSF";

	auto normal1SF = SpriteFrame::create("sect/sectDefault.png", Rect(0, 0, 90, 110));
	sectData[normal1SF].insert(std::pair<float, float>(70, 60));
	secttags[normal1SF] = "normal1SF";

	defaultVector.pushBack(normalSF);
	defaultVector.pushBack(normal1SF);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Secta::attackAnimation() {
	auto attackSF = SpriteFrame::create("sect/sectAttack.png", Rect(0, 0, 90, 110));
	secttags[attackSF] = "attackSF";

	attackVector.pushBack(attackSF);

	auto attAnimation = Animation::createWithSpriteFrames(attackVector, 0.20f);
	attackAnimate = Animate::create(attAnimation);
	attackAnimate->retain();

}

void Secta::superAnimation() {
	auto Sattack = SpriteFrame::create("sect/sectSuper.png", Rect(0, 0, 90, 110));
	secttags[Sattack] = "Sattack";

	superVector.pushBack(Sattack);

	auto spAnimation = Animation::createWithSpriteFrames(superVector, 0.20f);
	superAnimate = Animate::create(spAnimation);
	superAnimate->retain();

}

void Secta::againDefault(cocos2d::Animate* temp) {
	auto delay = DelayTime::create(temp->getDuration());
	auto revert = CallFunc::create([=]() {
			runDefaultAnimation();
		});

	this->runAction(Sequence::create(delay, revert, nullptr));
}

void Secta::runDefaultAnimation() {
	auto action = cocos2d::RepeatForever::create(defaultAnimate);
	this->runAction(action);
}

void Secta::runAttackAnimation() {
	this->stopAllActions();
	this->runAction(attackAnimate);

	againDefault(attackAnimate);
}

void Secta::runSuperAnimation() {
	this->stopAllActions();
	this->runAction(superAnimate);

	againDefault(superAnimate);
}

float Secta::getLive() const {
	return life;
}

void Secta::setLive(float live) {
	this->life = live;
}

float Secta::getShadow() const {
	return shadow;
}

float Secta::getAttack() const {
	return attack;
}

cocos2d::SpriteFrame* Secta::getSprite() const {
	return sect;
}