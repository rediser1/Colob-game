#include "DesignScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "ShopScene.h"
#include "Colob.h"

USING_NS_CC;

unsigned int score2;
Scene* DesignScene::createScene(unsigned int tempScore)
{
    score2 = tempScore;
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = DesignScene::create();

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
bool DesignScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

   
     visibleSize = Director::getInstance()->getVisibleSize();
     origin = Director::getInstance()->getVisibleOrigin();
    userDesign = UserDefault::getInstance();

    auto bg = Sprite::create("shopbg.png");
    bg->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    this->addChild(bg);

    auto backGameButton = MenuItemImage::create("exit.png", "exit_clicked.png", CC_CALLBACK_1(DesignScene::resumeGameScene, this));
    backGameButton->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.1));
    auto backGame = Menu::create(backGameButton, NULL);
    backGame->setPosition(Point(0, 0));
    this->addChild(backGame);

    auto backButton = MenuItemImage::create("arrow_left.png", "arrow_left_clicked.png", CC_CALLBACK_1(DesignScene::resumeShopScene, this));
    backButton->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.18));
    auto back = Menu::create(backButton, NULL);
    back->setPosition(Point(0, 0));
    this->addChild(back);

    scoreLabel = Label::createWithTTF(std::to_string(score2), "fonts/MaldiniNormal-ZVKG3.ttf", 84);
    scoreLabel->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.9 + origin.y));
    scoreLabel->setColor(Color3B(65.0, 105.0, 225.0)); // purple 166.0, 94.0, 239.0
    this->addChild(scoreLabel, 1000);

    auto designLabel = Label::createWithTTF("Design", "fonts/Marker Felt.ttf", 70);
    designLabel->setPosition(Point(visibleSize.width * 0.8 + origin.x, visibleSize.height * 0.89 + origin.y));
    designLabel->setColor(Color3B(65, 105, 225));
    this->addChild(designLabel, 1000);

    auto line = Sprite::create("blue_line.png");
    line->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.8 + origin.y));
    this->addChild(line);

    auto bgLabel = Label::createWithTTF("Backgrounds", "fonts/Marker Felt.ttf", 40);
    bgLabel->setPosition(Point(visibleSize.width * 0.5 + origin.x,  visibleSize.height * 0.76 + origin.y));
    bgLabel->setColor(Color3B(65, 105, 225));
    this->addChild(bgLabel, 1000);

    //Tissue
    auto buyTissueButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyBgTissue, this));
    buyTissueButton->setPosition(Vec2(visibleSize.width * 0.12 + origin.x, visibleSize.height * 0.5 + origin.y));
    auto buyTissue = Menu::create(buyTissueButton, NULL);
    buyTissue->setPosition(Point(0, 0));
    this->addChild(buyTissue);

    if (isTissueBought == true && selectedBg != "Tissue")
        bgTissueCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 30);
    else if(isTissueBought == true && selectedBg == "Tissue")
        bgTissueCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 30);
    else
        bgTissueCost = Label::createWithTTF(std::to_string(2500), "fonts/Flix.ttf", 30);
    bgTissueCost->setPosition(Vec2(visibleSize.width * 0.12 + origin.x,  visibleSize.height * 0.5 + origin.y));
    bgTissueCost->setColor(Color3B(0, 0, 0));
    this->addChild(bgTissueCost);

    auto bgTissueSprite = Sprite::create("bg_tissue.png");
    bgTissueSprite->setScale(0.7);
    bgTissueSprite->setPosition(Vec2(visibleSize.width * 0.12 + origin.x, visibleSize.height * 0.65 + origin.y));
    this->addChild(bgTissueSprite);

    //Space
    auto buySpaceButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyBgSpace, this));
    buySpaceButton->setPosition(Vec2(visibleSize.width * 0.32 + origin.x, visibleSize.height * 0.5 + origin.y));
    auto buySpace = Menu::create(buySpaceButton, NULL);
    buySpace->setPosition(Point(0, 0));
    this->addChild(buySpace);

    if (isSpaceBought == true && selectedBg != "Space")
        bgSpaceCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 30);
    else if (isSpaceBought == true && selectedBg == "Space")
        bgSpaceCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 30);
    else
        bgSpaceCost = Label::createWithTTF(std::to_string(5000), "fonts/Flix.ttf", 30);
    bgSpaceCost->setPosition(Vec2(visibleSize.width * 0.32 + origin.x, visibleSize.height * 0.5 + origin.y));
    bgSpaceCost->setColor(Color3B(0, 0, 0));
    this->addChild(bgSpaceCost);

    auto bgSpaceSprite = Sprite::create("bg_space.png");
    bgSpaceSprite->setScale(0.34);
    bgSpaceSprite->setPosition(Vec2(visibleSize.width * 0.32 + origin.x, visibleSize.height * 0.65 + origin.y));
    this->addChild(bgSpaceSprite);

    //Landscape
    auto buyLandscapeButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyBgLandscape, this));
    buyLandscapeButton->setPosition(Vec2(visibleSize.width * 0.52 + origin.x,  visibleSize.height * 0.5 + origin.y));
    auto buyLandscape = Menu::create(buyLandscapeButton, NULL);
    buyLandscape->setPosition(Point(0, 0));
    this->addChild(buyLandscape);

    if (isLandscapeBought == true && selectedBg != "Landscape")
        bgLandscapeCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 30);
    else if (isLandscapeBought == true && selectedBg == "Landscape")
        bgLandscapeCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 30);
    else
        bgLandscapeCost = Label::createWithTTF(std::to_string(5000), "fonts/Flix.ttf", 30);
    bgLandscapeCost->setPosition(Vec2(visibleSize.width * 0.52 + origin.x,  visibleSize.height * 0.5 + origin.y));
    bgLandscapeCost->setColor(Color3B(0, 0, 0));
    this->addChild(bgLandscapeCost);

    auto bgLandscapeSprite = Sprite::create("bg_landscape.png");
    bgLandscapeSprite->setScale(0.17);
    bgLandscapeSprite->setPosition(Vec2(visibleSize.width * 0.52 + origin.x, visibleSize.height * 0.65 + origin.y));
    this->addChild(bgLandscapeSprite);

    //Scull
    auto buyScullButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyBgScull, this));
    buyScullButton->setPosition(Vec2(visibleSize.width * 0.72 + origin.x,  visibleSize.height * 0.5 + origin.y));
    auto buyScull = Menu::create(buyScullButton, NULL);
    buyScull->setPosition(Point(0, 0));
    this->addChild(buyScull);

    if (isScullBought == true && selectedBg != "Scull")
        bgScullCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 30);
    else if (isScullBought == true && selectedBg == "Scull")
        bgScullCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 30);
    else
        bgScullCost = Label::createWithTTF(std::to_string(5000), "fonts/Flix.ttf", 30);
    bgScullCost->setPosition(Vec2(visibleSize.width * 0.72 + origin.x,  visibleSize.height * 0.5 + origin.y));
    bgScullCost->setColor(Color3B(0, 0, 0));
    this->addChild(bgScullCost);

    auto bgScullSprite = Sprite::create("bg_scull.jpg");
    bgScullSprite->setScale(0.075);
    bgScullSprite->setPosition(Vec2(visibleSize.width * 0.72 + origin.x, visibleSize.height * 0.65 + origin.y));
    this->addChild(bgScullSprite);

    //default bg
    auto buyDefaultButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::setDefaultBg, this));
    buyDefaultButton->setPosition(Vec2(visibleSize.width * 0.92 + origin.x,  visibleSize.height * 0.5 + origin.y));
    auto buyDefault = Menu::create(buyDefaultButton, NULL);
    buyDefault->setPosition(Point(0, 0));
    this->addChild(buyDefault);

    if(selectedBg == "Default")
        bgDefaultCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 30);
    else
        bgDefaultCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 30);
    bgDefaultCost->setPosition(Vec2(visibleSize.width * 0.92 + origin.x,  visibleSize.height * 0.5 + origin.y));
    bgDefaultCost->setColor(Color3B(0, 0, 0));
    this->addChild(bgDefaultCost);

    auto bgDefaultSprite = Sprite::create("gamebg.png");
    bgDefaultSprite->setScale(0.065);
    bgDefaultSprite->setPosition(Vec2(visibleSize.width * 0.92 + origin.x,  visibleSize.height * 0.65 + origin.y));
    this->addChild(bgDefaultSprite);

    ////////SKINS SKINS SKINS SKINS SKINS SKINS /////////////

   //RED
    auto buyRedSkinButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyRedSkin, this));
    buyRedSkinButton->setPosition(Vec2(visibleSize.width * 0.48 + origin.x, visibleSize.height * 0.25 + origin.y));
    buyRedSkinButton->setScale(0.8);
    auto buyRedSkin = Menu::create(buyRedSkinButton, NULL);
    buyRedSkin->setPosition(Point(0, 0));
    this->addChild(buyRedSkin);

    if (isRedSkinBought == true && selectedSkin != "Red")
        redSkinCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 25);
    else if (isRedSkinBought == true && selectedSkin == "Red")
        redSkinCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 25);
    else
        redSkinCost = Label::createWithTTF(std::to_string(5000), "fonts/Flix.ttf", 25);
    redSkinCost->setPosition(Vec2(visibleSize.width * 0.48 + origin.x,  visibleSize.height * 0.25 + origin.y));
    redSkinCost->setColor(Color3B(0, 0, 0));
    this->addChild(redSkinCost);

    auto redSkinSprite = Sprite::create("colob_skin_red.png");
    redSkinSprite->setScale(0.33);
    redSkinSprite->setPosition(Vec2(visibleSize.width * 0.48 + origin.x,  visibleSize.height * 0.35 + origin.y));
    this->addChild(redSkinSprite);

    //NIGHT
    auto buyNightSkinButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyNightSkin, this));
    buyNightSkinButton->setPosition(Vec2(visibleSize.width * 0.24 + origin.x,  visibleSize.height * 0.25 + origin.y));
    buyNightSkinButton->setScale(0.8);
    auto buyNightSkin = Menu::create(buyNightSkinButton, NULL);
    buyNightSkin->setPosition(Point(0, 0));
    this->addChild(buyNightSkin);

    if (isNightSkinBought == true && selectedSkin != "Night")
        nightSkinCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 25);
    else if (isNightSkinBought == true && selectedSkin == "Night")
        nightSkinCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 25);
    else
        nightSkinCost = Label::createWithTTF(std::to_string(5000), "fonts/Flix.ttf", 25);
    nightSkinCost->setPosition(Vec2(visibleSize.width * 0.24 + origin.x,  visibleSize.height * 0.25 + origin.y));
    nightSkinCost->setColor(Color3B(0, 0, 0));
    this->addChild(nightSkinCost);

    auto nightSkinSprite = Sprite::create("skin_night2.png");
    nightSkinSprite->setPosition(Vec2(visibleSize.width * 0.24 + origin.x,  visibleSize.height * 0.35 + origin.y));
    nightSkinSprite->setScale(0.33);
    this->addChild(nightSkinSprite);

    //SPACE
    auto buySpaceSkinButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buySpaceSkin, this));
    buySpaceSkinButton->setPosition(Vec2(visibleSize.width * 0.36 + origin.x, visibleSize.height * 0.25 + origin.y));
    buySpaceSkinButton->setScale(0.8);
    auto buySpaceSkin = Menu::create(buySpaceSkinButton, NULL);
    buySpaceSkin->setPosition(Point(0, 0));
    this->addChild(buySpaceSkin);

    if (isSpaceSkinBought == true && selectedSkin != "Space")
        spaceSkinCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 25);
    else if (isSpaceSkinBought == true && selectedSkin == "Space")
        spaceSkinCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 25);
    else
        spaceSkinCost = Label::createWithTTF(std::to_string(5000), "fonts/Flix.ttf", 25);
    spaceSkinCost->setPosition(Vec2(visibleSize.width * 0.36 + origin.x, visibleSize.height * 0.25 + origin.y));
    spaceSkinCost->setColor(Color3B(0, 0, 0));
    this->addChild(spaceSkinCost);

    auto spaceSkinSprite = Sprite::create("space_skin.png");
    spaceSkinSprite->setPosition(Vec2(visibleSize.width * 0.36 + origin.x, visibleSize.height * 0.35 + origin.y));
    spaceSkinSprite->setScale(0.33);
    this->addChild(spaceSkinSprite);

    //DEFAULT

    auto buyDefaultSkinButton = MenuItemImage::create("shop_button.png", "shop_button_clicked.png", CC_CALLBACK_1(DesignScene::buyDefaultSkin, this));
    buyDefaultSkinButton->setPosition(Vec2(visibleSize.width * 0.12 + origin.x, visibleSize.height * 0.25 + origin.y));
    buyDefaultSkinButton->setScale(0.8);
    auto buyDefaultSkin = Menu::create(buyDefaultSkinButton, NULL);
    buyDefaultSkin->setPosition(Point(0, 0));
    this->addChild(buyDefaultSkin);

    if (selectedSkin != "Default")
        defaultSkinCost = Label::createWithTTF("Click to set", "fonts/Flix.ttf", 25);
    else if ( selectedSkin == "Default")
        defaultSkinCost = Label::createWithTTF("Selected", "fonts/Flix.ttf", 25);
    defaultSkinCost->setPosition(Vec2(visibleSize.width * 0.12 + origin.x, visibleSize.height * 0.25 + origin.y));
    defaultSkinCost->setColor(Color3B(0, 0, 0));
    this->addChild(defaultSkinCost);

    auto defaultSkinSprite = Sprite::create("colob_new.png");
    defaultSkinSprite->setPosition(Vec2(visibleSize.width * 0.12 + origin.x, visibleSize.height * 0.35 + origin.y));
    defaultSkinSprite->setScale(0.33);
    this->addChild(defaultSkinSprite);

    return true;
}

