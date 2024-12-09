#include "Level2.h"
#include "Level3.h"
#include <cstdlib>
#include <random>

USING_NS_CC;

Scene* Level2::createScene()
{
    return Level2::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Level2::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    srand((unsigned)time(NULL));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("Level2.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(5, -50));
    this->addChild(bg, -1);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Level2::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto pauseItem = MenuItemImage::create(
        "PauseNormal.png",
        "PauseSelected.png",
        CC_CALLBACK_1(Level2::pause, this));

    float pause_x = origin.x + visibleSize.width / 2;
    float pause_y = visibleSize.height;
    pauseItem->setPosition(Vec2(pause_x, pause_y));

    auto pause_menu = Menu::create(pauseItem, NULL);
    pause_menu->setPosition(Vec2::ZERO);
    this->addChild(pause_menu, 1);

    createPlayer();
    createGirlfriend();
    this->schedule(CC_SCHEDULE_SELECTOR(Level2::player_events), .10f);

    
    attacksStr.push_back("I miss u");
    attacksStr.push_back("Kiss me");
    attacksStr.push_back("I need u");
    attacksStr.push_back("I love u");

    this->schedule([this](float delta) {
        checkAttacks();
        }, 7.0f, "check_distance");

    this->scheduleOnce([this](float) {
        endLevel();
        }, 60.0f, "end");

    this->schedule([this](float delta) {
        upCont();
        }, 24.0f, "cont");

    this->schedule([this](float delta) {
        labelAttack();
        checkCont();
        }, 2.0f, "labels");

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void Level2 :: upCont() {
    speed-=.15f;
}

void Level2::pause(Ref* pSender) {
    if (!Paused) {
        Director::getInstance()->pause();
        Paused = true;
    }
    else {
        Director::getInstance()->resume();
        Paused = false;
    }
}

void Level2::checkCont() {
    if (cont >= 5) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        this->stopAllActions();

        auto delay = DelayTime::create(0.1f);

        this->runAction(Sequence::create(
            CallFunc::create([this,visibleSize]() {
                auto label = Label::createWithTTF("YOU LOST", "fonts/Marker Felt.ttf", 40);
                label->setTextColor(Color4B::RED);
                label->setPosition(Vec2(190, visibleSize.height));
                }), delay,
            CallFunc::create([this]() {
                auto scene = Level2::createScene();
                auto transition = TransitionFade::create(1.0f, scene, Color3B::BLACK);
                Director::getInstance()->replaceScene(transition);
                }),
            nullptr
        ));

    }
}

void Level2::labelAttack() {
    if (player && girlfriend) {
        oneTime = false;
        auto delay = DelayTime::create(.7f);

        int n = random(0, 3);
        std::string name;
        
        if (n == 0) {
            name = attacksStr[0];
            
        }
        else if (n == 1) {
            name = attacksStr[1];
        }
        else if (n == 2) {
            name = attacksStr[2];
        }
        else if (n == 3) {
            name = attacksStr[3];
        }

        CCLOG("chi");

        auto Lattack = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 10);
        Lattack->setTextColor(Color4B::RED);
        Lattack->setPosition(Vec2(girlfriend->getPositionX() - 10, 120));
        this->addChild(Lattack);

        auto lPoint = Node::create();
        lPoint->setPosition(Vec2(5, 7));
        lPoint->setVisible(true);
        lPoint->retain();
        Lattack->addChild(lPoint);

        movePlayer = false;

        auto moveBottle = MoveTo::create(speed, Vec2(player->getPositionX() + 20, 103));
        Lattack->runAction(Sequence::create(
            moveBottle,
            CallFunc::create([this, lPoint, Lattack]() {
                if (lPoint && lPoint->getParent()) {
                    Vec2 globalPoint = lPoint->convertToWorldSpace(Vec2::ZERO);
                    //CCLOG("Global Point Position: (%f, %f)", globalPoint.x, globalPoint.y);
                    check(globalPoint);
                }
                }),
            CallFunc::create([this, Lattack]() {
                this->removeChild(Lattack);
                movePlayer = true;
                oneTime = false;
                }),
            nullptr
        ));
    }
}

