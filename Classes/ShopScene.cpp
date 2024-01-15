#include "ShopScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include <list>
#include "MainMenuScene.h"
#include "DesignScene.h"

USING_NS_CC;


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

   
    buySound->play2d("go_some_scene.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("shopbg.png");
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
    scoreLabel->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.9 + origin.y));
    scoreLabel->setColor(Color3B(65.0, 105.0, 225.0)); // purple 166.0, 94.0, 239.0
    this->addChild(scoreLabel, 1000);

    auto skillsLabel = Label::createWithTTF("Skills", "fonts/Marker Felt.ttf", 70);
    skillsLabel->setPosition(Point(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.89 + origin.y));
    skillsLabel->setColor(Color3B(65, 105, 225));
    this->addChild(skillsLabel, 1000);

    auto line = Sprite::create("blue_line.png");
    line->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.8 + origin.y));
    this->addChild(line);


    //buy upgrade for red mobs
    auto redButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::redMobBought, this));
    redButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.7 + origin.y));
    auto shopRed = Menu::create(redButton, NULL);
    shopRed->setPosition(Point(0, 0));
    this->addChild(shopRed);

    if (redMobLevel == MAX_MOB_LEVEL)
        upgradeRedLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        upgradeRedLabel = Label::createWithTTF(std::to_string(redMobCost), "fonts/Flix.ttf", 50);
    upgradeRedLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x,  visibleSize.height * 0.7 + origin.y));
    upgradeRedLabel->setColor(Color3B(0, 0, 0));
    this->addChild(upgradeRedLabel);

    auto redSprite = Sprite::create("colob_red.png");
    redSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x,  visibleSize.height * 0.7 + origin.y));
    this->addChild(redSprite);



    //buy upgrade for blue mobs
    auto blueButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::blueMobBought, this));
    blueButton->setPosition(Vec2(visibleSize.width / 2 + origin.x,  visibleSize.height * 0.5 + origin.y));
    auto shopBlue = Menu::create(blueButton, NULL);
    shopBlue->setPosition(Point(0, 0));
    this->addChild(shopBlue);

    if (blueMobLevel == MAX_MOB_LEVEL)
        upgradeBlueLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        upgradeBlueLabel = Label::createWithTTF(std::to_string(blueMobCost), "fonts/Flix.ttf", 50);
    upgradeBlueLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.5 + origin.y));
    upgradeBlueLabel->setColor(Color3B(0, 0, 0));
    this->addChild(upgradeBlueLabel);

    auto blueSprite = Sprite::create("colob_blue.png");
    blueSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x, visibleSize.height * 0.5 + origin.y));
    this->addChild(blueSprite);



    //buy upgrade for yellow mobs
    auto yellowButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::yellowMobBought, this));
    yellowButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.3 + origin.y));
    auto shopYellow = Menu::create(yellowButton, NULL);
    shopYellow->setPosition(Point(0, 0));
    this->addChild(shopYellow);

    if (yellowMobLevel == MAX_MOB_LEVEL)
        upgradeYellowLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        upgradeYellowLabel = Label::createWithTTF(std::to_string(yellowMobCost), "fonts/Flix.ttf", 50);
    upgradeYellowLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.3 + origin.y));
    upgradeYellowLabel->setColor(Color3B(0,0,0));
    this->addChild(upgradeYellowLabel);

    auto yellowSprite = Sprite::create("colob_yellow.png");
    yellowSprite->setPosition(Vec2(visibleSize.width * 0.6 + origin.x,  visibleSize.height * 0.3 + origin.y));
    this->addChild(yellowSprite);

    //buy upgrade for purple mobs
    auto purpleButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::purpleMobBought, this));
    purpleButton->setPosition(Vec2(visibleSize.width * 0.2 + origin.x,  visibleSize.height * 0.5 + origin.y));
    auto shopPurple = Menu::create(purpleButton, NULL);
    shopPurple->setPosition(Point(0, 0));
    this->addChild(shopPurple);

    if (purpleMobLevel == MAX_MOB_LEVEL)
        upgradePurpleLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        upgradePurpleLabel = Label::createWithTTF(std::to_string(purpleMobCost), "fonts/Flix.ttf", 50);
    upgradePurpleLabel->setPosition(Vec2(visibleSize.width * 0.2 + origin.x,  visibleSize.height * 0.5 + origin.y));
    upgradePurpleLabel->setColor(Color3B(0, 0, 0));
    this->addChild(upgradePurpleLabel);

    auto purpleSprite = Sprite::create("colob_purple.png");
    purpleSprite->setPosition(Vec2(visibleSize.width * 0.3 + origin.x,  visibleSize.height * 0.5 + origin.y));
    this->addChild(purpleSprite);

    //buy upgrade for green mobs
    auto greenButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::greenMobBought, this));
    greenButton->setPosition(Vec2(visibleSize.width * 0.2 + origin.x, visibleSize.height * 0.3 + origin.y));
    auto shopGreen = Menu::create(greenButton, NULL);
    shopGreen->setPosition(Point(0, 0));
    this->addChild(shopGreen);

    if(greenMobLevel == MAX_MOB_LEVEL)
        upgradeGreenLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        upgradeGreenLabel = Label::createWithTTF(std::to_string(greenMobCost), "fonts/Flix.ttf", 50);
    upgradeGreenLabel->setPosition(Vec2(visibleSize.width * 0.2 + origin.x,  visibleSize.height * 0.3 + origin.y));
    upgradeGreenLabel->setColor(Color3B(0, 0, 0));
    this->addChild(upgradeGreenLabel);

    auto greenSprite = Sprite::create("colob_green.png");
    greenSprite->setPosition(Vec2(visibleSize.width * 0.3 + origin.x, visibleSize.height * 0.3 + origin.y));
    this->addChild(greenSprite);

    //add mob
    auto addButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::addMobBought, this));
    addButton->setPosition(Vec2(visibleSize.width * 0.8 + origin.x,  visibleSize.height * 0.5 + origin.y));
    auto shopAdd = Menu::create(addButton, NULL);
    shopAdd->setPosition(Point(0, 0));
    this->addChild(shopAdd);

    if(countOfAddedMobs == MAX_ADDED_MOBS)
        addMobCostLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        addMobCostLabel = Label::createWithTTF(std::to_string(addMobCost), "fonts/Flix.ttf", 50);
    addMobCostLabel->setPosition(Vec2(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.5 + origin.y));
    addMobCostLabel->setColor(Color3B(0,0,0));
    this->addChild(addMobCostLabel);

    Label* addMobLabel = Label::createWithTTF("Add 1 mob", "fonts/MaldiniNormal-ZVKG3.ttf", 40);
    addMobLabel->setPosition(Vec2(visibleSize.width * 0.925 + origin.x, visibleSize.height * 0.5 + origin.y));
    addMobLabel->setColor(Color3B(65.0f, 105.0f, 225.0f));
    this->addChild(addMobLabel);
    
    //+speed
    auto speedButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::speedUpgradeBought, this));
    speedButton->setPosition(Vec2(visibleSize.width * 0.8 + origin.x,  visibleSize.height * 0.7 + origin.y));
    auto speedAdd = Menu::create(speedButton, NULL);
    speedAdd->setPosition(Point(0, 0));
    this->addChild(speedAdd);

    if(speedLevel == MAX_LEVEL_SPEED)
        speedCostLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        speedCostLabel = Label::createWithTTF(std::to_string(speedCost), "fonts/Flix.ttf", 50);
    speedCostLabel->setPosition(Vec2(visibleSize.width * 0.8 + origin.x,  visibleSize.height * 0.7 + origin.y));
    speedCostLabel->setColor(Color3B(0, 0, 0));
    this->addChild(speedCostLabel);

    Label* speedMobLabel = Label::createWithTTF("Increase \n speed", "fonts/MaldiniNormal-ZVKG3.ttf", 40);
    speedMobLabel->setPosition(Vec2(visibleSize.width * 0.925 + origin.x, visibleSize.height * 0.7 + origin.y));
    speedMobLabel->setColor(Color3B(65.0f, 105.0f, 225.0f));
    this->addChild(speedMobLabel);

    userLevels = UserDefault::getInstance();

    //music button
    if (GameScene::getMusicStatus() == false)
        musicOnButton = MenuItemImage::create("music_off.png", "music_on.png", CC_CALLBACK_1(ShopScene::isMusicOnClick, this));
    else
        musicOnButton = MenuItemImage::create("music_on.png", "music_off.png", CC_CALLBACK_1(ShopScene::isMusicOnClick, this));
    musicOnButton->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95));
    musicOnButton->setSelectedImage(Sprite::create("music_off.png"));
    auto musicOn = Menu::create(musicOnButton, NULL);
    musicOn->setPosition(Point(0, 0));
    this->addChild(musicOn, 2);

    //go design scene
    auto designSceneButton = MenuItemImage::create("arrow_right.png", "arrow_right_clicked.png", CC_CALLBACK_1(ShopScene::goDesignScene, this));
    designSceneButton->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.18));
    auto designScene = Menu::create(designSceneButton, NULL);
    designScene->setPosition(Point(0, 0));
    this->addChild(designScene, 2);

    //super mob upgr

    auto superButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(ShopScene::superMobBought, this));
    superButton->setPosition(Vec2(visibleSize.width * 0.2 + origin.x, visibleSize.height * 0.7 + origin.y));
    auto shopSuper = Menu::create(superButton, NULL);
    shopSuper->setPosition(Point(0, 0));
    this->addChild(shopSuper);

    if (superMobLevel == MAX_MOB_LEVEL)
        superCostLabel = Label::createWithTTF("MAX", "fonts/Flix.ttf", 50);
    else
        superCostLabel = Label::createWithTTF(std::to_string(superMobCost), "fonts/Flix.ttf", 50);
    superCostLabel->setPosition(Vec2(visibleSize.width * 0.2 + origin.x, visibleSize.height * 0.7 + origin.y));
    superCostLabel->setColor(Color3B(0, 0, 0));
    this->addChild(superCostLabel);

    switch(superMobLevel)
    {
    case 1:
        superSprite = Sprite::create("colob_super_100.png");
        break;
    case 2:
        superSprite = Sprite::create("colob_super_250.png");
        break;
    case 3:
        superSprite = Sprite::create("colob_super_500.png"); 
        break;
    case 4:
        superSprite = Sprite::create("colob_super_1000.png");
        break;
    case 5:
        superSprite = Sprite::create("colob_super_1000.png");
        break;
    }
    superSprite->setPosition(Vec2(visibleSize.width * 0.3 + origin.x, visibleSize.height * 0.7 + origin.y));
    this->addChild(superSprite);

    return true;
}

