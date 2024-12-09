#include "Level3.h"
#include "Level31.h"

USING_NS_CC;

Scene* Level3::createScene()
{
    return Level3::create();
}

bool Level3::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("City.png");
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(1, 30));
    this->addChild(bg, -1);;

    // moto
    moto = Sprite::create("player/playerMoto.png");
    moto->setPosition(Vec2(295, 85));
    this->addChild(moto);

    this->schedule(CC_SCHEDULE_SELECTOR(Level3::checkMove), .10f);
    this->scheduleUpdate();

    auto event = EventListenerKeyboard::create();
    event->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        Vec2 move;
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            left = true;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            right = true;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            up = true;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            down = true;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
            speed = 3.0f;
        }

        };

    event->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            left = false;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            right = false;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            up = false;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            down = false;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
            speed = 1.0f;
        }
        };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);

    return true;
}

void Level3::update(float delta) {
    if (!enable) {
        return;
    }

    Vec2 move(0, 0);
    float rotation = moto->getRotation();
    if (left) {
        move.x -= speed*170 * delta;
        rotation = -90;
    }
    if (right) {
        move.x += speed * 170 * delta;
        rotation = 90;
    }
    if (up) {
        move.y += speed * 170 * delta;
        rotation = 0;
    }
    if (down) {
        move.y -= speed * 170 * delta;
        rotation = 180;
    }

    if (moto->getRotation() != rotation) {
        moto->setRotation(rotation);
    }
    moto->setPosition(moto->getPosition() + move);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 motoPos = moto->getPosition();

    float x = std::max(0.0f, motoPos.x - visibleSize.width / 2);
    float y = std::max(0.0f, motoPos.y - visibleSize.height / 2);

    float maxX = bg->getContentSize().width - visibleSize.width;
    float maxY = bg->getContentSize().height - visibleSize.height;

    x = std::min(x, maxX);
    y = std::min(y, maxY);

    this->setPosition(-x, -y);

}

