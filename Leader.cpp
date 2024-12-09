#include "HelloWorldScene.h"
#include "Leader.h"

USING_NS_CC;
// attack, heal, superA;
Leader::Leader() :
	life(40), attack(15), heal(10), superA(10), leader(nullptr), defaultAnimate(nullptr), attackAnimate(nullptr), superAnimate(nullptr),healAnimate(nullptr),teleAnimate(nullptr) {}

Leader::~Leader() {
	CC_SAFE_RELEASE(defaultAnimate);
	CC_SAFE_RELEASE(attackAnimate);
	CC_SAFE_RELEASE(superAnimate);
	CC_SAFE_RELEASE(healAnimate);
	CC_SAFE_RELEASE(teleAnimate);
}

bool Leader::init() {
	if (!Sprite::init()) {
		return false;
	}

	leader = SpriteFrame::create("leader/leader.png", Rect(0, 0, 80, 110));

	if (!leader) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(leader);

	defaultAnimation();
	attackAnimation();
	superAnimation();
	healAnimation();

	return true;
}

void Leader::defaultAnimation() {
	auto normalLSF = SpriteFrame::create("leader/leaderDefault.png", Rect(0, 0, 80, 110));
	leaderData[normalLSF].insert(std::pair<float, float>(70, 60));
	leadertags[normalLSF] = "normalLSF";

	auto normal1LSF = SpriteFrame::create("leader/leaderDefault.png", Rect(0, 0, 80, 110));
	leaderData[normal1LSF].insert(std::pair<float, float>(70, 60));
	leadertags[normal1LSF] = "normal1LSF";

	defaultVector.pushBack(normalLSF);
	defaultVector.pushBack(normal1LSF);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Leader::attackAnimation() {
	auto attackLSF = SpriteFrame::create("leader/leaderAttack.png", Rect(0, 0, 80, 110));
	leadertags[attackLSF] = "attackLSF";

	attackVector.pushBack(attackLSF);

	// ver especificaciones

	auto attAnimation = Animation::createWithSpriteFrames(attackVector, 0.20f);
	attackAnimate = Animate::create(attAnimation);
	attackAnimate->retain();

}

void Leader::healAnimation() {
	auto healLSF = SpriteFrame::create("leader/leaderAttack.png", Rect(0, 0, 80, 110));
	leadertags[healLSF] = "attackLSF";

	healVector.pushBack(healLSF);

	// ver especificaciones

	auto hlAnimation = Animation::createWithSpriteFrames(healVector, 0.40f);
	healAnimate = Animate::create(hlAnimation);
	healAnimate->retain();

}


void Leader::superAnimation() {
	auto SattackLSF = SpriteFrame::create("leader/leaderSuper.png", Rect(0, 0, 80, 110));
	leadertags[SattackLSF] = "SattackLSF";

	superVector.pushBack(SattackLSF);

	auto spAnimation = Animation::createWithSpriteFrames(superVector, 0.40f);
	superAnimate = Animate::create(spAnimation);
	superAnimate->retain();

}

void Leader::againDefault(cocos2d::Animate* temp) {
	auto delay = DelayTime::create(temp->getDuration());
	auto revert = CallFunc::create([=]() {
			runDefaultAnimation();
		});

	this->runAction(Sequence::create(delay, revert, nullptr));
}

void Leader::runDefaultAnimation() {
	auto action = cocos2d::RepeatForever::create(defaultAnimate);
	this->runAction(action);
}

void Leader::runAttackAnimation() {
	this->stopAllActions();
	this->runAction(attackAnimate);

	againDefault(attackAnimate);
}

void Leader::runHealAnimation() {
	this->stopAllActions();
	this->runAction(healAnimate);

	againDefault(healAnimate);
}

void Leader::runSuperAnimation() {
	this->stopAllActions();
	this->runAction(superAnimate);

	againDefault(superAnimate);
}

float Leader::getLive() const {
	return life;
}

void Leader::setLive(float live) {
	this->life = live;
}


float Leader::getAttack() const {
	return attack;
}

float Leader::getHeal() const {
	return heal;
}

float Leader::getSuperA() const {
	return superA;
}

cocos2d::SpriteFrame* Leader::getSprite() const {
	return leader;
}