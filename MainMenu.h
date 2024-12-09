#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

    void Play(Ref* pSender);
    void Tutorial(Ref* pSender);
    void Continue(Ref* pSender);
    
};

#endif // __HELLOWORLD_SCENE_H__
