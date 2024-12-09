#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "cocos2d.h"
#include "Player.h"
#include "girlfriend.h"
#include "vector"
#include "string"

class Level2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Level2);

    //Vector<std::string>attacks;

    std::vector<std::string> attacksStr;

    bool movePlayer = true;
    bool oneTime = false;
    float speed = 1.0f;
    float cont = 0.0f;

    void checkCont();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void endLevel();
    void upCont();

    void pause(cocos2d::Ref* pSender);

private:
    Player* player;
    Girlfriend* girlfriend;

    bool Paused = false;
    
    void createPlayer();
    void createGirlfriend();
    void player_events(float);
    
    void check(cocos2d::Vec2);
    void checkAttacks();
    void labelAttack();

};

#endif // __LEVEL2_H__
