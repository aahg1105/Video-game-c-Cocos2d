#include "LevelFinal.h"
#include "Level2.h"
#include "ending.h"
#include <cstdlib>


USING_NS_CC;

Scene* LevelFinal::createScene()
{
    return LevelFinal::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LevelFinal::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    //delay
    srand((unsigned)time(NULL));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    std::string po1 = "extra life";
    std::string po2 = "healing";

    auto bg = Sprite::create("Level5.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(5, -50));
    this->addChild(bg, -1);

    createPlayer();
    createEnemy();
    this->schedule(CC_SCHEDULE_SELECTOR(LevelFinal::player_events), .10f);

    int n = rand() % (2 - 1 + 1) + 1;
    if (n == 1) {
        player->setPower(po1);
    }
    else if (n == 2) {
        player->setPower(po2);
    }

    this->schedule([this](float delta) {
        especialPower();
        }, 5.0f, "special");

    this->schedule([this](float delta) {
        checkDistance();
        }, 2.0f, "check_distance");

    this->schedule([this](float delta) {
        checkLife();
        }, 1.0f, "check_lif");

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(LevelFinal::menuCloseCallback, this));

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
        CC_CALLBACK_1(LevelFinal::pause, this)
    );

    float pause_x = origin.x + visibleSize.width / 2;
    float pause_y = visibleSize.height;
    pauseItem->setPosition(Vec2(pause_x, pause_y));

    auto pause_menu = Menu::create(pauseItem, NULL);
    pause_menu->setPosition(Vec2::ZERO);
    this->addChild(pause_menu,1);

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void LevelFinal::checkLife() {
    if (player->getLife() <= 0) {
        auto next_scene = LevelFinal::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
    else if (enemy->getLife() <= 0) {
        auto next_scene = Ending::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
}

void LevelFinal::createPlayer() {
    player = Player::create();
    if (!player) {
        CCLOG("Error: No se pudo crear el jugador.");
        return;
    }

    player->setPosition(Vec2(40, 95));
    this->addChild(player);

    player->runDefaultAnimation();
    
}

void LevelFinal::createEnemy() {
    enemy = Boss::create();
    if (!enemy) {
        CCLOG("Error: No se pudo crear el enemigo.");
        return;
    }

    enemy->setPosition(Vec2(420, 107));
    this->addChild(enemy);

    enemy->runDefaultAnimation();
}

void LevelFinal::menuCloseCallback(Ref* pSender)
{
    auto next_scene = Level2::createScene();
    Director::getInstance()->pushScene(next_scene);
    CCLOG("change");

}

void LevelFinal::pause(Ref* pSender) {
    if (!Paused) {
        Director::getInstance()->pause();
        Paused = true;
    }
    else {
        Director::getInstance()->resume();
        Paused = false;
    }
}

void LevelFinal::especialPower() {
    if (player->getPower() == "healing") {
        player->setLife(player->getLife() + 15.0f);
    }
    else if (player->getPower() == "extra life") {
        if (player->getLife() <= 0 && cont ==0.0f) {
            player->setLife(100.0f);
        }
    }
}

void LevelFinal::checkDistance() {
    if (player && enemy) {
        float distance = player->getPosition().distance(enemy->getPosition());
        CCLOG("Distance between player and enemy: %f", distance);

        if (distance > 100.0f) {
            int n = rand() % (2 - 1 + 1) + 1;
            if (n == 1) {
                enemy->runFireAnimation();

                auto delay = DelayTime::create(.7f);

                auto bottle = Sprite::create("bullet.png");
                bottle->setPosition(Vec2(enemy->getPositionX() - 10, 120));
                this->addChild(bottle);

                auto pPoint = Node::create();
                pPoint->setPosition(Vec2(5, 8));
                pPoint->setVisible(true);
                pPoint->retain();
                bottle->addChild(pPoint);

                movePlayer = false;

                auto moveBottle = MoveTo::create(1.0f, Vec2(player->getPositionX() + 20, 103));
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
                        enemy->runMoveAnimation();
                        }),
                    nullptr
                ));
            }
            else if (n == 2) {
                enemy->runMagicAnimation();

                auto delay = DelayTime::create(.7f);

                auto bottle = Sprite::create("Fantasma.png");
                bottle->setPosition(Vec2(enemy->getPositionX() - 15.0f, 120.0f));
                this->addChild(bottle);

                auto pPoint = Node::create();
                pPoint->setPosition(Vec2(30, 50));
                pPoint->setVisible(true);
                pPoint->retain();
                bottle->addChild(pPoint);

                movePlayer = false;

                auto moveBottle = MoveTo::create(1.0f, Vec2(player->getPositionX() + 20, 103));
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
                        enemy->runMoveAnimation();
                        }),
                    nullptr
                ));
            }
        }
        else if (distance < 40.0f) {
            int n = rand() % (2 - 1 + 1) + 1;
            if (n == 1) {
                this->reorderChild(player, 1);
                this->reorderChild(enemy, 2);
                enemy->runAttackAnimation();
                this->schedule(CC_SCHEDULE_SELECTOR(LevelFinal::enemyCollisions), .10f);
            }
            else if (n == 2) {
                this->reorderChild(player, 1);
                this->reorderChild(enemy, 2);
                enemy->runKickAnimation();
                this->schedule(CC_SCHEDULE_SELECTOR(LevelFinal::enemyCollisions), .10f);
            }
        }
        else if (distance >= 40.0f && distance <= 100.0f) {
            enemy->runMoveAnimation();
        }
    }
}

