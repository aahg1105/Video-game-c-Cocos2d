#include "HelloWorldScene.h"
#include "Boss.h"

USING_NS_CC;
Boss::Boss() :
	life(200), strength(20), bullet(20), shadow(15), boss(nullptr), defaultAnimate(nullptr),attackAnimate(nullptr),moveAnimate(nullptr),fireAnimate(nullptr),magicAnimate(nullptr),QAnimate(nullptr),superAnimate(nullptr){

}

Boss::~Boss() {	
	CC_SAFE_RELEASE(defaultAnimate);
	CC_SAFE_RELEASE(attackAnimate);
	CC_SAFE_RELEASE(moveAnimate);
	CC_SAFE_RELEASE(magicAnimate);
	CC_SAFE_RELEASE(superAnimate);
	CC_SAFE_RELEASE(fireAnimate);
}

bool Boss::init() {
	if (!Sprite::init()) {
		return false;
	}

	boss = SpriteFrame::create("guard/guard.png", Rect(0, 0, 90, 110));

	if (!boss) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(boss);

	defaultAnimation();
	attackAnimation();
	moveAnimation();
	fireAnimation();
	kickAnimation();
	magicAnimation();
	QAnimation();
	superAnimation();

	return true;
}

void Boss::defaultAnimation() {
	auto normalBSF = SpriteFrame::create("boss/boss.png", Rect(0, 0, 80, 110));
	bossData[normalBSF].insert(std::pair<float, float>(60, 58));
	bossData[normalBSF].insert(std::pair<float, float>(60, 80));
	bossTags[normalBSF] = "normalB";

	auto normal1BSF = SpriteFrame::create("boss/bossDefault.png", Rect(0, 0, 80, 110));
	bossData[normal1BSF].insert(std::pair<float, float>(60, 60));
	bossData[normal1BSF].insert(std::pair<float, float>(60, 80));
	bossTags[normal1BSF] = "normalB1";

	defaultVector.pushBack(normalBSF);
	defaultVector.pushBack(normal1BSF);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Boss::moveAnimation() {
	auto moveBSF = SpriteFrame::create("boss/bossMove.png", Rect(0, 0, 80, 110));
	bossData[moveBSF].insert(std::pair<float, float>(60, 60));
	bossData[moveBSF].insert(std::pair<float, float>(60, 80));
	bossTags[moveBSF] = "moveB";

	moveVector.pushBack(moveBSF);

	auto mvAnimation = Animation::createWithSpriteFrames(moveVector, 0.15f);
	moveAnimate = Animate::create(mvAnimation);
	moveAnimate->retain();

}

void Boss::fireAnimation() {
	auto fireBSF = SpriteFrame::create("boss/bossGun.png", Rect(0, 0, 80, 110));
	bossTags[fireBSF] = "fireB";

	fireVector.pushBack(fireBSF);

	auto frAnimation = Animation::createWithSpriteFrames(fireVector, 0.10f);
	fireAnimate = Animate::create(frAnimation);
	fireAnimate->retain();

}

void Boss::attackAnimation() {
	auto attackBSF = SpriteFrame::create("boss/bossAttack.png", Rect(0, 0, 80, 110));
	bossData[attackBSF].insert(std::pair<float, float>(40, 68));
	bossTags[attackBSF] = "attackB";

	attackVector.pushBack(attackBSF);

	auto attAnimation = Animation::createWithSpriteFrames(attackVector, 0.10f);
	attackAnimate = Animate::create(attAnimation);
	attackAnimate->retain();

}

void Boss::kickAnimation() {
	auto kickBSF = SpriteFrame::create("boss/bossKick.png", Rect(0, 0, 80, 110));
	bossData[kickBSF].insert(std::pair<float, float>(28, 50));
	bossTags[kickBSF] = "kickB";

	kickVector.pushBack(kickBSF);

	auto kcAnimation = Animation::createWithSpriteFrames(kickVector, 0.15f);
	kickAnimate = Animate::create(kcAnimation);
	kickAnimate->retain();

}

void Boss::magicAnimation() {
	auto magicBSF = SpriteFrame::create("boss/bossMagic.png", Rect(0, 0, 80, 110));
	bossTags[magicBSF] = "magicB";
	magicVector.pushBack(magicBSF);

	auto mgAnimation = Animation::createWithSpriteFrames(magicVector, 0.10f);
	magicAnimate = Animate::create(mgAnimation);
	magicAnimate->retain();

}

void Boss::QAnimation() {
	auto QBSF = SpriteFrame::create("boss/bossQ.png", Rect(0, 0, 80, 110));
	bossTags[QBSF] = "QB";

	QVector.pushBack(QBSF);

	auto qAnimation = Animation::createWithSpriteFrames(QVector, 0.15f);
	QAnimate = Animate::create(qAnimation);
	QAnimate->retain();

}

void Boss::chargeAnimation() {
	auto chargeBSF = SpriteFrame::create("boss/bossCharge.png", Rect(0, 0, 80, 110));
	bossTags[chargeBSF] = "chargeB";

	chargeVector.pushBack(chargeBSF);

	auto chAnimation = Animation::createWithSpriteFrames(chargeVector, 0.07f);
	chargeAnimate = Animate::create(chAnimation);
	chargeAnimate->retain();
}

void Boss::superAnimation() {
	auto superBSF = SpriteFrame::create("boss/bossSuper.png", Rect(0, 0, 80, 110));
	bossData[superBSF].insert(std::pair<float, float>(29, 71));
	bossTags[superBSF] = "superB";

	superVector.pushBack(superBSF);

	auto spAnimation = Animation::createWithSpriteFrames(superVector, 0.10f);
	superAnimate = Animate::create(spAnimation);
	superAnimate->retain();

}

void Boss::againDefault(cocos2d::Animate* temp) {
	auto delay = DelayTime::create(temp->getDuration());
	auto revert = CallFunc::create([=]() {
			runDefaultAnimation();
		});

	this->runAction(Sequence::create(delay, revert, nullptr));
}

void Boss::runDefaultAnimation() {
	auto action = cocos2d::RepeatForever::create(defaultAnimate);
	this->runAction(action);
}

void Boss::runMoveAnimation() {
	this->stopAllActions();
	this->runAction(moveAnimate);
	this->setPosition(this->getPositionX() - 15, this->getPositionY());

	againDefault(moveAnimate);
}

void Boss::runFireAnimation() {
	this->stopAllActions();
	this->runAction(fireAnimate);

	againDefault(fireAnimate);
}

void Boss::runAttackAnimation() {
	this->stopAllActions();
	this->runAction(attackAnimate);

	againDefault(attackAnimate);
}

void Boss::runKickAnimation() {
	this->stopAllActions();
	this->runAction(kickAnimate);

	againDefault(kickAnimate);
}

void Boss::runMagicAnimation() {
	this->stopAllActions();
	this->runAction(magicAnimate);

	againDefault(magicAnimate);
}

void Boss::runQAnimation() {
	this->stopAllActions();
	this->runAction(QAnimate);

	againDefault(QAnimate);
}

void Boss::runChargeAnimation() {
	this->stopAllActions();
	this->runAction(chargeAnimate);
}

void Boss::runSuperAnimation() {
	this->stopAllActions();
	this->runAction(superAnimate);

	// mover el sprite

	againDefault(superAnimate);
}

float Boss::getLife() const {
	return life;
}

void Boss::setLife(float live) {
	this->life = live;
}

float Boss::getBullet() const {
	return bullet;
}

void Boss::setBullet(float bull) {
	this->bullet = bull;
}

float Boss::getStrength() const {
	return strength;
}

void Boss::setStrength(float strg) {
	this->strength = strg;
}

float Boss::getShadow() const {
	return shadow;
}

void Boss::setShadow(float sh) {
	this->shadow = sh;
}

cocos2d::SpriteFrame* Boss::getSprite() const {
	return boss;
}