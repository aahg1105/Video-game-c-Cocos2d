#ifndef __LEVEL4_H__
#define __LEVEL4_H__

#include "cocos2d.h"
#include "Player.h"
#include "Secta.h"
#include "Leader.h"
#include "vector"
#include "string"

class Level4 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Level4);

    bool movePlayer = true;
    bool oneTime = false;
    float speed = 1.0f;

    void menuCloseCallback(cocos2d::Ref* pSender);

private:
    Player* player;
    Secta* sect;
    Leader* leader;
    
    void createPlayer();
    void createSect();
    void createLeader();
    void player_events(float);
    
    void check();
    void checkLife();
    void leaderAttacks();
    void sectAttack();

};

#endif // __LEVEL2_H__