void LevelFinal::playerMovements() {
    float playerX = player->getPositionX();
    float enemyX = enemy->getPositionX();

    if (playerX < 30.0f) {
        player->setPositionX(30.0f);
        left = false;
        movePlayer = false;
    }
    else if (playerX >= enemyX-22.0f) {
        player->setPositionX(enemyX - 25.0f);
    }
}

void LevelFinal::enemyCollisions(float delta) {
    auto playerCurrent = player->getSpriteFrame();
    auto enemyCurrent = enemy->getSpriteFrame();

    if ((enemy->bossTags[enemyCurrent] == "attackB" || enemy->bossTags[enemyCurrent] == "kickB") && ((player->tags[playerCurrent] != "block") || (player->tags[playerCurrent] != "duck"))) {
        player->setLife(player->getLife() - enemy->getStrength());
        CCLOG("Life K: (%f)", player->getLife());
        player->runHurtAnimation();

        this->unschedule(CC_SCHEDULE_SELECTOR(LevelFinal::enemyCollisions));
    }
}

void LevelFinal::playerCollisions(float delta) {
    auto playerCurrent = player->getSpriteFrame();
    auto enemyCurrent = enemy->getSpriteFrame();
    float distance = player->getPosition().distance(enemy->getPosition());

    if (player->tags[playerCurrent] == "punch" && (distance<40.0f)) {
        enemy->setLife(enemy->getLife() - player->getStrength());
        
        Color3B color = enemy->getColor();

        auto delay = DelayTime::create(0.1f);

        enemy->runAction(Sequence::create(
            CallFunc::create([this]() {
                enemy->setColor(Color3B(250, 121, 121));
                
                }), delay,
            CallFunc::create([this,color]() {
                enemy->setColor(color);
                }),
            nullptr
        ));

        this->unschedule(CC_SCHEDULE_SELECTOR(LevelFinal::playerCollisions));
    }

}

