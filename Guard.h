#ifndef __GUARD_H__
#define __GUARD_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Guard : public cocos2d::Sprite
{
private:
	float life, attack, bullet;

	cocos2d::SpriteFrame* guard;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> punchRightVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> punchLeftVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> moveVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> fireVector;

	cocos2d::Animate* defaultAnimate;
	cocos2d::Animate* punchRightAnimate;
	cocos2d::Animate* punchLeftAnimate;
	cocos2d::Animate* moveAnimate;
	cocos2d::Animate* fireAnimate;

	void defaultAnimation();
	void punchRightAnimation();
	void punchLeftAnimation();
	void moveAnimation();
	void fireAnimation();

	void againDefault(cocos2d::Animate*);

public:

	Guard();
	~Guard();

	virtual bool init();
	CREATE_FUNC(Guard);

	std::map<cocos2d::SpriteFrame*, std::set<std::pair<float, float>>> guardData;
	std::map<cocos2d::SpriteFrame*, std::string> customerTags;

	void runDefaultAnimation();
	void runPunchRightAnimation();
	void runPunchLeftAnimation();
	void runMoveAnimation();
	void runFireAnimation();

	float getLive() const;
	void setLive(float);

	float getAttack() const;
	void setAttack(float);

	float getBullet() const;
	void setBullet(float);

	cocos2d::SpriteFrame* getSprite() const;
};

#endif // __PLAYER_H__