void Level2::checkAttacks() {
    if (player && girlfriend) {
        oneTime = true;
        int n = random(0, 1);

        if (n == 0) {
            auto delay = DelayTime::create(.7f);

            auto bottle = Sprite::create("girlfriend/Notebook.png");
            bottle->setPosition(Vec2(girlfriend->getPositionX() - 10, 120));
            this->addChild(bottle);

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(5, 8));
            pPoint->setVisible(true);
            pPoint->retain();
            bottle->addChild(pPoint);

            movePlayer = false;

            auto moveBottle = MoveTo::create(speed, Vec2(player->getPositionX() + 20, 103));
            bottle->runAction(Sequence::create(
                moveBottle,
                CallFunc::create([this, pPoint, bottle]() {
                    if (pPoint && pPoint->getParent()) {
                        Vec2 globalPoint = pPoint->convertToWorldSpace(Vec2::ZERO);
                        //CCLOG("Global Point Position: (%f, %f)", globalPoint.x, globalPoint.y);
                        check(globalPoint);
                    }
                    }),
                CallFunc::create([this, bottle]() {
                    this->removeChild(bottle);
                    movePlayer = true;
                    oneTime = false;
                    }),
                nullptr
            ));
        }
        else if (n == 1) {
            auto delay = DelayTime::create(.7f);

            auto bottle = Sprite::create("girlfriend/Lamp.png");
            bottle->setPosition(Vec2(girlfriend->getPositionX() - 10, 120));
            this->addChild(bottle);

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(5, 8));
            pPoint->setVisible(true);
            pPoint->retain();
            bottle->addChild(pPoint);

            movePlayer = false;

            auto moveBottle = MoveTo::create(speed, Vec2(player->getPositionX() + 20, 103));
            bottle->runAction(Sequence::create(
                moveBottle,
                CallFunc::create([this, pPoint, bottle]() {
                    if (pPoint && pPoint->getParent()) {
                        Vec2 globalPoint = pPoint->convertToWorldSpace(Vec2::ZERO);
                        //CCLOG("Global Point Position: (%f, %f)", globalPoint.x, globalPoint.y);
                        check(globalPoint);
                    }
                    }),
                CallFunc::create([this, bottle]() {
                    this->removeChild(bottle);
                    movePlayer = true;
                    }),
                nullptr
            ));
        }
    }
}

void Level2::menuCloseCallback(Ref* pSender)
{
    auto next_scene = Level3::createScene();
    Director::getInstance()->pushScene(next_scene);
    CCLOG("change");

}

void Level2::check(cocos2d::Vec2 tempo) {
    float tolerance = 5.0f;
    auto current = player->getSpriteFrame();
    Vec2 local = player->convertToNodeSpace(tempo);

    for (auto element : player->playerData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        if (hit <= tolerance) {
            //Director::getInstance()->pause();
            
            player->runHurtAnimation();
            cont += 1;
            //player->playerTakeDamage(enemy->getBottleAt());

            auto delay = DelayTime::create(.7f);

            CCLOG("Bottle: (%f)", player->getLife());
            CCLOG("Colision");
            return;
        }
    }

    CCLOG("No colision");
}

void Level2::endLevel() {
    auto nextScene = Level3::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, nextScene));
}

void Level2::createPlayer() {
    player = Player::create();
    if (!player) {
        CCLOG("Error: No se pudo crear el jugador.");
        return;
    }

    player->setPosition(Vec2(30, 100));
    this->addChild(player);

    player->runDefaultAnimation();
}

void Level2::createGirlfriend() {
    girlfriend = Girlfriend::create();
    if (!girlfriend) {
        CCLOG("Error: No se pudo crear el enemigo.");
        return;
    }

    girlfriend->setPosition(Vec2(400, 105));
    this->addChild(girlfriend);

    girlfriend->runDefaultAnimation();
}

void Level2::player_events(float delta) {
    auto event = EventListenerKeyboard::create();
    event->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
            if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
                player->runJumpAnimation();
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
                if (!movePlayer) return;
                player->runMoveRightAnimation();
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
                if (!movePlayer) return;
                player->runMoveLeftAnimation();
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
                player->runBlockAnimation();
            }
        };

    event->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            if (!movePlayer) return;
            player->isMovingRight = false;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            if (!movePlayer) return;
            player->isMovingLeft = false;
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
}