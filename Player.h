#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Player : public cocos2d::Sprite
{
private:
	float life, boxes, bottles, strength, boxAt, botAt, health;
	std::string power;
	std::string name;

	cocos2d::SpriteFrame* player;

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
	cocos2d::Animate* objectAnimate;
	cocos2d::Animate* defaultPowerAnimate;
	cocos2d::Animate* attackAnimate;
	cocos2d::Animate* hurtAnimate;


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

	void animating();

public:
	Player();
	~Player();

	virtual bool init();
	CREATE_FUNC(Player);

	bool superP = false;
	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isBlock = false;

	cocos2d::ProgressTimer* healthBar;
	

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> playerData;
	std::map<cocos2d::SpriteFrame*, std::pair<float, float>> playerAttack;
	std::map<cocos2d::SpriteFrame*, std::string> tags;

	void runDefaultAnimation();
	void runPunchAnimation();
	void runBlockAnimation();
	void runJumpAnimation();
	void runDuckAnimation();
	void runMoveRightAnimation();
	void runMoveLeftAnimation();
	void runChargeAnimation();
	void runDefaultPowerAnimation();
	void runAttackAnimation(float,float);
	void runObjectAnimation();
	void runHurtAnimation();

	void playerTakeDamage(float);

	void againDefault(cocos2d::Animate*);

	cocos2d::SpriteFrame* getSprite() const;

	cocos2d::Animate* getBlockAnimate() const;

	float getLife();
	void setLife(float);

	float getStrength();
	void setStrength(float);

	std::string getName();
	void setName(std::string);

	std::string getPower();
	void setPower(std::string);

	float getBoxAt() const;
	void setBoxAt(float);

	void setSuperP(bool);
};

#endif // __PLAYER_H__