void DesignScene::resumeShopScene(cocos2d::Ref* sender)
{
    sound->play2d("go_some_scene.mp3");
    ShopScene::setScore(score2);
    ShopScene::updateScoreLabel();
    Director::getInstance()->popScene();

}

void DesignScene::buyBgTissue(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isTissueBought == true)
    {
        if (selectedBg == "Tissue")
            return;
        else
        {
            GameScene::replaceBg("bg_tissue.png");
            if(selectedBg == "Landscape" || selectedBg == "Space")
                GameScene::changeScoreColor(Color3B(245, 245, 220));
            selectedBg = "Tissue";
            bgTissueCost->setString("Selected");
            userDesign->setStringForKey("selectedBg", "Tissue");
            if(isSpaceBought == true)
               bgSpaceCost->setString("Click to set");
            if(isLandscapeBought == true)
               bgLandscapeCost->setString("Click to set");
            if (isScullBought == true)
                bgScullCost->setString("Click to set");
            bgDefaultCost->setString("Click to set");
            return;
        }
    }
   
    if (score2 >= 2500)
    {
        score2 -= 2500;
        scoreLabel->setString(std::to_string(score2));
        bgTissueCost->setString("Selected");
        GameScene::replaceBg("bg_tissue.png");
        isTissueBought = true;
        userDesign->setBoolForKey("isTissueBought", true);
        if (selectedBg == "Landscape" || selectedBg == "Space")
            GameScene::changeScoreColor(Color3B(245, 245, 220));
        selectedBg = "Tissue";
        userDesign->setStringForKey("selectedBg", "Tissue");
        if (isSpaceBought == true)
            bgSpaceCost->setString("Click to set");
        if (isLandscapeBought == true)
            bgLandscapeCost->setString("Click to set");
        if (isScullBought == true)
            bgScullCost->setString("Click to set");
        bgDefaultCost->setString("Click to set");
    }
}

