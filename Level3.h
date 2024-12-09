#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include "cocos2d.h"
#include "Player.h"
#include "girlfriend.h"

class Level3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(Level3);
    void update(float);
    
    cocos2d::Sprite* moto;
    cocos2d::Sprite* enemy;
    cocos2d::Sprite* bg;

    bool right = false;
    bool left = false;
    bool up = false;
    bool down = false;

    float speed = 1.0f;

    bool enable = true;

    void checkMove(float);
    void checkCollision(cocos2d::Vec2);


};

#endif // __LEVEL2_H__
