#include "Level31.h"
#include "Level4.h"

USING_NS_CC;

Scene* Level31::createScene()
{
    return Level31::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool Level31::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("Level3.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(5, -50));
    this->addChild(bg, -1);

    this->schedule([this](float delta) {
        checkDistance();
        }, 2.0f, "check_distance");

    this->schedule([this](float delta) {
        checkLife();
        }, 1.0f, "check_life");

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Level31::menuCloseCallback, this));

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
        CC_CALLBACK_1(Level31::pause, this));

    float pause_x = origin.x + visibleSize.width / 2;
    float pause_y = visibleSize.height;
    pauseItem->setPosition(Vec2(pause_x, pause_y));

    auto pause_menu = Menu::create(pauseItem, NULL);
    pause_menu->setPosition(Vec2::ZERO);
    this->addChild(pause_menu, 1);

    createPlayer();
    createImpostor();
    this->schedule(CC_SCHEDULE_SELECTOR(Level31::player_events), .10f);
    return true;
}

void Level31::pause(Ref* pSender) {
    if (!Paused) {
        Director::getInstance()->pause();
        Paused = true;
    }
    else {
        Director::getInstance()->resume();
        Paused = false;
    }
}

void Level31::createPlayer() {
    player = Player::create();
    if (!player) {
        CCLOG("Error: No se pudo crear el jugador.");
        return;
    }

    player->setPosition(Vec2(40, 100));
    this->addChild(player);

    player->runDefaultAnimation();

}

void Level31::createImpostor() {
    impostor = Impostor::create();
    if (!impostor) {
        CCLOG("Error: No se pudo crear el enemigo.");
        return;
    }

    impostor->setPosition(Vec2(410, 100));
    this->addChild(impostor);

    impostor->runDefaultAnimation();
}

