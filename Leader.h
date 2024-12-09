#ifndef __LEADER_H__
#define __LEADER_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Leader : public cocos2d::Sprite
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float life, attack, heal, superA;

	cocos2d::SpriteFrame* leader;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> attackVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> superVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> healVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> teleVector;

	cocos2d::Animate* defaultAnimate;
	cocos2d::Animate* attackAnimate;
	cocos2d::Animate* superAnimate;
	cocos2d::Animate* healAnimate;
	cocos2d::Animate* teleAnimate;

	void defaultAnimation();
	void attackAnimation();
	void superAnimation();
	void healAnimation();

	void againDefault(cocos2d::Animate*);

public:

	Leader();
	~Leader();

	virtual bool init();
	CREATE_FUNC(Leader);

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> leaderData;
	std::map<cocos2d::SpriteFrame*, std::string> leadertags;

	void runDefaultAnimation();
	void runAttackAnimation();
	void runSuperAnimation();
	void runHealAnimation();

	float getLive() const;
	void setLive(float lives);

	float getHeal() const;

	float getSuperA() const;

	float getAttack() const;

	cocos2d::SpriteFrame* getSprite() const;
};

#endif // __PLAYER_H__
