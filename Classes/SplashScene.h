
#ifndef __SPLASHSCENE_SCENE_H__
#define __SPLASHSCENE_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
private:

    void GoToMainMenuScene(float dt);
};

#endif // __SPLASHSCENE_SCENE_H__
