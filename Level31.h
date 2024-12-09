#ifndef __LEVEL31_H__
#define __LEVEL31_H__

#include "cocos2d.h"
#include "Player.h"
#include "Impostor.h"

class Level31 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    bool movePlayer = true;
    bool left = true;
    bool right = true;

    void pause(cocos2d::Ref* pSender);
    void checkLife();

    cocos2d::Sprite* box;

    CREATE_FUNC(Level31);

    void menuCloseCallback(cocos2d::Ref* pSender);
private:
    Player* player;
    Impostor* impostor;

    bool isTPressed = false;
    bool superPower = false;
    bool Paused = false;

    void playerCollisions(float);
    void enemyCollisions(float);

    void playerMovements();
    void checkDistance();
    
    void superPowerFunc();
    void enemySuper();

    void boxes(cocos2d::Vec2);
    void check(cocos2d::Vec2);

    void createPlayer();
    void createImpostor();
    void player_events(float);
    
};

#endif // __LEVEL31_H__
