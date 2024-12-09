#include "Level1.h"
#include "Level2.h"
#include <cstdlib>


USING_NS_CC;

Scene* Level1::createScene()
{
    return Level1::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Level1::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    //delay
    srand((unsigned)time(NULL));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("Level1.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(5, -50));
    this->addChild(bg, -1);

    createPlayer();
    createEnemy();
    this->schedule(CC_SCHEDULE_SELECTOR(Level1::player_events), .10f);

    auto label = Label::createWithTTF(player->getName(), "fonts/Marker Felt.ttf", 10);
    label->setTextColor(Color4B::RED);
    label->setPosition(Vec2(190, visibleSize.height));

    auto label2 = Label::createWithTTF("Customer", "fonts/Marker Felt.ttf", 10);
    label2->setTextColor(Color4B::RED);
    label2->setPosition(Vec2(290, visibleSize.height));

    auto healthBarBg = Sprite::create("player/barFill.png");
    healthBarBg->setPosition(Vec2(90, visibleSize.height));
    this->addChild(healthBarBg, 2);

    auto healthBarSprite = Sprite::create("player/healthbarbg.png");
    player->healthBar = ProgressTimer::create(healthBarSprite);

    player->healthBar->setType(ProgressTimer::Type::BAR);
    player->healthBar->setMidpoint(Vec2(0, 0.5));
    player->healthBar->setBarChangeRate(Vec2(1, 0));
    player->healthBar->setPosition(Vec2(107, visibleSize.height));
    player->healthBar->setPercentage(100);
    this->addChild(player->healthBar, 1);


    auto ChealthBarBg = Sprite::create("customer/barFill.png");
    ChealthBarBg->setPosition(Vec2(390, visibleSize.height));
    this->addChild(ChealthBarBg, 2);

    auto ChealthBarSprite = Sprite::create("customer/healthbarbg.png");
    enemy->customerHealthBar = ProgressTimer::create(ChealthBarSprite);

    enemy->customerHealthBar->setType(ProgressTimer::Type::BAR);
    enemy->customerHealthBar->setMidpoint(Vec2(1, 0.5));
    enemy->customerHealthBar->setBarChangeRate(Vec2(1, 0));
    enemy->customerHealthBar->setPosition(Vec2(373, visibleSize.height));
    enemy->customerHealthBar->setPercentage(100);
    this->addChild(enemy->customerHealthBar, 1);

    this->addChild(label, 1);
    this->addChild(label2, 1);

    this->schedule([this](float delta) {
        checkDistance();
        }, 2.0f, "check_distance");

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Level1::menuCloseCallback, this));

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
        CC_CALLBACK_1(Level1::pause, this)
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

void Level1::createPlayer() {
    player = Player::create();
    if (!player) {
        CCLOG("Error: No se pudo crear el jugador.");
        return;
    }

    player->setPosition(Vec2(40, 95));
    this->addChild(player);

    player->runDefaultAnimation();
    
}

void Level1::createEnemy() {
    enemy = Customer::create();
    if (!enemy) {
        CCLOG("Error: No se pudo crear el enemigo.");
        return;
    }

    enemy->setPosition(Vec2(420, 100));
    this->addChild(enemy);

    enemy->runDefaultAnimation();
}

void Level1::menuCloseCallback(Ref* pSender)
{
    auto next_scene = Level2::createScene();
    Director::getInstance()->pushScene(next_scene);
    CCLOG("change");

}

void Level1::pause(Ref* pSender) {
    if (!Paused) {
        Director::getInstance()->pause();
        Paused = true;
    }
    else {
        Director::getInstance()->resume();
        Paused = false;
    }
}

void Level1::checkDistance() {
    if (player && enemy) {
        float distance = player->getPosition().distance(enemy->getPosition());
        CCLOG("Distance between player and enemy: %f", distance);

        if (distance > 100.0f) {
            enemy->runThrowAnimation();

            auto delay = DelayTime::create(.7f);

            auto bottle = Sprite::create("customer/bottle.png");
            bottle->setPosition(Vec2(enemy->getPositionX() - 10, 120));
            this->addChild(bottle);

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(5, 8));
            pPoint->setVisible(true);
            pPoint->retain();
            bottle->addChild(pPoint);

            movePlayer = false;

            auto moveBottle = MoveTo::create(.30f, Vec2(player->getPositionX()+20,103));
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
                    enemy->runMoveRightAnimation();
                }),
                nullptr
            ));
        }
        else if (distance < 40.0f) {
            int n = rand() % (2 - 1 + 1) + 1;
            if (n == 1) {
                this->reorderChild(player, 1);
                this->reorderChild(enemy, 2);
                enemy->runPunchAnimation();
                this->schedule(CC_SCHEDULE_SELECTOR(Level1::enemyCollisions), .10f);
            }
            else if (n == 2) {
                this->reorderChild(player, 1);
                this->reorderChild(enemy, 2);
                enemy->runKickAnimation();
                this->schedule(CC_SCHEDULE_SELECTOR(Level1::enemyCollisions), .10f);
            }
        }
        else if (distance >= 40.0f && distance <= 100.0f) {
            enemy->runMoveRightAnimation();
        }
    }
}

