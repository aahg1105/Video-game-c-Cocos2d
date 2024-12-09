#ifndef __GIRLFRIEND_H__
#define __GIRLFRIEND_H__

#include "cocos2d.h"
#include "string.h"
#include <unordered_map>
#include <set>
#include "iostream"

class Girlfriend : public cocos2d::Sprite
{
private:
	cocos2d::SpriteFrame* girlfriend;

	cocos2d::Vector<cocos2d::SpriteFrame*> defaultVector;

	cocos2d::Animate* defaultAnimate;

	void defaultAnimation();
	
	void againDefault(cocos2d::Animate*);

public:
	Girlfriend();
	~Girlfriend();

	virtual bool init();
	CREATE_FUNC(Girlfriend);

	int life;

	void runDefaultAnimation();
	
	cocos2d::SpriteFrame* getSprite() const;

};

#endif // __PLAYER_H__
