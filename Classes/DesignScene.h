#ifndef __DESIGN_SCENE_H__
#define __DESIGN_SCENE_H__

#include "cocos2d.h"
#include "Colob.h"
#include "AudioEngine.h"
#include <list>
#include "GameScene.h"

class DesignScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int tempScore);

    virtual bool init();

    CREATE_FUNC(DesignScene);

    static void loadInfo();
private:
    void resumeShopScene(cocos2d::Ref* sender);
    void resumeGameScene(cocos2d::Ref* sender);

    void setDefaultBg(cocos2d::Ref* sender);
    Label* bgDefaultCost;
    void buyBgLandscape(cocos2d::Ref* sender);
    static bool isLandscapeBought;
    Label* bgLandscapeCost;

    void buyBgScull(cocos2d::Ref* sender);
    static bool isScullBought;
    Label* bgScullCost;

    void buyRedSkin(cocos2d::Ref* sender);
    static bool isRedSkinBought;
    Label* redSkinCost;

    void buyNightSkin(cocos2d::Ref* sender);
    static bool isNightSkinBought;
    Label* nightSkinCost;

    void buySpaceSkin(cocos2d::Ref* sender);
    static bool isSpaceSkinBought;
    Label* spaceSkinCost;

    void buyDefaultSkin(cocos2d::Ref* sender);
    Label* defaultSkinCost;

    void buyBgTissue(cocos2d::Ref* sender);
    void buyBgSpace(cocos2d::Ref* sender);
    static bool isTissueBought;
    static bool isSpaceBought;
    Label* bgSpaceCost;
    Label* scoreLabel;
    Label* bgTissueCost;
    std::list<Label*> list_noten;
    UserDefault* userDesign;
    AudioEngine* sound;
    MenuItemImage* musicOnButton;
    static std::string selectedBg;
    static std::string selectedSkin;
    Size visibleSize;
    Vec2 origin;
    
};

#endif // __DESIGN_SCENE_H__
