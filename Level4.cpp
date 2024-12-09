#include "Level4.h"
#include "Level5.h"
#include <cstdlib>
#include <random>

USING_NS_CC;

Scene* Level4::createScene()
{
    return Level4::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Level4::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    srand((unsigned)time(NULL));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("Level4.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(5, -50));
    this->addChild(bg, -1);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Level4::menuCloseCallback, this));

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

    createPlayer();
    createSect();
    createLeader();

    this->schedule(CC_SCHEDULE_SELECTOR(Level4::player_events), .10f);

   
    this->schedule([this](float delta) {
        leaderAttacks();
        }, 2.5f, "check_distance");

    this->schedule([this](float delta) {
        sectAttack();
        }, 2.0f, "labels");

    this->schedule([this](float delta) {
        checkLife();
        }, 2.0f, "Life");

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void Level4::checkLife() {
    float distance = player->getPosition().distance(sect->getPosition());
    if (distance <= 30.0f) {
        auto next_scene = Level5::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
    else if (player->getLife() <= 0) {
        CCLOG("CI esalf");
        auto next_scene = Level4::createScene();
        Director::getInstance()->pushScene(next_scene);
    }
}

void Level4::leaderAttacks() {
    if (player && sect && leader) {
        int n = random(0, 2);
        if (n == 0) {
            sect->setLive(sect->getLive()+leader->getHeal());
            auto heal = Sprite::create("heal.png");
            heal->setPosition(sect->getPosition());
            this->addChild(heal);
            CCLOG("heal");
            auto delay = DelayTime::create(1.4f);
            heal->runAction(Sequence::create(
                delay,
                CallFunc::create([this, heal]() {
                    leader->runHealAnimation();
                    this->removeChild(heal);
                    }),
                nullptr
            ));
        }
        else if (n == 1) {
            leader->runSuperAnimation();
            player->setLife(player->getLife() - leader->getSuperA());
            auto shinra = Sprite::create("superAttack.png");
            CCLOG("shinra");
            shinra->setPosition(sect->getPositionX()-20.0f, sect->getPositionY());
            this->addChild(shinra);
            auto moveAttack = MoveTo::create(speed, player->getPosition());
            shinra->runAction(Sequence::create(
                moveAttack,
                CallFunc::create([this, shinra]() {
                    check();
                    this->removeChild(shinra);
                    }),
                nullptr
            ));
        }
        else if (n == 2) {
            Vec2 aux = leader->getPosition();
            leader->setPosition(player->getPositionX() + 25, player->getPositionY());
            auto magic = Sprite::create("Magic.png");
            magic->setPosition(leader->getPositionX()-10.0f,leader->getPositionY());
            this->addChild(magic);
            auto moveMagic = MoveTo::create(speed, Vec2(player->getPosition()));
            magic->runAction(Sequence::create(
                moveMagic,
                CallFunc::create([this]() {
                    check();
                    }),
                CallFunc::create([this, magic]() {
                    this->removeChild(magic);
                    movePlayer = true;
                    }),
                CallFunc::create([this, aux]() {
                    leader->setPosition(aux);
                    }),
                nullptr
            ));
        }
    }
}

void Level4::sectAttack() {
    if (player && sect && leader) {
        oneTime = true;
        int n = random(0, 1);

        if (n == 0) {
            auto delay = DelayTime::create(.7f);

            auto ghost = Sprite::create("Fantasma.png");
            ghost->setPosition(Vec2(sect->getPositionX() - 10.0f, 120.0f));
            this->addChild(ghost);
            sect->runAttackAnimation();

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(5, 8));
            pPoint->setVisible(true);
            pPoint->retain();
            ghost->addChild(pPoint);

            movePlayer = false;

            auto moveBottle = MoveTo::create(speed, Vec2(player->getPositionX() + 20.0f, 103.0f));
            ghost->runAction(Sequence::create(
                moveBottle,
                CallFunc::create([this, pPoint, ghost]() {
                    if (pPoint && pPoint->getParent()) {
                        Vec2 globalPoint = pPoint->convertToWorldSpace(Vec2::ZERO);
                        //CCLOG("Global Point Position: (%f, %f)", globalPoint.x, globalPoint.y);
                        check();
                    }
                    }),
                CallFunc::create([this, ghost]() {
                    this->removeChild(ghost);
                    movePlayer = true;
                    oneTime = false;
                    }),
                nullptr
            ));
        }
        else if (n == 1) {
            auto delay = DelayTime::create(.7f);

            auto magic = Sprite::create("Magic.png");
            magic->setPosition(Vec2(sect->getPositionX() - 10.0f, 120.0f));
            this->addChild(magic);
            sect->runAttackAnimation();

            auto pPoint = Node::create();
            pPoint->setPosition(Vec2(5, 8));
            pPoint->setVisible(true);
            pPoint->retain();
            magic->addChild(pPoint);

            movePlayer = false;

            auto moveBottle = MoveTo::create(speed, Vec2(player->getPositionX() + 20.0f, 103.0f));
            magic->runAction(Sequence::create(
                moveBottle,
                CallFunc::create([this, pPoint, magic]() {
                    if (pPoint && pPoint->getParent()) {
                        Vec2 globalPoint = pPoint->convertToWorldSpace(Vec2::ZERO);
                        //CCLOG("Global Point Position: (%f, %f)", globalPoint.x, globalPoint.y);
                        check();
                    }
                    }),
                CallFunc::create([this, magic]() {
                    this->removeChild(magic);
                    movePlayer = true;
                    }),
                nullptr
            ));
        }
    }
}

void Level4::menuCloseCallback(Ref* pSender)
{
    auto next_scene = Level4::createScene();
    Director::getInstance()->pushScene(next_scene);
    CCLOG("change");

}

void Level4::check() {
    auto current = player->getSpriteFrame();
    if (player->tags[current] != "punch" && player->tags[current] != "jump" && player->tags[current] != "block") {
        player->setLife(player->getLife() - 5.0f);
        player->runHurtAnimation();
    }

    CCLOG("No colision");
}


void Level4::createPlayer() {
    player = Player::create();
    if (!player) {
        CCLOG("Error: No se pudo crear el jugador.");
        return;
    }

    player->setPosition(Vec2(30, 100));
    this->addChild(player);

    player->runDefaultAnimation();
}

void Level4::createSect() {
    sect = Secta::create();
    if (!sect) {
        CCLOG("Error: No se pudo crear el enemigo.");
        return;
    }

    sect->setPosition(Vec2(395, 105));
    this->addChild(sect);

    sect->runDefaultAnimation();
}

void Level4::createLeader() {
    leader = Leader::create();
    if (!leader) {
        CCLOG("Error: No se pudo crear el enemigo.");
        return;
    }

    leader->setPosition(Vec2(435, 105));
    this->addChild(leader);

    leader->runDefaultAnimation();
}

void Level4::player_events(float delta) {
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
            else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
                player->runDuckAnimation();
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
                player->runBlockAnimation();
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
                player->runPunchAnimation();
            }
            else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
                player->runPunchAnimation();
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