void DesignScene::buyBgSpace(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isSpaceBought == true)
    {
        if (selectedBg == "Space")
            return;
        else
        {
            GameScene::replaceBg("bg_space.png");
            selectedBg = "Space";
            bgSpaceCost->setString("Selected");
            userDesign->setStringForKey("selectedBg", "Space");
            GameScene::changeScoreColor(Color3B(65, 105, 225));
            if (isTissueBought == true)
                bgTissueCost->setString("Click to set");
            if (isLandscapeBought == true)
                bgLandscapeCost->setString("Click to set");
            if (isScullBought == true)
                bgScullCost->setString("Click to set");
            bgDefaultCost->setString("Click to set");
            return;
        }
    }

    if (score2 >= 5000)
    {
        score2 -= 5000;
        scoreLabel->setString(std::to_string(score2));
        bgSpaceCost->setString("Selected");
        GameScene::replaceBg("bg_space.png");
        isSpaceBought = true;
        userDesign->setBoolForKey("isSpaceBought", true);
        selectedBg = "Space";
        userDesign->setStringForKey("selectedBg", "Space");
        GameScene::changeScoreColor(Color3B(65, 105, 225));
        if (isTissueBought == true)
            bgTissueCost->setString("Click to set");
        if (isLandscapeBought == true)
            bgLandscapeCost->setString("Click to set");
        if (isScullBought == true)
            bgScullCost->setString("Click to set");
        bgDefaultCost->setString("Click to set");
    }
}

