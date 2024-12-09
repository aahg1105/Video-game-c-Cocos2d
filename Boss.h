#ifndef __BOSS_H__
#define __BOSS_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Boss : public cocos2d::Sprite
{
private:
	float life, strength, bullet, shadow;

	cocos2d::SpriteFrame* boss;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector; //
	cocos2d::Vector<cocos2d::SpriteFrame*> attackVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> kickVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> fireVector; //
	cocos2d::Vector<cocos2d::SpriteFrame*> magicVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> QVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> moveVector; //
	cocos2d::Vector<cocos2d::SpriteFrame*> superVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> chargeVector;

	cocos2d::Animate* defaultAnimate; //
	cocos2d::Animate* attackAnimate; //
	cocos2d::Animate* kickAnimate; //
	cocos2d::Animate* fireAnimate; //
	cocos2d::Animate* magicAnimate; //
	cocos2d::Animate* QAnimate; //
	cocos2d::Animate* moveAnimate; //
	cocos2d::Animate* superAnimate; 
	cocos2d::Animate* chargeAnimate;

	void defaultAnimation(); //
	void attackAnimation(); //
	void moveAnimation(); //
	void fireAnimation(); //
	void kickAnimation(); //
	void magicAnimation(); //
	void QAnimation(); //
	void superAnimation();
	void chargeAnimation();

	void againDefault(cocos2d::Animate*);

public:

	Boss();
	~Boss();

	virtual bool init();
	CREATE_FUNC(Boss);

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> bossData;
	std::map<cocos2d::SpriteFrame*, std::string> bossTags;

	void runDefaultAnimation(); //
	void runAttackAnimation(); //
	void runMoveAnimation(); //
	void runFireAnimation(); //
	void runKickAnimation(); //
	void runMagicAnimation(); //
	void runQAnimation();
	void runSuperAnimation();
	void runChargeAnimation();

	float getLife() const;
	void setLife(float);

	float getStrength() const;
	void setStrength(float);

	float getShadow() const;
	void setShadow(float);

	float getBullet() const;
	void setBullet(float);

	cocos2d::SpriteFrame* getSprite() const;
};

#endif // __PLAYER_H__
