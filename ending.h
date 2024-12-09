#ifndef __ENDING_H__
#define __ENDING_H__

#include "cocos2d.h"

class Ending : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ending);
private:
    void nextScene(float delta);
};

#endif // __HELLOWORLD_SCENE_H__