void Level1::playerMovements() {
    float playerX = player->getPositionX();
    float enemyX = enemy->getPositionX();

    if (playerX < 30.0f) {
        player->setPositionX(30.0f);
        left = false;
        movePlayer = false;
    }
    else if (playerX >= enemyX-32.0f) {
        player->setPositionX(enemyX - 35.0f);
    }
}

void Level1::enemyCollisions(float delta) {
    auto playerCurrent = player->getSpriteFrame();
    auto enemyCurrent = enemy->getSpriteFrame();

    if (enemy->customerTags[enemyCurrent] == "kick" && ((player->tags[playerCurrent] != "block") || (player->tags[playerCurrent] != "jump"))) {
        player->setLife(player->getLife() - enemy->getStrength());
        CCLOG("Life K: (%f)", player->getLife());
        player->runHurtAnimation();
        player->playerTakeDamage(enemy->getStrength());

        this->unschedule(CC_SCHEDULE_SELECTOR(Level1::enemyCollisions));
    }

    else if (enemy->customerTags[enemyCurrent] == "punchCustomer" && ((player->tags[playerCurrent] != "duck"))) {
        player->setLife(player->getLife() - enemy->getStrength());
        CCLOG("Life P: (%f)", player->getLife());
        player->runHurtAnimation();
        player->playerTakeDamage(enemy->getStrength());

        this->unschedule(CC_SCHEDULE_SELECTOR(Level1::enemyCollisions));
    }
}

void Player::playerTakeDamage(float damage) {
    if (this->getLife() <= 0) {
        auto next_scene = Level1::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
    else {
        float healtPercentage = (static_cast<float>(this->getLife()) / 100) * 100.0f;
        this->healthBar->setPercentage(healtPercentage);
    }
}

void Customer::customerTakeDamage(float damage) {
    if (this->getLife() <= 0) {
        CCLOG("Sali");
        auto next_scene = Level2::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
    else {
        float healtPercentage = (static_cast<float>(this->getLife() / 200) * 100.0f);
        this->customerHealthBar->setPercentage(healtPercentage);
    }
}

void Level1::playerCollisions(float delta) {
    auto playerCurrent = player->getSpriteFrame();
    auto enemyCurrent = enemy->getSpriteFrame();
    float distance = player->getPosition().distance(enemy->getPosition());

    if (player->tags[playerCurrent] == "punch" && (distance<40.0f)) {
        enemy->setLife(enemy->getLife() - player->getStrength());
        enemy->customerTakeDamage(player->getStrength());
        CCLOG("Enemy life: (%f)", enemy->getLife());

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

        this->unschedule(CC_SCHEDULE_SELECTOR(Level1::playerCollisions));
    }

}

void Level1::boxes(cocos2d::Vec2 tempo) {
    CCLOG("ENTRE");
    float tolerance = 5.0f;
    auto current = enemy->getSpriteFrame();
    Vec2 local = enemy->convertToNodeSpace(tempo);

    for (auto element : enemy->customerData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        if (hit <= tolerance) {
            enemy->setLife(enemy->getLife() - player->getBoxAt());
            Color3B color = enemy->getColor();

            auto delay = DelayTime::create(0.1f);

            enemy->runAction(Sequence::create(
                CallFunc::create([this]() {
                    enemy->setColor(Color3B(250, 121, 121));
                    enemy->customerTakeDamage(player->getBoxAt());
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

void Level1::check(cocos2d::Vec2 tempo) {
    float tolerance = 5.0f;
    auto current = player->getSpriteFrame();
    Vec2 local = player->convertToNodeSpace(tempo);

    for (auto element : player->playerData[current]) {
        float hit = local.distance(Vec2(element.first, element.second));
        if (hit <= tolerance) {
            //Director::getInstance()->pause();
            player->setLife(player->getLife() - enemy->getBottleAt());
            player->runHurtAnimation();
            player->playerTakeDamage(enemy->getBottleAt());

            auto delay = DelayTime::create(.7f);

            CCLOG("Bottle: (%f)", player->getLife());
            CCLOG("Colision");
            return;
        }
    }

    CCLOG("No colision");
}


void Level1::player_events(float delta) {
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
            this->schedule(CC_SCHEDULE_SELECTOR(Level1::playerCollisions), .10f);
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

            auto moveBox = MoveTo::create(.30f, Vec2(enemy->getPositionX(), 103));
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
            auto action = MoveTo::create(1.0f,Vec2(enemy->getPositionX(), 100));
            player->runAction(action);
            player->runAttackAnimation(enemy->getPositionX()-40,enemy->getPositionY());

            enemy->stopAllActions();
            enemy->setLife(enemy->getLife() - 15.0f);
            enemy->customerTakeDamage(15.0f);
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