void DesignScene::buyBgLandscape(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isLandscapeBought == true)
    {
        if (selectedBg == "Landscape")
            return;
        else
        {
            GameScene::replaceBg("bg_landscape.png");
            selectedBg = "Landscape";
            bgLandscapeCost->setString("Selected");
            userDesign->setStringForKey("selectedBg", "Landscape");
            GameScene::changeScoreColor(Color3B(65, 105, 225));
            if (isTissueBought == true)
                bgTissueCost->setString("Click to set");
            if (isSpaceBought == true)
                bgSpaceCost->setString("Click to set");
            if (isScullBought == true)
                bgScullCost->setString("Click to set");
            bgDefaultCost->setString("Click to set");
            return;
        }
    }

    if (score2 >= 5000)
    {
        score2 -= 5000;
        scoreLabel->setString(std::to_string(score2));
        bgLandscapeCost->setString("Selected");
        GameScene::replaceBg("bg_landscape.png");
        GameScene::changeScoreColor(Color3B(65, 105, 225));
        isLandscapeBought = true;
        userDesign->setBoolForKey("isLandscapeBought", true);
        selectedBg = "Landscape";
        userDesign->setStringForKey("selectedBg", "Landscape");
        if (isTissueBought == true)
            bgTissueCost->setString("Click to set");
        if (isSpaceBought == true)
            bgSpaceCost->setString("Click to set");
        if (isScullBought == true)
            bgScullCost->setString("Click to set");
        bgDefaultCost->setString("Click to set");
    }
}

