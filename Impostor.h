#ifndef __IMPOSTOR_H__
#define __IMPOSTOR_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Impostor : public cocos2d::Sprite
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float life, boxes, strength, boxAt, botAt, health;

	bool superP = false;

	cocos2d::SpriteFrame* impostorS;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> punchVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> blockVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> jumpVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> duckVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> moveVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> chargeVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> defaultPowerVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> attackVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> hurtVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> objectVector;

	cocos2d::Animate* defaultAnimate;
	cocos2d::Animate* punchAnimate;
	cocos2d::Animate* blockAnimate;
	cocos2d::Animate* jumpAnimate;
	cocos2d::Animate* duckAnimate;
	cocos2d::Animate* moveAnimate;
	cocos2d::Animate* chargeAnimate;
	cocos2d::Animate* defaultPowerAnimate;
	cocos2d::Animate* attackAnimate;
	cocos2d::Animate* hurtAnimate;
	cocos2d::Animate* objectAnimate;

	void defaultAnimation();
	void punchAnimation();
	void blockAnimation();
	void jumpAnimation();
	void duckAnimation();
	void moveAnimation();
	void chargeAnimation();
	void defaultPowerAnimation();
	void attackAnimation();
	void objectAnimation();
	void hurtAnimation();

	void againDefault(cocos2d::Animate*);

public:

	Impostor();
	~Impostor();

	virtual bool init();
	CREATE_FUNC(Impostor);

	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isBlock = false;

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> impostorData;
	std::map<cocos2d::SpriteFrame*, std::string> tagsI;

	void runDefaultAnimation();
	void runPunchAnimation();
	void runBlockAnimation();
	void runJumpAnimation();
	void runDuckAnimation();
	void runMoveRightAnimation();
	void runMoveLeftAnimation();
	void runChargeAnimation();
	void runDefaultPowerAnimation();
	void runAttackAnimation(float, float);
	void runObjectAnimation();
	void runHurtAnimation();

	float getLife() const;
	void setLife(float);

	float getBoxes() const;
	void setBoxes(float);

	float getStrength();
	void setStrength(float);

	float getBoxAt() const;
	void setBoxAt(float);

	cocos2d::SpriteFrame* getSprite() const;

};

#endif // __IMPOSTOR_H__
