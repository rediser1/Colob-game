#include "ShopScene.h";
#include "Definitions.h";
#include "GameScene.h";
#include "ui/CocosGUI.h";
USING_NS_CC;

unsigned int score;
Scene* ShopScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ShopScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("shopbg.jpg");
    bg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    this->addChild(bg);

    //go back to Game Scene
    auto backButton = MenuItemImage::create("exit.png", "exit_clicked.png", CC_CALLBACK_1(ShopScene::resumeGameScene, this));
    backButton->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.1));
    auto back = Menu::create(backButton, NULL);
    back->setPosition(Point(0, 0));
    this->addChild(back);

    scoreLabel = Label::createWithTTF(std::to_string(score), "fonts/MaldiniNormal-ZVKG3.ttf", 84);
    scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.85 + origin.y));
    scoreLabel->setColor(Color3B(166.0, 94.0, 239.0));
    this->addChild(scoreLabel, 1000);


    //buy upgrade for red mobs
    auto redButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::redMobBought, this));
    redButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.7 + origin.y));
    auto shopRed = Menu::create(redButton, NULL);
    shopRed->setPosition(Point(0, 0));
    this->addChild(shopRed);

    if (redMobLevel == MAX_MOB_LEVEL)
        upgradeRedLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        upgradeRedLabel = Label::createWithTTF(std::to_string(redMobCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    upgradeRedLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.7 + origin.y));
    upgradeRedLabel->setColor(Color3B(255, 203, 219));
    this->addChild(upgradeRedLabel);

    auto redSprite = Sprite::create("colob_red.png");
    redSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x, origin.y + visibleSize.height * 0.7 + origin.y));
    this->addChild(redSprite);



    //buy upgrade for blue mobs
    auto blueButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::blueMobBought, this));
    blueButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.5 + origin.y));
    auto shopBlue = Menu::create(blueButton, NULL);
    shopBlue->setPosition(Point(0, 0));
    this->addChild(shopBlue);

    if (blueMobLevel == MAX_MOB_LEVEL)
        upgradeBlueLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        upgradeBlueLabel = Label::createWithTTF(std::to_string(blueMobCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    upgradeBlueLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.5 + origin.y));
    upgradeBlueLabel->setColor(Color3B(255, 203, 219));
    this->addChild(upgradeBlueLabel);

    auto blueSprite = Sprite::create("colob_blue.png");
    blueSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x, origin.y + visibleSize.height * 0.5 + origin.y));
    this->addChild(blueSprite);



    //buy upgrade for yellow mobs
    auto yellowButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::yellowMobBought, this));
    yellowButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.3 + origin.y));
    auto shopYellow = Menu::create(yellowButton, NULL);
    shopYellow->setPosition(Point(0, 0));
    this->addChild(shopYellow);

    if (yellowMobLevel == MAX_MOB_LEVEL)
        upgradeYellowLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        upgradeYellowLabel = Label::createWithTTF(std::to_string(yellowMobCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    upgradeYellowLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.3 + origin.y));
    upgradeYellowLabel->setColor(Color3B(255, 203, 219));
    this->addChild(upgradeYellowLabel);

    auto yellowSprite = Sprite::create("colob_yellow.png");
    yellowSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x, origin.y + visibleSize.height * 0.3 + origin.y));
    this->addChild(yellowSprite);

    //buy upgrade for purple mobs
    auto purpleButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::purpleMobBought, this));
    purpleButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.1 + origin.y));
    auto shopPurple = Menu::create(purpleButton, NULL);
    shopPurple->setPosition(Point(0, 0));
    this->addChild(shopPurple);

    if (purpleMobLevel == MAX_MOB_LEVEL)
        upgradePurpleLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        upgradePurpleLabel = Label::createWithTTF(std::to_string(purpleMobCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    upgradePurpleLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.1 + origin.y));
    upgradePurpleLabel->setColor(Color3B(255, 203, 219));
    this->addChild(upgradePurpleLabel);

    auto purpleSprite = Sprite::create("colob_purple.png");
    purpleSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x, origin.y + visibleSize.height * 0.1 + origin.y));
    this->addChild(purpleSprite);

    //buy upgrade for green mobs
    auto greenButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::greenMobBought, this));
    greenButton->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height * 0.7 + origin.y));
    auto shopGreen = Menu::create(greenButton, NULL);
    shopGreen->setPosition(Point(0, 0));
    this->addChild(shopGreen);

    if(greenMobLevel == MAX_MOB_LEVEL)
        upgradeGreenLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        upgradeGreenLabel = Label::createWithTTF(std::to_string(greenMobCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    upgradeGreenLabel->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height * 0.7 + origin.y));
    upgradeGreenLabel->setColor(Color3B(255, 203, 219));
    this->addChild(upgradeGreenLabel);

    auto greenSprite = Sprite::create("colob_green.png");
    greenSprite->setPosition(Vec2(visibleSize.width * 0.9 + origin.x, origin.y + visibleSize.height * 0.7 + origin.y));
    this->addChild(greenSprite);

    //add mob
    auto addButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::addMobBought, this));
    addButton->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height * 0.5 + origin.y));
    auto shopAdd = Menu::create(addButton, NULL);
    shopAdd->setPosition(Point(0, 0));
    this->addChild(shopAdd);

    if(countOfAddedMobs == MAX_ADDED_MOBS)
        addMobCostLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        addMobCostLabel = Label::createWithTTF(std::to_string(addMobCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    addMobCostLabel->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height * 0.5 + origin.y));
    addMobCostLabel->setColor(Color3B(255, 203, 219));
    this->addChild(addMobCostLabel);

    Label* addMobLabel = Label::createWithTTF("Add 1 mob", "fonts/MaldiniNormal-ZVKG3.ttf", 40);
    addMobLabel->setPosition(Vec2(visibleSize.width * 0.925 + origin.x, origin.y + visibleSize.height * 0.5 + origin.y));
    addMobLabel->setColor(Color3B(166.0, 94.0, 239.0));
    this->addChild(addMobLabel);
    
    //+speed
    auto speedButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::speedUpgradeBought, this));
    speedButton->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height * 0.3 + origin.y));
    auto speedAdd = Menu::create(speedButton, NULL);
    speedAdd->setPosition(Point(0, 0));
    this->addChild(speedAdd);

    if(speedLevel == MAX_LEVEL_SPEED)
        speedCostLabel = Label::createWithTTF("MAX", "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    else
        speedCostLabel = Label::createWithTTF(std::to_string(speedCost), "fonts/MaldiniNormal-ZVKG3.ttf", 50);
    speedCostLabel->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, origin.y + visibleSize.height * 0.3 + origin.y));
    speedCostLabel->setColor(Color3B(255, 203, 219));
    this->addChild(speedCostLabel);

    Label* speedMobLabel = Label::createWithTTF("Increase \n speed", "fonts/MaldiniNormal-ZVKG3.ttf", 40);
    speedMobLabel->setPosition(Vec2(visibleSize.width * 0.925 + origin.x, origin.y + visibleSize.height * 0.3 + origin.y));
    speedMobLabel->setColor(Color3B(166.0, 94.0, 239.0));
    this->addChild(speedMobLabel);



    return true;
}


