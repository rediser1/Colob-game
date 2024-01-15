#ifndef __GAME_SCENE_SCENE_H__
#define __GAME_SCENE_SCENE_H__

#include "cocos2d.h"
#include "Colob.h"
#include "Mob.h"
#include <vector>
#include "AudioEngine.h"
#include "RandomEvent.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int shopScore);

    virtual bool init();
    
    CREATE_FUNC(GameScene);

    void SpawnMob(float dt);
    void spawnRandomIvent(float dt);
    static void setScore(unsigned int tempscore);
    static int getScore();
    static void addMob();
    static void updateScoreLabel();
    static void setMusicStatus(bool status);
    static bool getMusicStatus();
    static void replaceBg(const char* newSpriteName);
    static void changeScoreColor(Color3B color);
private:
    static int mobsCount;
    static unsigned int score;
    static Label* scoreLabel;
    static int tag;

    void isMusicOnClick(cocos2d::Ref* sender);
    void killMob(int index);
    void explosion(int index);
    void multiplie(int index);
    void removeMob(int index);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void startShopScene(cocos2d::Ref* sender);
    void countCheking(float dt);
    void update(float dt);
    void killAllMobs(float dt);
    

    Colob *colob;
    std::vector<Mob> vec;
    static UserDefault* userScore;
    AudioEngine* sound;
    RandomEvent* randomIvent;
    static Sprite* bg1;
    static Sprite* bg2;
    static MenuItemImage* musicOnButton;
    Size visibleSize;
    Vec2 origin;
    
    int randomDelay;
    int mobsAlive;
    static bool isMusicOn;
};

#endif // __GAME_SCENE_SCENE_H__