void DesignScene::buyBgScull(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isScullBought == true)
    {
        if (selectedBg == "Scull")
            return;
        else
        {
            GameScene::replaceBg("bg_scull.jpg");
            if (selectedBg == "Landscape" || selectedBg == "Space")
                GameScene::changeScoreColor(Color3B(245, 245, 220));
            selectedBg = "Scull";
            bgScullCost->setString("Selected");
            userDesign->setStringForKey("selectedBg", "Scull");
            if (isTissueBought == true)
                bgTissueCost->setString("Click to set");
            if (isSpaceBought == true)
                bgSpaceCost->setString("Click to set");
            if (isLandscapeBought == true)
                bgLandscapeCost->setString("Click to set");
            bgDefaultCost->setString("Click to set");
            return;
        }
    }

    if (score2 >= 5000)
    {
        score2 -= 5000;
        scoreLabel->setString(std::to_string(score2));
        bgScullCost->setString("Selected");
        GameScene::replaceBg("bg_scull.jpg");
        isLandscapeBought = true;
        userDesign->setBoolForKey("isScullBought", true);
        if (selectedBg == "Landscape" || selectedBg == "Space")
            GameScene::changeScoreColor(Color3B(245, 245, 220));
        selectedBg = "Scull";
        userDesign->setStringForKey("selectedBg", "Scull");
        if (isTissueBought == true)
            bgTissueCost->setString("Click to set");
        if (isSpaceBought == true)
            bgSpaceCost->setString("Click to set");
        if (isLandscapeBought == true)
            bgLandscapeCost->setString("Click to set");
        bgDefaultCost->setString("Click to set");
    }
}

