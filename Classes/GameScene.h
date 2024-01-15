#ifndef __GAME_SCENE_SCENE_H__
#define __GAME_SCENE_SCENE_H__

#include "cocos2d.h"
#include "Colob.h";
#include "Mob.h";
#include <vector>

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void SpawnMob(float dt);

    static void setScore(unsigned int tempscore);

    static void addMob();
private:
    static int mobsCount;

    int mobsAlive;

    static unsigned int score;

    void killMob(int index);

    bool onContactBegin(cocos2d::PhysicsContact& contact);

    void startShopScene(cocos2d::Ref* sender);
    
    static int tag;

    void countCheking(float dt);

    Colob *colob;

    std::vector<Mob> vec;

    Label* scoreLabel;

    
    
};

#endif // __GAME_SCENE_SCENE_H__
