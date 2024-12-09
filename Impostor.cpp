#include "HelloWorldScene.h"
#include "Impostor.h"

USING_NS_CC;

Impostor::Impostor() :
	life(100), boxes(15), strength(5), boxAt(5), botAt(6), impostorS(nullptr), defaultAnimate(nullptr), punchAnimate(nullptr), blockAnimate(nullptr), jumpAnimate(nullptr), duckAnimate(nullptr), moveAnimate(nullptr), chargeAnimate(nullptr), defaultPowerAnimate(nullptr), attackAnimate(nullptr), hurtAnimate(nullptr), objectAnimate(nullptr) {}

bool Impostor::init() {
	if (!Sprite::init()) {
		return false;
	}

	impostorS = SpriteFrame::create("impostor/impostor.png", Rect(0, 0, 80, 110));

	health = life;

	if (!impostorS) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(impostorS);

	defaultAnimation();
	punchAnimation();
	blockAnimation();
	jumpAnimation();
	duckAnimation();
	moveAnimation();
	chargeAnimation();
	defaultPowerAnimation();
	attackAnimation();
	objectAnimation();
	hurtAnimation();

	return true;
}

Impostor::~Impostor() {
	CC_SAFE_RELEASE(defaultAnimate);
	CC_SAFE_RELEASE(punchAnimate);
	CC_SAFE_RELEASE(blockAnimate);
	CC_SAFE_RELEASE(jumpAnimate);
	CC_SAFE_RELEASE(duckAnimate);
	CC_SAFE_RELEASE(moveAnimate);
	CC_SAFE_RELEASE(chargeAnimate);
	CC_SAFE_RELEASE(defaultPowerAnimate);
	CC_SAFE_RELEASE(attackAnimate);
	CC_SAFE_RELEASE(objectAnimate);
	CC_SAFE_RELEASE(hurtAnimate);
}