void DesignScene::setDefaultBg(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (selectedBg == "Deafult")
        return;
    else
    {
        GameScene::replaceBg("gamebg.png");
        if (selectedBg == "Landscape" || selectedBg == "Space")
            GameScene::changeScoreColor(Color3B(245, 245, 220));
        selectedBg = "Default";
        bgDefaultCost->setString("Selected");
        userDesign->setStringForKey("selectedBg", "Default");
        if (isTissueBought == true)
            bgTissueCost->setString("Click to set");
        if (isSpaceBought == true)
            bgSpaceCost->setString("Click to set");
        if (isLandscapeBought == true)
            bgLandscapeCost->setString("Click to set");
        if (isScullBought == true)
            bgScullCost->setString("Click to set");
    }
}

void DesignScene::buyRedSkin(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isRedSkinBought == true)
    {
        if (selectedSkin == "Red")
            return;
        else
        {
            Colob::changeSprite("colob_skin_red.png");
            selectedSkin = "Red";
            redSkinCost->setString("Selected");
            userDesign->setStringForKey("selectedSkin", "Red");
            if (isNightSkinBought == true)
                nightSkinCost->setString("Click to set");
            if (isSpaceSkinBought == true)
                spaceSkinCost->setString("Click to set");
                defaultSkinCost->setString("Click to set");
            return;
        }
    }

    if (score2 >= 2500)
    {
        score2 -= 2500;
        scoreLabel->setString(std::to_string(score2));
        redSkinCost->setString("Selected");
        Colob::changeSprite("colob_skin_red.png");
        isRedSkinBought = true;
        userDesign->setBoolForKey("isRedSkinBought", true);
        selectedSkin = "Red";
        userDesign->setStringForKey("selectedSkin", "Red");
        if (isNightSkinBought == true)
            nightSkinCost->setString("Click to set");
        if (isSpaceSkinBought == true)
            spaceSkinCost->setString("Click to set");
        defaultSkinCost->setString("Click to set");
    }
}

void DesignScene::buyNightSkin(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isNightSkinBought == true)
    {
        if (selectedSkin == "Night")
            return;
        else
        {
            Colob::changeSprite("skin_night2.png");
            selectedSkin = "Night";
            nightSkinCost->setString("Selected");
            userDesign->setStringForKey("selectedSkin", "Night");
            if (isRedSkinBought == true)
                redSkinCost->setString("Click to set");
            if (isSpaceSkinBought == true)
                spaceSkinCost->setString("Click to set");
                defaultSkinCost->setString("Click to set");
            return;
        }
    }

    if (score2 >= 2500)
    {
        score2 -= 2500;
        scoreLabel->setString(std::to_string(score2));
        nightSkinCost->setString("Selected");
        Colob::changeSprite("skin_night2.png");
        isNightSkinBought = true;
        userDesign->setBoolForKey("isNightSkinBought", true);
        selectedSkin = "Night";
        userDesign->setStringForKey("selectedSkin", "Night");
        if (isRedSkinBought == true)
            redSkinCost->setString("Click to set");
        if (isSpaceSkinBought == true)
            spaceSkinCost->setString("Click to set");
        defaultSkinCost->setString("Click to set");
    }
}

