#include "MainMenuScene.h";
#include "GameScene.h";
#include "Definitions.h";

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto menuBgSprite = Sprite::create("menubg.jpg");
    menuBgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
    menuBgSprite->setScale(visibleSize.width / menuBgSprite->getContentSize().width, visibleSize.height / menuBgSprite->getContentSize().height);
    this->addChild(menuBgSprite, -1);
  
    auto playItem = MenuItemImage::create("playbutton.png", "playbutton_clicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point(0, 0));

    this->addChild(menu, 1);

    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



