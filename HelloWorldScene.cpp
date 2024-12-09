#include "HelloWorldScene.h"
#include "MainMenu.h"
#include "LevelFinal.h"
#include "Level4.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::nextScene), 1);

    auto sprite = Sprite::create("Logo.png");
    if (sprite == nullptr)
    {
        problemLoading("'Logo.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    return true;
}


void HelloWorld::nextScene(float delta)
{
    auto next_scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, next_scene));

}