void Level3::checkMove(float delta) {
    // left, right
    if (((moto->getPositionX() > 259.0f && moto->getPositionX() < 324.0f) && (moto->getPositionY() > 243.0f && moto->getPositionY() < 423.0f))||((moto->getPositionX() > 718.0f && moto->getPositionX() < 784.0f) && (moto->getPositionY() > 493.0f && moto->getPositionY() < 725.0f)) || (moto->getPositionX() > 259.0f && moto->getPositionX() < 324.0f) && (moto->getPositionY() > 495.0f && moto->getPositionY() < 620.0f) || (moto->getPositionX() > 38.0f && moto->getPositionX() < 94.0f) && (moto->getPositionY() > 490.0f && moto->getPositionY() < 620.0f) || (moto->getPositionX() > 259.0f && moto->getPositionX() < 324.0f) && (moto->getPositionY() > 243.0f && moto->getPositionY() < 423.0f) ||(moto->getPositionX() > 259.0f && moto->getPositionX() < 324.0f) && (moto->getPositionY() < 169.0f) || ((moto->getPositionX() > 36.0f && moto->getPositionX() < 94.0f) && ((moto->getPositionY() > 243.0f && moto->getPositionY() < 423.0f)))) {
        if (right || left) {
            CCLOG("no AQUI es");
            enable = false;

            auto crash = Sprite::create("crash.png");
            crash->setPosition(moto->getPosition());
            this->addChild(crash);

            auto delay = DelayTime::create(0.1f);

            this->runAction(Sequence::create(delay,
                CallFunc::create([this]() {
                    auto scene = Level3::createScene();
                    auto transition = TransitionFade::create(1.0f, scene, Color3B::BLACK);
                    Director::getInstance()->replaceScene(transition);
                    }),
                        nullptr
                        ));
        }
    }
    // up, down
    else if ((moto->getPositionX() > 505.0f && moto->getPositionX() < 718.0f) && (moto->getPositionY() > 423.0f && moto->getPositionY() < 490.0f) || (moto->getPositionX() > 324.0f && moto->getPositionX() < 439.0f) && (moto->getPositionY() > 423.0f && moto->getPositionY() < 490.0f) || (moto->getPositionX() > 94.0f && moto->getPositionX() < 259.0f) && (moto->getPositionY() > 620.0f && moto->getPositionY() < 678.0f) || (moto->getPositionX() > 94.0f && moto->getPositionX() < 259.0f) && (moto->getPositionY() > 169.0f && moto->getPositionY() < 243.0f)) {
        if (up || down) {
            enable = false;

            auto crash = Sprite::create("crash.png");
            crash->setPosition(moto->getPosition());
            this->addChild(crash);

            auto delay = DelayTime::create(0.1f);

            this->runAction(Sequence::create(delay,
                CallFunc::create([this]() {
                    auto scene = Level3::createScene();
                    auto transition = TransitionFade::create(1.0f, scene, Color3B::BLACK);
                    Director::getInstance()->replaceScene(transition);
                    }),
                nullptr
            ));
        }
    }
    else if ((moto->getPositionX() < 505.0f && moto->getPositionX() > 439.0f)&&(moto->getPositionY()>423.0f)) {
        if (up) {
            auto crash = Sprite::create("crash.png");
            crash->setPosition(moto->getPosition());
            this->addChild(crash);

            auto delay = DelayTime::create(0.1f);

            this->runAction(Sequence::create(delay,
                CallFunc::create([this]() {
                    auto scene = Level3::createScene();
                    auto transition = TransitionFade::create(1.0f, scene, Color3B::BLACK);
                    Director::getInstance()->replaceScene(transition);
                    }),
                nullptr
            ));
        }
    }
    //choque
    else if (((moto->getPositionX() > 94.0f && moto->getPositionX() < 259.0f) && (moto->getPositionY() > 423.0f && moto->getPositionX() < 490.0f))||(moto->getPositionX() < 505.0f && moto->getPositionX() > 439.0f) && (moto->getPositionY() < 423.0f)||(moto->getPositionX() > 324.0f && moto->getPositionX() < 718.0f) && (moto->getPositionY() < 423.0f) || (moto->getPositionX() > 718.0f && moto->getPositionX() < 784.0f) && (moto->getPositionY() < 423.0f)) {
        enable = false;
        auto crash = Sprite::create("Car.png");
        auto crash2 = Sprite::create("Car2.png");

        if (right) {
            crash->setPosition(moto->getPositionX() + 200.0f, moto->getPositionY());
            this->addChild(crash);
            crash->runAction(MoveTo::create(.05f, Vec2(moto->getPositionX()+10.0f, moto->getPositionY())));
        }
        else if (down) {
            crash2->setPosition(moto->getPositionX(), moto->getPositionY()-200.0f);
            this->addChild(crash2);
            crash2->runAction(MoveTo::create(.05f, Vec2(moto->getPositionX(), moto->getPositionY()-10.0f)));
        }

        auto delay = DelayTime::create(0.1f);

        this->runAction(Sequence::create(delay,
            CallFunc::create([this]() {
                auto scene = Level3::createScene();
                auto transition = TransitionFade::create(1.0f, scene, Color3B::BLACK);
                Director::getInstance()->replaceScene(transition);
                }),
            nullptr
        ));
    }
    //lost
    else if ((moto->getPositionX() < 30.0f) || (moto->getPositionX() < 706.0f && moto->getPositionY() > 760.0f) || (moto->getPositionX()>774.0f)) {
        enable = false;
        
        auto crash = Sprite::create("Lost.png");

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        crash->setPosition(moto->getPosition());
        this->addChild(crash);

        auto delay = DelayTime::create(0.1f);

        this->runAction(Sequence::create(delay,
            CallFunc::create([this]() {
                auto scene = Level3::createScene();
                auto transition = TransitionFade::create(1.0f, scene, Color3B::BLACK);
                Director::getInstance()->replaceScene(transition);
                }),
            nullptr
        ));
    }
    else if ((moto->getPositionX()>718.0f && moto->getPositionX() < 784.0f) && moto->getPositionY() > 725.0f) {
        auto next_scene = Level31::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1, next_scene));
    }
    if ((moto->getPositionX()>36.0f && moto->getPositionX() < 94.0f) && (moto->getPositionY() < 405.0f && moto->getPositionY() > 395.0f)) {
        enemy = Sprite::create("impostor/impostorMoto.png");
        enemy->setPosition(moto->getPositionX()-10.0f, moto->getPositionY()+65.0f);
        this->addChild(enemy);
        this->runAction(Sequence::create(
            CallFunc::create([this]() {
                enemy->runAction(MoveTo::create(4.5f, Vec2(enemy->getPositionX() + 900.0f, enemy->getPositionY())));
                checkCollision(enemy->getPosition());
                }),
            nullptr
        ));
        
    }
    
}

void Level3::checkCollision(cocos2d::Vec2 tempo) {
    float distance = moto->getPosition().distance(tempo);
    if (distance >= 30.0f && distance <= 50.0f) {
        auto next_scene = Level31::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1, next_scene));
    }
}