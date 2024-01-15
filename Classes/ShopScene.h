#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "Colob.h"
#include "AudioEngine.h"
#include <list>
#include "GameScene.h"

class ShopScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int tempScore);

    virtual bool init();

    CREATE_FUNC(ShopScene);

    static void loadInfo();
    static void setScore(unsigned int tempscore);
    static void updateScoreLabel();
private:
    void resumeGameScene(cocos2d::Ref* sender);
    void isMusicOnClick(cocos2d::Ref* sender);
    void goDesignScene(cocos2d::Ref* sender);

    //red
    void redMobBought(cocos2d::Ref* sender);
    static int redMobLevel;
    static int redMobCost;
    Label* upgradeRedLabel;

    //blue
    void blueMobBought(cocos2d::Ref* sender);
    static int blueMobLevel;
    static int blueMobCost;
    Label* upgradeBlueLabel;

    //green
    void greenMobBought(cocos2d::Ref* sender);
    static int greenMobLevel;
    static int greenMobCost;
    Label* upgradeGreenLabel;

    //purple
    void purpleMobBought(cocos2d::Ref* sender);
    static int purpleMobLevel;
    static int purpleMobCost;
    Label* upgradePurpleLabel;

    //yellow
    void yellowMobBought(cocos2d::Ref* sender);
    static int yellowMobLevel;
    static int yellowMobCost;
    Label* upgradeYellowLabel;

    //+1 mob
    void addMobBought(cocos2d::Ref* sender);
    static int countOfAddedMobs;
    static int addMobCost;
    Label* addMobCostLabel;
    
    //+speed
    void speedUpgradeBought(cocos2d::Ref* sender);
    static int speedLevel;
    static int speedCost;
    Label* speedCostLabel;

    void superMobBought(cocos2d::Ref* sender);
    static int superMobLevel;
    static int superMobCost;
    Label* superCostLabel;
    Sprite* superSprite;

    static Label* scoreLabel;
    std::list<Label*> list_noten;
    UserDefault* userLevels;
    AudioEngine* buySound;
    MenuItemImage* musicOnButton;
    static unsigned int score;

    void spawnNotEnough();
    void removeNoten();
    bool isMusicOn = true;
};

#endif // __SHOP_SCENE_H__