void ShopScene::goDesignScene(cocos2d::Ref* sender)
{
    auto scene = DesignScene::createScene(score);
    Director::getInstance()->pushScene(scene);
    buySound->play2d("go_some_scene.mp3");
}

void ShopScene::isMusicOnClick(cocos2d::Ref* sender)
{
    if (GameScene::getMusicStatus() == true)
    {
        MainMenuScene::stopMusic();
        musicOnButton->setSelectedImage(Sprite::create("music_on.png"));
        musicOnButton->setNormalImage(Sprite::create("music_off.png"));
        GameScene::setMusicStatus(false);
    }
    else {
        MainMenuScene::startMusic();
        musicOnButton->setSelectedImage(Sprite::create("music_off.png"));
        musicOnButton->setNormalImage(Sprite::create("music_on.png"));
       GameScene::setMusicStatus(true);
    }
}

void ShopScene::resumeGameScene(cocos2d::Ref* sender)
{
    buySound->play2d("go_some_scene.mp3");
    GameScene::setScore(score);
    GameScene::updateScoreLabel();
    Director::getInstance()->popScene();
}

void ShopScene::redMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (redMobLevel == MAX_MOB_LEVEL)
        return;
    if (score >= redMobCost)
    {
        score -= redMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (redMobLevel == 1)
        {
            Mob::setRedCost(2);
            redMobCost = 100;
        }
        else if (redMobLevel == 2)
        {
            Mob::setRedCost(4);
            redMobCost = 200;
        }
        else if (redMobLevel == 3)
        {
            Mob::setRedCost(8);
            redMobCost = 400;
        }
        else if (redMobLevel == 4)
        {
            Mob::setRedCost(16);
            upgradeRedLabel->setString("MAX");
            redMobLevel++;
            userLevels->setIntegerForKey("redMobLvl", redMobLevel);
            return;
        }
        ++redMobLevel;
        userLevels->setIntegerForKey("redMobLvl", redMobLevel);
        upgradeRedLabel->setString(std::to_string(redMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::blueMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (blueMobLevel == MAX_MOB_LEVEL)
        return;
    if (score >= blueMobCost)
    {
        score -= blueMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (blueMobLevel == 1)
        {
            Mob::setBlueCost(2);
            blueMobCost = 100;
        }
        else if (blueMobLevel == 2)
        {
            Mob::setBlueCost(4);
            blueMobCost = 200;
        }
        else if (blueMobLevel == 3)
        {
            Mob::setBlueCost(8);
            blueMobCost = 400;
        }
        else if (blueMobLevel == 4)
        {
            Mob::setBlueCost(16);
            upgradeBlueLabel->setString("MAX");
            blueMobLevel++;
            userLevels->setIntegerForKey("blueMobLvl", blueMobLevel);
            return;
        }
        ++blueMobLevel;
        userLevels->setIntegerForKey("blueMobLvl", blueMobLevel);
        upgradeBlueLabel->setString(std::to_string(blueMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::yellowMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (yellowMobLevel == MAX_MOB_LEVEL)
        return;
    if (score >= yellowMobCost)
    {
        score -= yellowMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (yellowMobLevel == 1)
        {
            Mob::setYellowCost(2);
            yellowMobCost = 100;
        }
        else if (yellowMobLevel == 2)
        {
            Mob::setYellowCost(4);
            yellowMobCost = 200;
        }
        else if (yellowMobLevel == 3)
        {
            Mob::setYellowCost(8);
            yellowMobCost = 400;
        }
        else if (yellowMobLevel == 4)
        {
            Mob::setYellowCost(16);
            upgradeYellowLabel->setString("MAX");
            yellowMobLevel++;
            userLevels->setIntegerForKey("yellowMobLvl", yellowMobLevel);
            return;
        }
        yellowMobLevel++;
        userLevels->setIntegerForKey("yellowMobLvl", yellowMobLevel);
        upgradeYellowLabel->setString(std::to_string(yellowMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::purpleMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (purpleMobLevel == MAX_MOB_LEVEL)
        return;
    if (score >= purpleMobCost)
    {
        score -= purpleMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (purpleMobLevel == 1)
        {
            Mob::setPurpleCost(2);
            purpleMobCost = 100;
        }
        else if (purpleMobLevel == 2)
        {
            Mob::setPurpleCost(4);
            purpleMobCost = 200;
        }
        else if (purpleMobLevel == 3)
        {
            Mob::setPurpleCost(8);
            purpleMobCost = 400;
        }
        else if (purpleMobLevel == 4)
        {
            Mob::setPurpleCost(16);
            upgradePurpleLabel->setString("MAX");
            purpleMobLevel++;
            userLevels->setIntegerForKey("purpleMobLvl", purpleMobLevel);
            return;
        }
        purpleMobLevel++;
        userLevels->setIntegerForKey("purpleMobLvl", purpleMobLevel);
        upgradePurpleLabel->setString(std::to_string(purpleMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::greenMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (greenMobLevel == MAX_MOB_LEVEL)
        return;
    if (score >= greenMobCost)
    {
        score -= greenMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (greenMobLevel == 1)
        {
            Mob::setGreenCost(2);
            greenMobCost = 100;
        }
        else if (greenMobLevel == 2)
        {
            Mob::setGreenCost(4);
            greenMobCost = 200;
        }
        else if (greenMobLevel == 3)
        {
            Mob::setGreenCost(8);
            greenMobCost = 400;
        }
        else if (greenMobLevel == 4)
        {
            Mob::setGreenCost(16);
            upgradeGreenLabel->setString("MAX");
            greenMobLevel++;
            userLevels->setIntegerForKey("greenMobLvl", greenMobLevel);
            return;
        }
        greenMobLevel++;
        userLevels->setIntegerForKey("greenMobLvl", greenMobLevel);
        upgradeGreenLabel->setString(std::to_string(greenMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::superMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (superMobLevel == MAX_MOB_LEVEL)
        return;
    if (score >= superMobCost)
    {
        score -= superMobCost;
        GameScene::setScore(score);
        scoreLabel->setString(std::to_string(score));
        if (superMobLevel == 1)
        {
            Mob::setSuperCost(100);
            superMobCost = 250;
            Mob::setSuperLevel(2);
            superSprite->setTexture("colob_super_250.png");
        }
        else if (superMobLevel == 2)
        {
            Mob::setSuperCost(250);
            superMobCost = 550;
            Mob::setSuperLevel(3);
            superSprite->setTexture("colob_super_500.png");
        }
        else if (superMobLevel == 3)
        {
            Mob::setSuperCost(500);
            superMobCost = 1250;
            Mob::setSuperLevel(4);
            superSprite->setTexture("colob_super_1000.png");
        }
        else if (superMobLevel == 4)
        {
            Mob::setSuperCost(1000);
            superCostLabel->setString("MAX");
            superMobLevel++;
            userLevels->setIntegerForKey("superMobLvl", superMobLevel);
            Mob::setSuperLevel(5);
            return;
        }
        superMobLevel++;
        userLevels->setIntegerForKey("superMobLvl", superMobLevel);
        superCostLabel->setString(std::to_string(superMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::addMobBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (countOfAddedMobs == MAX_ADDED_MOBS)
        return;
    if (score >= addMobCost)
    {
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
            userLevels->setIntegerForKey("addedMobs", countOfAddedMobs);
            return;
        }
        GameScene::addMob();
        countOfAddedMobs++;
        userLevels->setIntegerForKey("addedMobs", countOfAddedMobs);
        addMobCostLabel->setString(std::to_string(addMobCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::speedUpgradeBought(cocos2d::Ref* sender)
{
    buySound->play2d("button_click_sound.mp3");
    if (speedLevel == MAX_LEVEL_SPEED)
        return;
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
        }
        else if (speedLevel == 2)
        {
            speedCost = 1000;
            Colob::setSpeed(250);
        }
        else if (speedLevel == 3)
        {
            speedCost = 2000;
            Colob::setSpeed(300);
        }
        else if (speedLevel == 4)
        {
            speedCostLabel->setString("MAX");
            Colob::setSpeed(350);
            speedLevel++;
            userLevels->setIntegerForKey("speedLvl", speedLevel);
            return;
        }
        speedLevel++;
        userLevels->setIntegerForKey("speedLvl", speedLevel);
        speedCostLabel->setString(std::to_string(speedCost));
    }
    else {
        spawnNotEnough();
    }
}

void ShopScene::loadInfo()
{
    //red
    redMobLevel = UserDefault::getInstance()->getIntegerForKey("redMobLvl", 1);
    if (redMobLevel == 2)
    {
        Mob::setRedCost(2);
        redMobCost = 100;
    }
    else if (redMobLevel == 3)
    {
        Mob::setRedCost(4);
        redMobCost = 200;
    }
    else if (redMobLevel == 4)
    {
        Mob::setRedCost(8);
        redMobCost = 400;
    }
    else if (redMobLevel == 5)
    {
        Mob::setRedCost(16);
    }

    //blue
    blueMobLevel = UserDefault::getInstance()->getIntegerForKey("blueMobLvl", 1);
    if (blueMobLevel == 2)
    {
        Mob::setBlueCost(2);
        blueMobCost = 100;
    }
    else if (blueMobLevel == 3)
    {
        Mob::setBlueCost(4);
        blueMobCost = 200;
    }
    else if (blueMobLevel == 4)
    {
        Mob::setBlueCost(8);
        blueMobCost = 400;
    }
    else if (blueMobLevel == 5)
    {
        Mob::setBlueCost(16);
    }

    //yellow
    yellowMobLevel = UserDefault::getInstance()->getIntegerForKey("yellowMobLvl", 1);
    if (yellowMobLevel == 2)
    {
        Mob::setYellowCost(2);
        yellowMobCost = 100;
    }
    else if (yellowMobLevel == 3)
    {
        Mob::setYellowCost(4);
        yellowMobCost = 200;
    }
    else if (yellowMobLevel == 4)
    {
        Mob::setYellowCost(8);
        yellowMobCost = 400;
    }
    else if (yellowMobLevel == 5)
    {
        Mob::setYellowCost(16);
    }

    //purple
    purpleMobLevel = UserDefault::getInstance()->getIntegerForKey("purpleMobLvl", 1);
    if (purpleMobLevel == 2)
    {
        Mob::setPurpleCost(2);
        purpleMobCost = 100;
    }
    else if (purpleMobLevel == 3)
    {
        Mob::setPurpleCost(4);
        purpleMobCost = 200;
    }
    else if (purpleMobLevel == 4)
    {
        Mob::setPurpleCost(8);
        purpleMobCost = 400;
    }
    else if (purpleMobLevel == 5)
    {
        Mob::setPurpleCost(16);
    }

    //green
    greenMobLevel = UserDefault::getInstance()->getIntegerForKey("greenMobLvl", 1);
    if (greenMobLevel == 2)
    {
        Mob::setGreenCost(2);
        greenMobCost = 100;
    }
    else if (greenMobLevel == 3)
    {
        Mob::setGreenCost(4);
        greenMobCost = 200;
    }
    else if (greenMobLevel == 4)
    {
        Mob::setGreenCost(8);
        greenMobCost = 400;
    }
    else if (greenMobLevel == 5)
    {
        Mob::setGreenCost(16);
    }
    
    //add mob
    countOfAddedMobs = UserDefault::getInstance()->getIntegerForKey("addedMobs", 0);
    if (countOfAddedMobs == 1)
    {
        addMobCost = 100;
        GameScene::addMob();
    }
    else if (countOfAddedMobs == 2)
    {
        addMobCost = 250;
        GameScene::addMob();
        GameScene::addMob();
    }
    else if (countOfAddedMobs == 3)
    {
        addMobCost = 500;
        for (int i = 0; i < 3; i++)
            GameScene::addMob();
    }
    else if (countOfAddedMobs == 4)
    {
        for(int i = 0; i < 4; i++)
          GameScene::addMob();
    }

    //speed
    speedLevel = UserDefault::getInstance()->getIntegerForKey("speedLvl", 1);
    if (speedLevel == 2)
    {
        speedCost = 500;
        Colob::setSpeed(200);
    }
    else if (speedLevel == 3)
    {
        speedCost = 1000;
        Colob::setSpeed(250);
    }
    else if (speedLevel == 4)
    {
        speedCost = 2000;
        Colob::setSpeed(300);
    }
    else if (speedLevel == 5)
    {
        Colob::setSpeed(350);
    }

    //super
    superMobLevel = UserDefault::getInstance()->getIntegerForKey("superMobLvl", 1);
    if (superMobLevel == 2)
    {
        Mob::setSuperCost(100);
        superMobCost = 250;
        Mob::setSuperLevel(2);
    }
    else if (superMobLevel == 3)
    {
        Mob::setSuperCost(250);
        superMobCost = 550;
        Mob::setSuperLevel(3);
    }
    else if (superMobLevel == 4)
    {
        Mob::setSuperCost(500);
        superMobCost = 1250;
        Mob::setSuperLevel(4);
    }
    else if (superMobLevel == 5)
    {
        Mob::setSuperCost(1000);
        Mob::setSuperLevel(5);
    }

    DesignScene::loadInfo();
}

void ShopScene::spawnNotEnough()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Label* noten = Label::createWithTTF("Not enough points", "fonts/MaldiniNormal-ZVKG3.ttf", 60);
    noten->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + visibleSize.height/2 + origin.y));
    noten->setColor(Color3B(220, 20, 60));
    this->addChild(noten);
    auto down_moving = MoveBy::create(1, Vec2(0, -150));
    noten->runAction(down_moving);
    list_noten.push_back(noten);
    CallFunc* runCallback = CallFunc::create(CC_CALLBACK_0(ShopScene::removeNoten, this));
    this->runAction(Sequence::create(DelayTime::create(1), runCallback, nullptr));
}

void ShopScene::removeNoten()
{
    this->removeChild(list_noten.front());
    list_noten.pop_front();
}

 void ShopScene::setScore(unsigned int tempscore)
{
    score = tempscore;
}

void ShopScene::updateScoreLabel()
{
    scoreLabel->setString(std::to_string(score));
}

int ShopScene::redMobLevel = 1;
int ShopScene::redMobCost = 50;

int ShopScene::yellowMobLevel = 1;
int ShopScene::yellowMobCost = 50;

int ShopScene::blueMobLevel = 1;
int ShopScene::blueMobCost = 50;

int ShopScene::greenMobLevel = 1;
int ShopScene::greenMobCost = 50;

int ShopScene::purpleMobLevel = 1;
int ShopScene::purpleMobCost = 50;

int ShopScene::countOfAddedMobs = 0;
int ShopScene::addMobCost = 50;

int ShopScene::speedLevel = 1;
int ShopScene::speedCost = 100;

int ShopScene::superMobLevel = 1;
int ShopScene::superMobCost = 125;

unsigned int ShopScene::score = 0;
Label* ShopScene::scoreLabel;