void LevelFinal::boxes(cocos2d::Vec2 tempo) {
    CCLOG("ENTRE");
    float tolerance = 5.0f;
    auto current = enemy->getSpriteFrame();
    Vec2 local = enemy->convertToNodeSpace(tempo);

    for (auto element : enemy->bossData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        if (hit <= tolerance) {
            enemy->setLife(enemy->getLife() - player->getBoxAt());
            Color3B color = enemy->getColor();

            auto delay = DelayTime::create(0.1f);

            enemy->runAction(Sequence::create(
                CallFunc::create([this]() {
                    enemy->setColor(Color3B(250, 121, 121));
                    }), delay,
                CallFunc::create([this, color]() {
                        enemy->setColor(color);
                    }),
                        nullptr
                        ));
            return;
        }
    }

}

void LevelFinal::check(cocos2d::Vec2 tempo) {
    float tolerance = 10.0f;
    auto current = player->getSpriteFrame();
    Vec2 local = player->convertToNodeSpace(tempo);

    for (auto element : player->playerData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        if (hit <= tolerance) {
            //Director::getInstance()->pause();
            player->setLife(player->getLife() - enemy->getBullet());
            player->runHurtAnimation();

            auto delay = DelayTime::create(.7f);

            CCLOG("Bottle: (%f)", player->getLife());
            CCLOG("Colision");
            return;
        }
    }

    CCLOG("No colision");
}


void LevelFinal::player_events(float delta) {
    auto event = EventListenerKeyboard::create();
    event->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            player->runDuckAnimation();
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
            player->runJumpAnimation();
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            playerMovements();
            if (!movePlayer) return;
            player->runMoveRightAnimation();
            //player->setPositionX(player->getPositionX() + 5);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            playerMovements();
            if (!movePlayer) return;
            player->runMoveLeftAnimation();
            //player->setPositionX(player->getPositionX() - 5);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
            player->runBlockAnimation();
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
            this->reorderChild(player, 2);
            this->reorderChild(enemy, 1);
            player->runPunchAnimation();
            this->schedule(CC_SCHEDULE_SELECTOR(LevelFinal::playerCollisions), .10f);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_T && !isTPressed) {
            isTPressed = true;
            player->runObjectAnimation();
            auto delay = DelayTime::create(.7f);

            int n = rand() % (2 - 1 + 1) + 1;
            if (n == 1) {
                auto box = Sprite::create("player/Box.png");
                box->setPosition(Vec2(player->getPositionX() + 40, 100));
                this->addChild(box);

                auto pPoint = Node::create();
                pPoint->setPosition(Vec2(40, 34));
                pPoint->setVisible(true);
                pPoint->retain();
                box->addChild(pPoint);

                auto moveBox = MoveTo::create(.30f, Vec2(enemy->getPositionX(), 103));
                box->runAction(Sequence::create(
                    moveBox,
                    CallFunc::create([this, box]() {
                        enemy->runQAnimation();

                        this->removeChild(box);
                        }),
                    nullptr
                ));
            }
            else if (n == 2) {
                auto box = Sprite::create("customer/bottle.png");
                box->setPosition(Vec2(player->getPositionX() + 40, 100));
                this->addChild(box);

                auto pPoint = Node::create();
                pPoint->setPosition(Vec2(40, 34));
                pPoint->setVisible(true);
                pPoint->retain();
                box->addChild(pPoint);

                auto moveBox = MoveTo::create(.30f, Vec2(enemy->getPositionX(), 103));
                box->runAction(Sequence::create(
                    moveBox,
                    CallFunc::create([this, box]() {
                        enemy->runQAnimation();
                        this->removeChild(box);
                        }),
                    nullptr
                ));
            }
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER && !superPower) {
            superPower = true;
            player->runAttackAnimation(enemy->getPositionX()-25.0f,enemy->getPositionY()-10.0f);

            enemy->stopAllActions();
            enemy->setLife(enemy->getLife() - 25.0f);
            enemy->runDefaultAnimation();
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
            player->runChargeAnimation();
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
        else if (keyCode == EventKeyboard::KeyCode::KEY_T) {
            isTPressed = false;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
            superPower = false;
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
}
