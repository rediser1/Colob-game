
#ifndef __GAME_SCENE_SCENE_H__
#define __GAME_SCENE_SCENE_H__

#include "cocos2d.h"
#include "Colob.h";
#include "Mob.h";
#include <map>
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

private:

    void SpawnMob(float dt);
    void killMob(int index);
    void killingMobs(float dt);
    static int tag;
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    Colob *colob;
    std::vector<Mob> vec;
    
};

#endif // __GAME_SCENE_SCENE_H__
