
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "AudioEngine.h"
#include "cocos2d.h"
#include "Colob.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

    static void stopMusic();
    static void startMusic();

private:
    void GoToGameScene(cocos2d::Ref* sender);
    static AudioEngine* audio;
    static int id;
};

#endif // __MAINMENU_SCENE_H__
