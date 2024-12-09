#ifndef __LEVEL5_H__
#define __LEVEL5_H__

#include "cocos2d.h"
#include "Player.h"
#include "Guard.h"
#include "set"

class Level5 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Level5);

    bool movePlayer = true;
    bool left = true;
    bool right = true;
    float globalDistance;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void pause(cocos2d::Ref* pSender);

    void damage(int, int);
    void updateHealthBar();
    void setupHealthBar();

    cocos2d::Sprite* bullet;

private:
    Player* player;
    Guard* enemy;

    bool Paused = false;
    bool isTPressed = false;
    bool superPower = false;
    
    void createPlayer();
    void createEnemy();

    void checkLife();
    void superPowerFunc();

    void check(cocos2d::Vec2);
    void boxes(cocos2d::Vec2);

    void checkDistance();
    
    void playerCollisions(float);
    void enemyCollisions(float);

    void playerMovements();

    void player_events(float);
    
};

#endif // __LEVEL5_H__
