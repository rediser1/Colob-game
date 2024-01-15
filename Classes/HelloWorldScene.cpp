
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "ShopScene.h"

USING_NS_CC;

Scene* HelloWorldScene::createScene()
{
    return HelloWorldScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool HelloWorldScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorldScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);

    auto bgsprite = Sprite::create("bg.jpg");
    bgsprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, visibleSize.height / bgsprite->getContentSize().height);
    this->addChild(bgsprite);

    //ShopScene::loadInfo();
    return true;
   
}

void  HelloWorldScene::GoToMainMenuScene(float dt)
{
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


