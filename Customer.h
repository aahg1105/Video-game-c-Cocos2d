#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Customer : public cocos2d::Sprite
{
private:
	float life, bottles, strength, botAt, health;
	cocos2d::SpriteFrame* customer;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> punchVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> moveVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> throwVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> kickVector;

	cocos2d::Animate* defaultAnimate;
	cocos2d::Animate* punchAnimate;
	cocos2d::Animate* moveAnimate;
	cocos2d::Animate* throwAnimate;
	cocos2d::Animate* kickAnimate;

	void defaultAnimation();
	void punchAnimation();
	void moveAnimation();
	void throwAnimation();
	void kickAnimation();

	void againDefault(cocos2d::Animate*);

public:
	Customer();
	~Customer();

	virtual bool init();
	CREATE_FUNC(Customer);

	bool isMovingRight = false;
	bool isMovingLeft = false;

	cocos2d::ProgressTimer* customerHealthBar;

	void customerTakeDamage(float);

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> customerData;
	std::map<cocos2d::SpriteFrame*, std::pair<float, float>> customerAttack;
	std::map<cocos2d::SpriteFrame*, std::string> customerTags;

	void runDefaultAnimation();
	void runPunchAnimation();
	void runMoveRightAnimation();
	void runMoveLeftAnimation();
	void runThrowAnimation();
	void runKickAnimation();

	cocos2d::SpriteFrame* getSprite() const;

	float getLife();
	void setLife(float);

	float getStrength();
	void setStrength(float);

	float getBottleAt();
	void setBottleAt(float);
};

#endif // __CUSTOMER_H__