void Impostor::defaultAnimation() {
	auto normal1I = SpriteFrame::create("impostor/impostor.png", Rect(0, 0, 90, 110));
	impostorData[normal1I].insert(std::pair<float, float>(64, 80));
	impostorData[normal1I].insert(std::pair<float, float>(66, 60));
	tagsI[normal1I] = "normalI1";

	auto normal2I = SpriteFrame::create("impostor/impostorDefault.png", Rect(0, 0, 90, 110));
	impostorData[normal2I].insert(std::pair<float, float>(64, 83));
	impostorData[normal2I].insert(std::pair<float, float>(66, 63));
	tagsI[normal2I] = "normalI2";

	defaultVector.pushBack(normal1I);
	defaultVector.pushBack(normal2I);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Impostor::punchAnimation() {
	auto punchI = SpriteFrame::create("impostor/impostorPunch.png", Rect(0, 0, 90, 110));
	impostorData[punchI].insert(std::pair<float, float>(48, 65));
	tagsI[punchI] = "punchI";

	punchVector.pushBack(punchI);
	// a lo mejor agregar normal

	auto punAnimation = Animation::createWithSpriteFrames(punchVector, 0.15f);
	punchAnimate = Animate::create(punAnimation);
	punchAnimate->retain();

}

void Impostor::blockAnimation() {
	auto blockI = SpriteFrame::create("impostor/impostorBlock.png", Rect(0, 0, 90, 110));
	impostorData[blockI].insert(std::pair<float, float>(64, 80));
	tagsI[blockI] = "blockI";

	blockVector.pushBack(blockI);
	// a lo mejor agregar normal

	auto blckAnimation = Animation::createWithSpriteFrames(blockVector, 0.30f);
	blockAnimate = Animate::create(blckAnimation);
	blockAnimate->retain();

}

void Impostor::jumpAnimation() {
	auto jumpI = SpriteFrame::create("impostor/impostorJump.png", Rect(0, 0, 90, 110));
	tagsI[jumpI] = "jumpI";

	jumpVector.pushBack(jumpI);

	auto jmpAnimation = Animation::createWithSpriteFrames(jumpVector, 0.20f);
	jumpAnimate = Animate::create(jmpAnimation);
	jumpAnimate->retain();

}

void Impostor::duckAnimation() {
	auto duckI = SpriteFrame::create("impostor/impostorDuck.png", Rect(0, 0, 90, 110));
	impostorData[duckI].insert(std::pair<float, float>(64, 68));
	tagsI[duckI] = "duckI";

	duckVector.pushBack(duckI);

	auto dckAnimation = Animation::createWithSpriteFrames(duckVector, 0.20f);
	duckAnimate = Animate::create(dckAnimation);
	duckAnimate->retain();

}

void Impostor::moveAnimation() {
	auto moveI = SpriteFrame::create("impostor/impostorMove.png", Rect(0, 0, 90, 110));
	impostorData[moveI].insert(std::pair<float, float>(64, 80));
	impostorData[moveI].insert(std::pair<float, float>(64, 60));
	tagsI[moveI] = "moveI";

	moveVector.pushBack(moveI);

	auto mvAnimation = Animation::createWithSpriteFrames(moveVector, 0.25f);
	moveAnimate = Animate::create(mvAnimation);
	moveAnimate->retain();

}

void Impostor::chargeAnimation() {
	auto chargeI = SpriteFrame::create("impostor/impostorCharge.png", Rect(0, 0, 90, 110));
	tagsI[chargeI] = "chargeI";

	chargeVector.pushBack(chargeI);

	auto chrAnimation = Animation::createWithSpriteFrames(chargeVector, 0.30f);
	chargeAnimate = Animate::create(chrAnimation);
	chargeAnimate->retain();

}

void Impostor::defaultPowerAnimation() {
	auto power1I = SpriteFrame::create("impostor/impostorPowerUp1.png", Rect(0, 0, 90, 110));
	impostorData[power1I].insert(std::pair<float, float>(64, 79));
	impostorData[power1I].insert(std::pair<float, float>(66, 60));
	tagsI[power1I] = "powerI1";

	auto power2I = SpriteFrame::create("impostor/impostorPowerUp.png", Rect(0, 0, 90, 110));
	impostorData[power2I].insert(std::pair<float, float>(64, 80));
	impostorData[power2I].insert(std::pair<float, float>(66, 62));
	tagsI[power2I] = "powerI2";

	defaultPowerVector.pushBack(power1I);
	defaultPowerVector.pushBack(power2I);

	auto defPowAnimation = Animation::createWithSpriteFrames(defaultPowerVector, 0.20f);
	defaultPowerAnimate = Animate::create(defPowAnimation);
	defaultPowerAnimate->retain();

}

void Impostor::attackAnimation() {
	auto attack1I = SpriteFrame::create("impostor/impostorJumpP.png", Rect(0, 0, 90, 110));
	auto attack2I = SpriteFrame::create("impostor/impostorSuper.png", Rect(0, 0, 90, 110));

	attackVector.pushBack(attack1I);
	attackVector.pushBack(attack2I);

	auto attAnimation = Animation::createWithSpriteFrames(attackVector, 0.20f);
	attackAnimate = Animate::create(attAnimation);
	attackAnimate->retain();

}

void Impostor::objectAnimation() {
	auto getOI = SpriteFrame::create("impostor/impostorPrep.png", Rect(0, 0, 90, 110));
	tagsI[getOI] = "getO";

	auto throwOI = SpriteFrame::create("impostor/impostorThrow.png", Rect(0, 0, 90, 110));
	tagsI[throwOI] = "throwO";

	objectVector.pushBack(getOI);
	objectVector.pushBack(throwOI);

	auto objAnimation = Animation::createWithSpriteFrames(objectVector, 0.20f);
	objectAnimate = Animate::create(objAnimation);
	objectAnimate->retain();

}

void Impostor::hurtAnimation() {
	auto hurtI = SpriteFrame::create("impostor/impostorHurt.png", Rect(0, 0, 90, 110));
	tagsI[hurtI] = "hurtI";

	hurtVector.pushBack(hurtI);

	auto htAnimation = Animation::createWithSpriteFrames(hurtVector, 0.50f);
	hurtAnimate = Animate::create(htAnimation);
	hurtAnimate->retain();

}

void Impostor::againDefault(cocos2d::Animate* temp) {
	auto delay = DelayTime::create(temp->getDuration());
	auto revert = CallFunc::create([=]() {
		if (!superP) {
			runDefaultAnimation();
		}
		else {
			runDefaultPowerAnimation();
		}
		});

	this->runAction(Sequence::create(delay, revert, nullptr));
}

void Impostor::runDefaultAnimation() {
	auto action = cocos2d::RepeatForever::create(defaultAnimate);
	this->runAction(action);
}

void Impostor::runDefaultPowerAnimation() {
	auto action = cocos2d::RepeatForever::create(defaultPowerAnimate);
	this->runAction(action);
}

void Impostor::runPunchAnimation() {
	this->stopAllActions();
	this->runAction(punchAnimate);

	againDefault(punchAnimate);
}

void Impostor::runBlockAnimation() {
	this->stopAllActions();
	this->runAction(blockAnimate);

}

void Impostor::runJumpAnimation() {
	this->stopAllActions();
	this->runAction(jumpAnimate);

	againDefault(jumpAnimate);

}

void Impostor::runDuckAnimation() {
	this->stopAllActions();
	this->runAction(duckAnimate);
}

void Impostor::runMoveRightAnimation() {
	if (moveAnimate || !isMovingRight) {
		isMovingRight = true;
		this->stopAllActions();
		this->runAction(moveAnimate);

		//this->setPositionX(this->getPositionX() + .5);
		auto move = MoveBy::create(0.1f, Vec2(10, 0));
		auto finish = CallFunc::create([this]() {
			isMovingRight = false;
			});

		this->runAction(Sequence::create(move, finish, nullptr));
		againDefault(moveAnimate);
	}
}

void Impostor::runMoveLeftAnimation() {
	if (moveAnimate || !isMovingLeft) {
		isMovingLeft = true;
		this->stopAllActions();
		this->runAction(moveAnimate);

		//this->setPositionX(this->getPositionX() - .5);
		auto move = MoveBy::create(0.1f, Vec2(-5, 0));
		auto finish = CallFunc::create([this]() {
			isMovingRight = false;
			});

		this->runAction(Sequence::create(move, finish, nullptr));

		againDefault(moveAnimate);
	}
}

void Impostor::runChargeAnimation() {
	this->stopAllActions();
	this->runAction(chargeAnimate);
	superP = true;

	againDefault(chargeAnimate);
}

void Impostor::runHurtAnimation() {
	if (hurtAnimate) {
		this->stopAllActions();
		this->runAction(hurtAnimate);

		againDefault(hurtAnimate);
	}
}

void Impostor::runObjectAnimation() {
	if (objectAnimate) {
		this->stopAllActions();
		this->runAction(objectAnimate);

		againDefault(objectAnimate);
	}
}

void Impostor::runAttackAnimation(float x, float y) {
	this->stopAllActions();
	this->runAction(attackAnimate);

	auto move = MoveTo::create(0.1f, Vec2(x, y));
	this->runAction(move);

	superP = false;

	againDefault(attackAnimate);
}

float Impostor::getLife() const{
	return life;
}

void Impostor::setLife(float life) {
	this->life = life;
}

cocos2d::SpriteFrame* Impostor::getSprite() const {
	return impostorS;
}

float Impostor::getBoxAt() const {
	return boxAt;
}

void Impostor::setBoxAt(float bxA) {
	this->boxAt = bxA;
}

float Impostor::getStrength() {
	return strength;
}

void Impostor::setStrength(float strng) {
	this->strength = strng;
}