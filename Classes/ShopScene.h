#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "Colob.h";
#include "Mob.h";
#include <vector>

class ShopScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(unsigned int tempScore);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(ShopScene);

private:
    void resumeGameScene(cocos2d::Ref* sender);

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

    Label* scoreLabel;

};

#endif // __SHOP_SCENE_H__
