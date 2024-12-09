#ifndef __SECTA_H__
#define __SECTA_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Secta : public cocos2d::Sprite
{
private:
	float life, shadow, attack;

	cocos2d::SpriteFrame* sect;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> attackVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> superVector;

	cocos2d::Animate* defaultAnimate;
	cocos2d::Animate* attackAnimate;
	cocos2d::Animate* superAnimate;

	void defaultAnimation();
	void attackAnimation();
	void superAnimation();

	void againDefault(cocos2d::Animate*);

public:

	Secta();
	~Secta();

	virtual bool init();
	CREATE_FUNC(Secta);

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> sectData;
	std::map<cocos2d::SpriteFrame*, std::string> secttags;

	void runDefaultAnimation();
	void runAttackAnimation();
	void runSuperAnimation();

	float getLive() const;
	void setLive(float lives);

	float getShadow() const;

	float getAttack() const;

	cocos2d::SpriteFrame* getSprite() const;
};

#endif // __PLAYER_H__