void Level31::checkLife() {
    if (player->getLife() <= 0.0f) {
        auto next_scene = Level31::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
    else if (impostor->getLife() <= 0.0f) {
        auto next_scene = Level4::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
}

void Level31::checkDistance() {
    if (player && impostor) {
        float distance = player->getPosition().distance(impostor->getPosition());
        CCLOG("Distance between player and enemy: %f", distance);

        if (distance > 100.0f) {
            impostor->runObjectAnimation();

            auto delay = DelayTime::create(.7f);

            auto box = Sprite::create("player/Box.png");
            box->setPosition(Vec2(impostor->getPositionX() - 10, 120));
            this->addChild(box);

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(18, 32));
            pPoint->setVisible(true);
            pPoint->retain();
            box->addChild(pPoint);

            movePlayer = false;

            auto moveBottle = MoveTo::create(.50f, Vec2(player->getPositionX() + 20, 103));
            box->runAction(Sequence::create(
                moveBottle,
                CallFunc::create([this, pPoint, box]() {
                    if (pPoint && pPoint->getParent()) {
                        Vec2 globalPoint = pPoint->convertToWorldSpace(Vec2::ZERO);
                        //CCLOG("Global Point Position: (%f, %f)", globalPoint.x, globalPoint.y);
                        check(globalPoint);
                    }
                    }),
                CallFunc::create([this, box]() {
                    this->removeChild(box);
                    movePlayer = true;
                    impostor->runMoveLeftAnimation();
                    }),
                nullptr
            ));
        }
        else if (distance < 35.0f) {
            this->reorderChild(player, 1);
            this->reorderChild(impostor, 2);
            impostor->runPunchAnimation();
            this->schedule(CC_SCHEDULE_SELECTOR(Level31::enemyCollisions), .10f);
        }
        else if (distance >= 35.0f && distance <= 100.0f) {
            impostor->runMoveLeftAnimation();
        }
    }
}

void Level31::menuCloseCallback(Ref* pSender)
{
    auto next_scene = Level31::createScene();
    Director::getInstance()->pushScene(next_scene);
    CCLOG("change");

}

void Level31::playerCollisions(float delta) {
    auto playerCurrent = player->getSpriteFrame();
    auto enemyCurrent = impostor->getSpriteFrame();
    float distance = player->getPosition().distance(impostor->getPosition());

    if (player->tags[playerCurrent] == "punch" && (distance < 40.0f)) {
        impostor->setLife(impostor->getLife() - player->getStrength());
        //impostor->customerTakeDamage(player->getStrength());
        CCLOG("Enemy life: (%f)", impostor->getLife());

        Color3B color = impostor->getColor();

        auto delay = DelayTime::create(0.1f);

        impostor->runAction(Sequence::create(
            CallFunc::create([this]() {
                impostor->setColor(Color3B(250, 121, 121));

                }), delay,
            CallFunc::create([this, color]() {
                    impostor->setColor(color);
                }),
                    nullptr
                    ));

        this->unschedule(CC_SCHEDULE_SELECTOR(Level31::playerCollisions));
    }

}

void Level31::enemyCollisions(float delta) {
    auto playerCurrent = player->getSpriteFrame();
    auto enemyCurrent = impostor->getSpriteFrame();

    if (impostor->tagsI[enemyCurrent] == "punchI" && ((player->tags[playerCurrent] != "block") || (player->tags[playerCurrent] != "jump") || (player->tags[playerCurrent] != "duck"))) {
        player->setLife(player->getLife() - impostor->getStrength());
        CCLOG("Life K: (%f)", player->getLife());
        player->runHurtAnimation();
        //player->playerTakeDamage(impostor->getStrength());

        this->unschedule(CC_SCHEDULE_SELECTOR(Level31::enemyCollisions));
    } 
    else if (impostor->tagsI[enemyCurrent] == "throwO" && ((player->tags[playerCurrent] != "block") || (player->tags[playerCurrent] != "jump") || (player->tags[playerCurrent] != "punch"))) {
        player->setLife(player->getLife() - impostor->getStrength());
        CCLOG("Life K: (%f)", player->getLife());
        player->runHurtAnimation();
        //player->playerTakeDamage(impostor->getStrength());

        this->unschedule(CC_SCHEDULE_SELECTOR(Level31::enemyCollisions));
    }
}

void Level31::playerMovements() {
    float playerX = player->getPositionX();
    float enemyX = impostor->getPositionX();

    if (playerX < 30.0f) {
        player->setPositionX(30.0f);
        left = false;
        movePlayer = false;
    }
    else if (playerX >= enemyX - 22.0f) {
        player->setPositionX(enemyX - 25.0f);
    }
}

void Level31::player_events(float delta) {
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
            this->reorderChild(impostor, 1);
            player->runPunchAnimation();
            this->schedule(CC_SCHEDULE_SELECTOR(Level31::playerCollisions), .10f);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_T && !isTPressed) {
            isTPressed = true;
            player->runObjectAnimation();
            auto delay = DelayTime::create(.7f);

            auto box = Sprite::create("player/Box.png");
            box->setPosition(Vec2(player->getPositionX() + 40, 100));
            this->addChild(box);

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(40, 34));
            pPoint->setVisible(true);
            pPoint->retain();
            box->addChild(pPoint);

            auto debugMarker = DrawNode::create();
            debugMarker->drawDot(Vec2::ZERO, 5, Color4F::RED);
            pPoint->addChild(debugMarker);

            auto moveBox = MoveTo::create(.30f, Vec2(impostor->getPositionX(), 103));
            box->runAction(Sequence::create(
                moveBox,
                CallFunc::create([this, pPoint, box]() {
                    if (pPoint && pPoint->getParent()) {
                        Vec2 gPoint = pPoint->convertToWorldSpace(Vec2::ZERO);
                        boxes(gPoint);
                    }
                    }),
                CallFunc::create([this, box]() {
                    this->removeChild(box);
                    }),
                nullptr
            ));
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER && !superPower) {
            superPower = true;
            auto action = MoveTo::create(1.0f, Vec2(impostor->getPositionX(), 100));
            player->runAction(action);
            player->runAttackAnimation(impostor->getPositionX() - 40, impostor->getPositionY());

            impostor->stopAllActions();
            impostor->setLife(impostor->getLife() - 15.0f);
            //impostor->customerTakeDamage(15.0f);
            impostor->runDefaultAnimation();
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

void Level31::boxes(cocos2d::Vec2 tempo) {
    CCLOG("ENTRE");
    float tolerance = 20.0f;
    auto current = impostor->getSpriteFrame();
    Vec2 local = impostor->convertToNodeSpace(tempo);

    for (auto element : impostor->impostorData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        if (hit <= tolerance) {
            impostor->setLife(impostor->getLife() - player->getBoxAt());
            Color3B color = impostor->getColor();

            auto delay = DelayTime::create(0.1f);

            impostor->runAction(Sequence::create(
                CallFunc::create([this]() {
                    impostor->setColor(Color3B(250, 121, 121));
                    //impostor->customerTakeDamage(player->getBoxAt());
                    }), delay,
                CallFunc::create([this, color]() {
                        impostor->setColor(color);
                    }),
                        nullptr
                        ));
            return;
        }
    }

}

void Level31::check(cocos2d::Vec2 tempo) {
    float tolerance = 20.0f;
    auto current = player->getSpriteFrame();
    Vec2 local = player->convertToNodeSpace(tempo);
    
    for (auto element : player->playerData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        
        if (hit <= tolerance) {
            //Director::getInstance()->pause();
            player->setLife(player->getLife() - impostor->getBoxAt());
            player->runHurtAnimation();

            //player->playerTakeDamage(impostor->getBoxAt());

            auto delay = DelayTime::create(.7f);

            CCLOG("Bottle: (%f)", player->getLife());
            CCLOG("Colision");
            return;
        }
    }

    CCLOG("No colision");
}