void DesignScene::buySpaceSkin(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");
    if (isSpaceSkinBought == true)
    {
        if (selectedSkin == "Space")
            return;
        else
        {
            Colob::changeSprite("space_skin.png");
            selectedSkin = "Space";
            spaceSkinCost->setString("Selected");
            userDesign->setStringForKey("selectedSkin", "Space");
            if (isRedSkinBought == true)
                redSkinCost->setString("Click to set");
            if (isNightSkinBought == true)
                nightSkinCost->setString("Click to set");
            defaultSkinCost->setString("Click to set");
            return;
        }
    }

    if (score2 >= 2500)
    {
        score2 -= 2500;
        scoreLabel->setString(std::to_string(score2));
        spaceSkinCost->setString("Selected");
        Colob::changeSprite("space_skin.png");
        isSpaceSkinBought = true;
        userDesign->setBoolForKey("isSpaceSkinBought", true);
        selectedSkin = "Space";
        userDesign->setStringForKey("selectedSkin", "Space");
        if (isRedSkinBought == true)
            redSkinCost->setString("Click to set");
        if (isNightSkinBought == true)
            nightSkinCost->setString("Click to set");
        defaultSkinCost->setString("Click to set");
    }
}

void DesignScene::buyDefaultSkin(cocos2d::Ref* sender)
{
    sound->play2d("button_click_sound.mp3");

    if (selectedSkin == "Default")
        return;
    else
        {
        Colob::changeSprite("colob_new.png");
        selectedSkin = "DefaultSkin";
        defaultSkinCost->setString("Selected");
        userDesign->setStringForKey("selectedSkin", "Default");
        if (isRedSkinBought == true)
            redSkinCost->setString("Click to set");
        if (isNightSkinBought == true)
             nightSkinCost->setString("Click to set");
        if (isSpaceSkinBought == true)
            spaceSkinCost->setString("Click to set");
        return;
        }
}

 void DesignScene::loadInfo()
{
     isTissueBought = UserDefault::getInstance()->getBoolForKey("isTissueBought", false);
     isSpaceBought = UserDefault::getInstance()->getBoolForKey("isSpaceBought", false);
     isLandscapeBought = UserDefault::getInstance()->getBoolForKey("isLandscapeBought", false);
     isScullBought = UserDefault::getInstance()->getBoolForKey("isLandscapeBought", false);
     isRedSkinBought = UserDefault::getInstance()->getBoolForKey("isRedSkinBought", false);
     isNightSkinBought = UserDefault::getInstance()->getBoolForKey("isNightSkinBought", false);
     isSpaceSkinBought = UserDefault::getInstance()->getBoolForKey("isSpaceSkinBought", false);

     selectedBg = UserDefault::getInstance()->getStringForKey("selectedBg");
     if(selectedBg == "Tissue")
         GameScene::replaceBg("bg_tissue.png");
     else if (selectedBg == "Space")
     {
         GameScene::replaceBg("bg_space.png");
         GameScene::changeScoreColor(Color3B(65, 105, 225));
     }
     else if (selectedBg == "Landscape")
     {
         GameScene::replaceBg("bg_landscape.png");
         GameScene::changeScoreColor(Color3B(65, 105, 225));
     }
     else if (selectedBg == "Scull")
     {
         GameScene::replaceBg("bg_scull.jpg");
     }
     else
     {
         GameScene::replaceBg("gamebg.png");
     }

     if (selectedSkin == "Red")
         Colob::changeSprite("colob_skin_red.png");
     else if(selectedSkin == "Night")
         Colob::changeSprite("skin_night2.png");
     else if (selectedSkin == "Space")
         Colob::changeSprite("space_skin.png");

}


 void DesignScene::resumeGameScene(cocos2d::Ref* sender)
 {
     sound->play2d("go_some_scene.mp3");
     GameScene::setScore(score2);
     GameScene::updateScoreLabel();
     Director::getInstance()->popScene();
     Director::getInstance()->popScene();
 }

 bool DesignScene::isTissueBought = false;
 bool DesignScene::isSpaceBought = false;
 bool DesignScene::isLandscapeBought = false;
 bool DesignScene::isScullBought = false;
 bool DesignScene::isRedSkinBought = false;
 bool DesignScene::isNightSkinBought = false;
 bool DesignScene::isSpaceSkinBought = false;
 std::string DesignScene::selectedBg = "Default";
 std::string DesignScene::selectedSkin = "Default";