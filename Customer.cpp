#include "Customer.h"

USING_NS_CC;

Customer::Customer() :
	life(200),
	bottles(30),
	strength(10),
	botAt(5),
	customer(nullptr),
	defaultAnimate(nullptr),
	punchAnimate(nullptr),
	moveAnimate(nullptr),
	throwAnimate(nullptr),
	kickAnimate(nullptr) {}



Customer::~Customer() {
	CC_SAFE_RELEASE(defaultAnimate);
	CC_SAFE_RELEASE(punchAnimate);
	CC_SAFE_RELEASE(moveAnimate);
	CC_SAFE_RELEASE(throwAnimate);
	CC_SAFE_RELEASE(kickAnimate);
}

bool Customer::init() {
	if (!Sprite::init()) {
		return false;
	}

	customer = SpriteFrame::create("customer/customer.png", Rect(0, 0, 90, 110));
	health = life;

	if (!customer) {
		CCLOG("Error: No se pudo cargar player");
		return false;
	}

	this->setSpriteFrame(customer);

	defaultAnimation();
	punchAnimation();
	moveAnimation();
	throwAnimation();
	kickAnimation();

	return true;
}

void Customer::defaultAnimation() {
	auto c1 = SpriteFrame::create("customer/customer.png", Rect(0, 0, 90, 110));
	customerData[c1].insert(std::pair<float, float>(54, 81));
	customerData[c1].insert(std::pair<float, float>(51, 61));
	customerTags[c1] = "c1";

	auto c2 = SpriteFrame::create("customer/customerDefault.png", Rect(0, 0, 90, 110));
	customerData[c2].insert(std::pair<float, float>(54, 80));
	customerData[c2].insert(std::pair<float, float>(51, 60));
	customerTags[c2] = "c2";

	defaultVector.pushBack(c1);
	defaultVector.pushBack(c2);

	auto cAnimation = Animation::createWithSpriteFrames(defaultVector, 0.20f);
	defaultAnimate = Animate::create(cAnimation);
	defaultAnimate->retain();

}

void Customer::punchAnimation() {
	auto punchCustomer = SpriteFrame::create("customer/customerPunch.png", Rect(0, 0, 90, 110));
	customerData[punchCustomer].insert(std::pair<float, float>(51, 60));
	customerAttack[punchCustomer].first = 28;
	customerAttack[punchCustomer].second = 72;
	customerTags[punchCustomer] = "punchCustomer";

	punchVector.pushBack(punchCustomer);

	auto pchAnimation = Animation::createWithSpriteFrames(punchVector, 0.40f);
	punchAnimate = Animate::create(pchAnimation);
	punchAnimate->retain();

}

void Customer::moveAnimation() {
	auto moveCustomer = SpriteFrame::create("customer/customerMove.png", Rect(0, 0, 90, 110));
	customerData[moveCustomer].insert(std::pair<float, float>(54, 80));
	customerData[moveCustomer].insert(std::pair<float, float>(51, 60));
	customerTags[moveCustomer] = "moveCustomer";

	moveVector.pushBack(moveCustomer);

	auto mvAnimation = Animation::createWithSpriteFrames(moveVector, 0.20f);
	moveAnimate = Animate::create(mvAnimation);
	moveAnimate->retain();

}

void Customer::throwAnimation() {
	auto prep = SpriteFrame::create("customer/customerPrep.png", Rect(0, 0, 90, 110));
	customerData[prep].insert(std::pair<float, float>(54, 80));
	customerData[prep].insert(std::pair<float, float>(51, 60));
	customerTags[prep] = "prep";

	auto thr = SpriteFrame::create("customer/customerThrow.png", Rect(0, 0, 90, 110));
	customerTags[thr] = "thr";

	throwVector.pushBack(prep);
	throwVector.pushBack(thr);

	auto thrAnimation = Animation::createWithSpriteFrames(throwVector, 0.05f);
	throwAnimate = Animate::create(thrAnimation);
	throwAnimate->retain();

}

void Customer::kickAnimation() {
	auto c1 = SpriteFrame::create("customer/customer.png", Rect(0, 0, 90, 110));
	customerData[c1].insert(std::pair<float, float>(54, 81));
	customerData[c1].insert(std::pair<float, float>(51, 61));

	auto kick = SpriteFrame::create("customer/customerKick.png", Rect(0, 0, 90, 110));
	customerAttack[kick].first = 29;
	customerAttack[kick].second = 57;
	customerTags[kick] = "kick";

	kickVector.pushBack(c1);
	kickVector.pushBack(kick);

	auto kckAnimation = Animation::createWithSpriteFrames(kickVector, .40f);
	kickAnimate = Animate::create(kckAnimation);
	kickAnimate->retain();

}

void Customer::againDefault(cocos2d::Animate* temp) {
	auto delay = DelayTime::create(temp->getDuration());
	auto revert = CallFunc::create([=]() {
		runDefaultAnimation();
		});

	this->runAction(Sequence::create(delay, revert, nullptr));
}

void Customer::runDefaultAnimation() {
	if (defaultAnimate) {
		auto action = cocos2d::RepeatForever::create(defaultAnimate);
		this->runAction(action);
	}
}

void Customer::runPunchAnimation() {
	if (punchAnimate) {
		this->stopAllActions();
		this->runAction(punchAnimate);

		againDefault(punchAnimate);
	}
}

void Customer::runKickAnimation() {
	if (kickAnimate) {
		this->stopAllActions();
		this->runAction(kickAnimate);

		againDefault(kickAnimate);
	}
}

void Customer::runThrowAnimation() {
	if (throwAnimate) {
		this->stopAllActions();
		this->runAction(throwAnimate);

		againDefault(throwAnimate);
	}
}

void Customer::runMoveRightAnimation() {
	if (moveAnimate || !isMovingRight) {
		isMovingRight = true;
		this->stopAllActions();
		this->runAction(moveAnimate);

		auto move = MoveBy::create(0.1f, Vec2(-15, 0));
		auto finish = CallFunc::create([this]() {
			isMovingRight = false;
			});

		this->runAction(Sequence::create(move, finish, nullptr));

		againDefault(moveAnimate);
	}
}

void Customer::runMoveLeftAnimation() {
	if (moveAnimate || !isMovingLeft) {
		isMovingLeft = true;
		this->stopAllActions();
		this->runAction(moveAnimate);

		auto move = MoveBy::create(0.1f, Vec2(15, 0));
		auto finish = CallFunc::create([this]() {
			isMovingLeft = false;
			});

		this->runAction(Sequence::create(move, finish, nullptr));

		againDefault(moveAnimate);
	}
}

cocos2d::SpriteFrame* Customer::getSprite() const {
	return customer;
}

float Customer::getLife() {
	return life;
}

void Customer::setLife(float life) {
	this->life = life;
}

float Customer::getStrength() {
	return strength;
}

void Customer::setStrength(float strng) {
	this->strength = strng;
}

float Customer::getBottleAt() {
	return botAt;
}

void Customer::setBottleAt(float bA) {
	this->botAt = bA;
}