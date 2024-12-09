#include "Player.h"

USING_NS_CC;

Player::Player() :
	life(100), boxes(15), bottles(0), power("None"), name("Benji"), strength(5),boxAt(5), botAt(6), healthBar(nullptr), player(nullptr), defaultAnimate(nullptr), punchAnimate(nullptr), blockAnimate(nullptr), jumpAnimate(nullptr), duckAnimate(nullptr), moveAnimate(nullptr), chargeAnimate(nullptr), defaultPowerAnimate(nullptr), attackAnimate(nullptr), hurtAnimate(nullptr), objectAnimate(nullptr) {}

Player::~Player() {
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

bool Player::init() {
	if (!Sprite::init()) {
		return false;
	}

	player = SpriteFrame::create("player/player.png", Rect(0, 0, 80, 110));

	health = life;

	if (!player) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(player);

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

void Player::defaultAnimation() {
	auto normal1 = SpriteFrame::create("player/player.png", Rect(0, 0, 80, 110));
	playerData[normal1].insert(std::pair<float, float>(54, 80));
	playerData[normal1].insert(std::pair<float, float>(52, 60));
	tags[normal1] = "normal1";

	auto normal2 = SpriteFrame::create("player/playerDefault.png", Rect(0, 0, 80, 110));
	playerData[normal2].insert(std::pair<float, float>(54, 83));
	playerData[normal2].insert(std::pair<float, float>(52, 63));
	tags[normal2] = "normal2";

	if (!normal1 || !normal2) {
		CCLOG("Error: No se pudieron cargar los frames para la animación.");
		return;
	}

	defaultVector.pushBack(normal1);
	defaultVector.pushBack(normal2);

	auto defAnimation = Animation::createWithSpriteFrames(defaultVector,0.20f);
	defaultAnimate = Animate::create(defAnimation);
	defaultAnimate->retain();

}

void Player::hurtAnimation() {
	auto hurt = SpriteFrame::create("player/playerHurt.png", Rect(0, 0, 80, 110));
	tags[hurt] = "hurt";

	hurtVector.pushBack(hurt);

	auto htAnimation = Animation::createWithSpriteFrames(hurtVector, 0.50f);
	hurtAnimate = Animate::create(htAnimation);
	hurtAnimate->retain();

}

void Player::punchAnimation() {
	auto punch = SpriteFrame::create("player/playerPunch.png", Rect(0, 0, 80, 110));
	playerData[punch].insert(std::pair<float, float>(70, 65));
	tags[punch] = "punch";

	punchVector.pushBack(punch);

	auto punAnimation = Animation::createWithSpriteFrames(punchVector, 0.20f);
	punchAnimate = Animate::create(punAnimation);
	punchAnimate->retain();

}

void Player::blockAnimation() {
	auto block = SpriteFrame::create("player/playerBlock.png", Rect(0, 0, 80, 110));
	playerData[block].insert(std::pair<float, float>(54, 80));
	tags[block] = "block";

	blockVector.pushBack(block);

	auto blckAnimation = Animation::createWithSpriteFrames(blockVector, 2.50f);
	blockAnimate = Animate::create(blckAnimation);
	blockAnimate->retain();

}

void Player::jumpAnimation() {
	auto jump = SpriteFrame::create("player/playerHigh.png", Rect(0, 0, 80, 110));
	tags[jump] = "jump";

	jumpVector.pushBack(jump);

	auto jmpAnimation = Animation::createWithSpriteFrames(jumpVector, 0.30f);
	jumpAnimate = Animate::create(jmpAnimation);
	jumpAnimate->retain();

}

void Player::duckAnimation() {
	auto duck = SpriteFrame::create("player/playerDuck.png", Rect(0, 0, 80, 110));
	playerData[duck].insert(std::pair<float, float>(54, 65));
	tags[duck] = "duck";

	duckVector.pushBack(duck);

	auto dckAnimation = Animation::createWithSpriteFrames(duckVector, 0.40f);
	duckAnimate = Animate::create(dckAnimation);
	duckAnimate->retain();

}

void Player::moveAnimation() {
	auto move = SpriteFrame::create("player/playerMove.png", Rect(0, 0, 80, 110));
	playerData[move].insert(std::pair<float, float>(54, 80));
	playerData[move].insert(std::pair<float, float>(54, 60));
	tags[move] = "move";

	moveVector.pushBack(move);

	auto mvAnimation = Animation::createWithSpriteFrames(moveVector, 0.25f);
	moveAnimate = Animate::create(mvAnimation);
	moveAnimate->retain();

}

void Player::chargeAnimation() {
	auto charge = SpriteFrame::create("player/playerPower.png", Rect(0, 0, 80, 110));
	tags[charge] = "charge";

	chargeVector.pushBack(charge);

	auto chrAnimation = Animation::createWithSpriteFrames(chargeVector, 0.30f);
	chargeAnimate = Animate::create(chrAnimation);
	chargeAnimate->retain();

}

void Player::defaultPowerAnimation() {
	auto power1 = SpriteFrame::create("player/playerPowerUp1.png", Rect(0, 0, 80, 110));
	playerData[power1].insert(std::pair<float, float>(54, 79));
	playerData[power1].insert(std::pair<float, float>(52, 60));
	tags[power1] = "power1";

	auto power2 = SpriteFrame::create("player/playerPowerUp.png", Rect(0, 0, 80, 110));
	playerData[power2].insert(std::pair<float, float>(54, 80));
	playerData[power2].insert(std::pair<float, float>(52, 62));
	tags[power2] = "power2";

	defaultPowerVector.pushBack(power1);
	defaultPowerVector.pushBack(power2);

	auto defPowAnimation = Animation::createWithSpriteFrames(defaultPowerVector, 0.20f);
	defaultPowerAnimate = Animate::create(defPowAnimation);
	defaultPowerAnimate->retain();

}

void Player::objectAnimation() {
	auto getO = SpriteFrame::create("player/playerPrep.png", Rect(0, 0, 80, 110));
	tags[getO] = "getO";

	auto throwO = SpriteFrame::create("player/playerThrow.png", Rect(0, 0, 90, 110));
	tags[throwO] = "throwO";

	objectVector.pushBack(getO);
	objectVector.pushBack(throwO);

	auto objAnimation = Animation::createWithSpriteFrames(objectVector, 0.20f);
	objectAnimate = Animate::create(objAnimation);
	objectAnimate->retain();

}

void Player::attackAnimation() {
	auto attack1 = SpriteFrame::create("player/playerJumpP.png", Rect(0, 0, 80, 110));
	auto attack2 = SpriteFrame::create("player/playerSuper.png", Rect(0, 0, 90, 110));

	attackVector.pushBack(attack1);
	attackVector.pushBack(attack2);

	auto attAnimation = Animation::createWithSpriteFrames(attackVector, 0.20f);
	attackAnimate = Animate::create(attAnimation);
	attackAnimate->retain();

}

void Player::againDefault(cocos2d::Animate* temp) {
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

void Player::runDefaultAnimation() {
	if (defaultAnimate) {
		auto action = cocos2d::RepeatForever::create(defaultAnimate);
		this->runAction(action);
	}
}

void Player::runObjectAnimation() {
	if (objectAnimate) {
		this->stopAllActions();
		this->runAction(objectAnimate);

		againDefault(objectAnimate);
	}
}

void Player::runHurtAnimation() {
	if (hurtAnimate) {
		this->stopAllActions();
		this->runAction(hurtAnimate);

		againDefault(hurtAnimate);
	}
}

void Player::runDefaultPowerAnimation() {
	if (defaultPowerAnimate) {
		auto action = cocos2d::RepeatForever::create(defaultPowerAnimate);
		this->runAction(action);
	}
}

void Player::runPunchAnimation() {
	if (punchAnimate) {
		this->stopAllActions();
		this->runAction(punchAnimate);

		againDefault(punchAnimate);
	}
}

void Player::runBlockAnimation() {
	if (blockAnimate) {
		this->stopAllActions();
		this->runAction(blockAnimate);

		againDefault(moveAnimate);
	}

}

void Player::runJumpAnimation() {
	if (jumpAnimate) {
		this->stopAllActions();
		this->runAction(jumpAnimate);

		againDefault(jumpAnimate);
	}

}

void Player::runDuckAnimation() {
	if (duckAnimate) {
		this->stopAllActions();
		this->runAction(duckAnimate);

		againDefault(duckAnimate);
	}
}

void Player::runMoveRightAnimation() {
	if (moveAnimate || !isMovingRight) {
		isMovingRight = true;
		this->stopAllActions();
		this->runAction(moveAnimate);

		//this->setPositionX(this->getPositionX() + .5);
		auto move = MoveBy::create(0.1f, Vec2(5, 0));
		auto finish = CallFunc::create([this]() {
			isMovingRight = false;
		});

		this->runAction(Sequence::create(move,finish, nullptr));
		againDefault(moveAnimate);
	}
}

void Player::runMoveLeftAnimation() {
	if (moveAnimate || !isMovingLeft) {
		isMovingLeft = true;
		this->stopAllActions();
		this->runAction(moveAnimate);
		 
		//this->setPositionX(this->getPositionX() - .5);
		auto move = MoveBy::create(0.1f, Vec2(-5, 0));
		auto finish = CallFunc::create([this]() {
			isMovingRight = false;
			});

		this->runAction(Sequence::create(move,finish, nullptr));

		againDefault(moveAnimate);
	}
}

void Player::runChargeAnimation() {
	if (chargeAnimate) {
		this->stopAllActions();
		this->runAction(chargeAnimate);
		superP = true;

		againDefault(chargeAnimate);
	}
}


void Player::runAttackAnimation(float x,float y) {
	if (attackAnimate) {
		this->stopAllActions();
		this->runAction(attackAnimate);
		
		auto move = MoveTo::create(0.1f, Vec2(x, y));
		this->runAction(move);

		superP = false;

		againDefault(attackAnimate);
	}
}

cocos2d::SpriteFrame* Player::getSprite() const {
	return player;
}


cocos2d::Animate* Player::getBlockAnimate() const {
	return blockAnimate;
}

float Player::getLife() {
	return life;
}

void Player::setLife(float life) {
	this->life = life;
}

float Player::getStrength() {
	return strength;
}

void Player::setStrength(float strng) {
	this->strength = strng;
}

float Player::getBoxAt() const{
	return boxAt;
}

void Player::setBoxAt(float bxA) {
	this->boxAt = bxA;
}

std::string Player::getName() {
	return name;
}

void Player::setName(std::string name) {
	this->name = name;
}

std::string Player::getPower() {
	return power;
}

void Player::setPower(std::string pow) {
	this->power = pow;
}

void Player::setSuperP(bool aux) {
	this->superP = aux;
}