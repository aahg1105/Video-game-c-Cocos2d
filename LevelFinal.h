#ifndef __LEVELFINAL_H__
#define __LEVELFINAL_H__

#include "cocos2d.h"
#include "Player.h"
#include "Boss.h"
#include "set"

class LevelFinal : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LevelFinal);

    bool movePlayer = true;
    bool left = true;
    bool right = true;
    float globalDistance;
    bool cont = 0;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void pause(cocos2d::Ref* pSender);

    void damage(int, int);
    void updateHealthBar();
    void setupHealthBar();

    cocos2d::Sprite* bullet;

private:
    Player* player;
    Boss* enemy;

    bool Paused = false;
    bool isTPressed = false;
    bool superPower = false;
    
    void createPlayer();
    void createEnemy();

    void check(cocos2d::Vec2);
    void boxes(cocos2d::Vec2);

    void checkLife();

    void checkDistance();
    void especialPower();
    
    void playerCollisions(float);
    void enemyCollisions(float);

    void playerMovements();

    void player_events(float);
    
};

#endif // __LEVEL5_H__
