#include "Ending.h"
#include "MainMenu.h"
#include "LevelFinal.h"
#include "Level4.h"

USING_NS_CC;

Scene* Ending::createScene()
{
    return Ending::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Ending::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

    auto label = Label::createWithTTF("THE END", "fonts/Marker Felt.ttf", 20);
    label->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2-40));
    this->addChild(label);

    return true;
}
