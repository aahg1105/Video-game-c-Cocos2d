#include "HelloWorldScene.h"
#include "MainMenu.h"
#include "Level1.h"
#include "LevelFinal.h"


USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("Menu.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(5, 30));
    this->addChild(bg, -1);

    
    auto item1 = MenuItemFont::create("PLAY", CC_CALLBACK_1(MainMenu::Play, this));
    //auto item2 = MenuItemFont::create("Continue", CC_CALLBACK_1(MainMenu::Continue, this));
    //auto item3 = MenuItemFont::create("Tutorial", CC_CALLBACK_1(MainMenu::Tutorial, this));

    auto menu = Menu::create(item1, NULL);

    menu->alignItemsHorizontally();
    this->addChild(menu);
    

    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    auto next_scene = Level1::createScene();
    Director::getInstance()->pushScene(next_scene);

}

void MainMenu::Play(cocos2d::Ref* pSender) {
    auto scene = Level1::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenu::Continue(cocos2d::Ref* pSender) {
    auto scene = Level1::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenu::Tutorial(cocos2d::Ref* pSender) {
    auto scene = Level1::createScene();
    Director::getInstance()->pushScene(scene);
}