void ShopScene::resumeGameScene(cocos2d::Ref* sender)
{
    Director::getInstance()->resume();
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void ShopScene::redMobBought(cocos2d::Ref* sender)
{
    if (score >= redMobCost)
    {
        if (redMobLevel == MAX_MOB_LEVEL)
            return;
        score -= redMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (redMobLevel == 1)
        {
            Mob::setRedCost(2);
            redMobCost = 50;
        }
        else if (redMobLevel == 2)
        {
            Mob::setRedCost(4);
            redMobCost = 100;
        }
        else if (redMobLevel == 3)
        {
            Mob::setRedCost(8);
            redMobCost = 200;
        }
        else if (redMobLevel == 4)
        {
            Mob::setRedCost(16);
            upgradeRedLabel->setString("MAX");
            redMobLevel++;
            return;
        }
        redMobLevel++;
        upgradeRedLabel->setString(std::to_string(redMobCost));
    }
}

void ShopScene::blueMobBought(cocos2d::Ref* sender)
{
    if (score >= blueMobCost)
    {
        if (blueMobLevel == MAX_MOB_LEVEL)
            return;
        score -= blueMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (blueMobLevel == 1)
        {
            Mob::setBlueCost(2);
            blueMobCost = 50;
        }
        else if (blueMobLevel == 2)
        {
            Mob::setBlueCost(4);
            blueMobCost = 100;
        }
        else if (blueMobLevel == 3)
        {
            Mob::setBlueCost(8);
            blueMobCost = 200;
        }
        else if (blueMobLevel == 4)
        {
            Mob::setBlueCost(16);
            upgradeBlueLabel->setString("MAX");
            blueMobLevel++;
            return;
        }
        blueMobLevel++;
        upgradeBlueLabel->setString(std::to_string(blueMobCost));
    }
}

void ShopScene::yellowMobBought(cocos2d::Ref* sender)
{
    if (score >= yellowMobCost)
    {
        if (yellowMobLevel == MAX_MOB_LEVEL)
            return;
        score -= yellowMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (yellowMobLevel == 1)
        {
            Mob::setYellowCost(2);
            yellowMobCost = 50;
        }
        else if (yellowMobLevel == 2)
        {
            Mob::setYellowCost(4);
            yellowMobCost = 100;
        }
        else if (yellowMobLevel == 3)
        {
            Mob::setYellowCost(8);
            yellowMobCost = 200;
        }
        else if (yellowMobLevel == 4)
        {
            Mob::setYellowCost(16);
            upgradeYellowLabel->setString("MAX");
            yellowMobLevel++;
            return;
        }
        yellowMobLevel++;
        upgradeYellowLabel->setString(std::to_string(yellowMobCost));
    }
}

void ShopScene::purpleMobBought(cocos2d::Ref* sender)
{
    if (score >= purpleMobCost)
    {
        if (purpleMobLevel == MAX_MOB_LEVEL)
            return;
        score -= purpleMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (purpleMobLevel == 1)
        {
            Mob::setPurpleCost(2);
            purpleMobCost = 50;
        }
        else if (purpleMobLevel == 2)
        {
            Mob::setPurpleCost(4);
            purpleMobCost = 100;
        }
        else if (purpleMobLevel == 3)
        {
            Mob::setPurpleCost(8);
            purpleMobCost = 200;
        }
        else if (purpleMobLevel == 4)
        {
            Mob::setPurpleCost(16);
            upgradePurpleLabel->setString("MAX");
            purpleMobLevel++;
            return;
        }
        purpleMobLevel++;
        upgradePurpleLabel->setString(std::to_string(purpleMobCost));
    }
}

void ShopScene::greenMobBought(cocos2d::Ref* sender)
{
    if (score >= greenMobCost)
    {
        if (greenMobLevel == MAX_MOB_LEVEL)
            return;
        score -= greenMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (greenMobLevel == 1)
        {
            Mob::setGreenCost(2);
            greenMobCost = 50;
        }
        else if (greenMobLevel == 2)
        {
            Mob::setGreenCost(4);
            greenMobCost = 100;
        }
        else if (greenMobLevel == 3)
        {
            Mob::setGreenCost(8);
            greenMobCost = 200;
        }
        else if (greenMobLevel == 4)
        {
            Mob::setGreenCost(16);
            upgradeGreenLabel->setString("MAX");
            greenMobLevel++;
            return;
        }
        greenMobLevel++;
        upgradeGreenLabel->setString(std::to_string(greenMobCost));
    }
}

void ShopScene::addMobBought(cocos2d::Ref* sender)
{
    if (score >= addMobCost)
    {
        if (countOfAddedMobs == MAX_ADDED_MOBS)
            return;
        score -= addMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (countOfAddedMobs == 0)
        {
            addMobCost = 100;
        }
        else if (countOfAddedMobs == 1)
        {
            addMobCost = 250;
        }
        else if (countOfAddedMobs == 2)
        {
            addMobCost = 500;
        }
        else if (countOfAddedMobs == 3)
        {
            addMobCostLabel->setString("MAX");
            GameScene::addMob();
            countOfAddedMobs++;
            return;
        }
        GameScene::addMob();
        countOfAddedMobs++;
        addMobCostLabel->setString(std::to_string(addMobCost));
    }
}

void ShopScene::speedUpgradeBought(cocos2d::Ref* sender)
{
    if (score >= speedCost)
    {
        if (speedLevel == MAX_LEVEL_SPEED)
            return;
        score -= speedCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (speedLevel == 1)
        {
            speedCost = 500;
            Colob::setSpeed(200);
            speedLevel++;
        }
        else if (speedLevel == 2)
        {
            speedCost = 1000;
            Colob::setSpeed(250);
            speedLevel++;
        }
        else if (speedLevel == 3)
        {
            speedCost = 2000;
            Colob::setSpeed(300);
            speedLevel++;
        }
        else if (speedLevel == 4)
        {
            speedCostLabel->setString("MAX");
            Colob::setSpeed(350);
            speedLevel++;
            return;
        }
        speedCostLabel->setString(std::to_string(speedCost));
    }
}


int ShopScene::redMobLevel = 1;
int ShopScene::redMobCost = 25;

int ShopScene::yellowMobLevel = 1;
int ShopScene::yellowMobCost = 25;

int ShopScene::blueMobLevel = 1;
int ShopScene::blueMobCost = 25;

int ShopScene::greenMobLevel = 1;
int ShopScene::greenMobCost = 25;

int ShopScene::purpleMobLevel = 1;
int ShopScene::purpleMobCost = 25;

int ShopScene::countOfAddedMobs = 0;
int ShopScene::addMobCost = 50;

int ShopScene::speedLevel = 1;
int ShopScene::speedCost = 100;
//std::string ShopScene::strSpeedCost = std::to_string(speedCost);