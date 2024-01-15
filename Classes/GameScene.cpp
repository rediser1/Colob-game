#include "GameScene.h"
#include "Colob.h"
#include "ui/CocosGUI.h"
#include "Mob.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "ShopScene.h"
#include "RandomEvent.h"
#include "MainMenuScene.h"

USING_NS_CC;


Scene* GameScene::createScene(unsigned int shopScore)
{
    score = shopScore;
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
     //////////////////////////////
     // 1. super init first
     if (!Layer::init())
     {
         return false;
     }


     visibleSize = Director::getInstance()->getVisibleSize();
     origin = Director::getInstance()->getVisibleOrigin();

     bg1 = Sprite::create("gamebg.png");
     bg1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
     bg1->setScale(visibleSize.width / bg1->getContentSize().width, visibleSize.height / bg1->getContentSize().height);

     bg2 = Sprite::create("gamebg.png");
     bg2->setScale(visibleSize.width / bg2->getContentSize().width, visibleSize.height / bg2->getContentSize().height);
     bg2->setPosition(Point(roundf(visibleSize.width * 1.5 + origin.x), visibleSize.height / 2 + origin.y));

     this->addChild(bg1);
     this->addChild(bg2);

     auto bgAction1 = RepeatForever::create(MoveBy::create(26.0f, Vec2(-visibleSize.width, 0)));
     bg1->runAction(bgAction1);

     auto bgAction2 = RepeatForever::create(MoveBy::create(26.0f, Vec2(-visibleSize.width, 0)));
     bg2->runAction(bgAction2);
     this->scheduleUpdate();

     colob = new Colob(this);

     //button left
     auto left_button = ui::Button::create("button_left_shared.png", "button_left_clicked.png");
     left_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
         switch (type)
         {
         case ui::Widget::TouchEventType::BEGAN:
         {
             colob->moveleft(1);
         }
         break;
         case ui::Widget::TouchEventType::CANCELED:
         {
             colob->stopmovingleft();
             break;
         }
         case ui::Widget::TouchEventType::MOVED:
         {
             break;
         }
         case ui::Widget::TouchEventType::ENDED:
             colob->stopmovingleft();
             break;
         default:
             break;
         }
         });

     left_button->setPosition(Point(visibleSize.width * 0.1 + origin.x, visibleSize.height * 0.2 + origin.y)); //visibleSize.width / 5.75
     this->addChild(left_button, 2);

     //button right

     auto right_button = ui::Button::create("button_right_shared.png", "button_right_clicked.png");
     right_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
        {
            colob->moveright(1);
        }
        break;
        case ui::Widget::TouchEventType::CANCELED:
            colob->stopmovingright();
            break;
        case ui::Widget::TouchEventType::MOVED:
            break;
        case ui::Widget::TouchEventType::ENDED:
            colob->stopmovingright();
            break;
        default:
            break;
        }
        });

     right_button->setPosition(Point(visibleSize.width * 0.18 + origin.x, visibleSize.height * 0.2 + origin.y)); // visibleSize.width / 4
     this->addChild(right_button, 2);

     //button up

     auto up_button = ui::Button::create("button_up_shared.png", "button_up_clicked.png");
     up_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
        {
            colob->moveup(1);
        }
        break;
        case ui::Widget::TouchEventType::CANCELED:
        {
            colob->stopmovingup();
            break;
        }
        case ui::Widget::TouchEventType::MOVED:
        {
            break;
        }
        case ui::Widget::TouchEventType::ENDED:
            colob->stopmovingup();
            break;
        default:
           break;
        }
        });

     up_button->setPosition(Point(visibleSize.width * 0.14 + origin.x, visibleSize.height * 0.27 + origin.y)); // (visibleSize.width / 4.725
     this->addChild(up_button, 2);

     //button down

     auto down_button = ui::Button::create("button_down_shared.png", "button_down_clicked.png");
     down_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
        {
            colob->movedown(1);
        }
        break;
        case ui::Widget::TouchEventType::CANCELED:
        {
            colob->stopmovingdown();
            break;
        }
        case ui::Widget::TouchEventType::MOVED:
        {
            break;
        }
        case ui::Widget::TouchEventType::ENDED:
            colob->stopmovingdown();
            break;
        default:
            break;
        }
        });

     down_button->setPosition(Point(visibleSize.width * 0.14 + origin.x, (up_button->getPositionY() -(up_button->getPositionY() - right_button->getPositionY()) * 2))); //visibleSize.width / 4.725
     this->addChild(down_button, 2);

     vec.reserve(40);
     GameScene::SpawnMob(0.1f);
     GameScene::SpawnMob(0.1f);
     GameScene::SpawnMob(0.1f);
     GameScene::SpawnMob(0.1f);
     GameScene::SpawnMob(0.1f);

     auto contactListener = EventListenerPhysicsContact::create();
     contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
     Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

     scoreLabel = Label::createWithTTF(std::to_string(score), "fonts/MaldiniNormal-ZVKG3.ttf", 84);
     scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.9 + origin.y));
     scoreLabel->setColor(Color3B(245, 245, 220));
     this->addChild(scoreLabel, 1000);

     auto edgeBody = PhysicsBody::createEdgeBox(visibleSize * 1.05, PhysicsMaterial(1, 1, 1), 26); 
     edgeBody->setCollisionBitmask(EDGE_COLLISION_BITMASK);
     edgeBody->setContactTestBitmask(true);

     auto edgeNode = Node::create();
     edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
     edgeNode->setPhysicsBody(edgeBody);
     this->addChild(edgeNode);


     auto shopButton = MenuItemImage::create("shop.png", "shop_clicked.png", CC_CALLBACK_1(GameScene::startShopScene, this));
     shopButton->setPosition(Vec2(origin.x + visibleSize.width * 0.9,  origin.y + visibleSize.height / 4));
     auto shop = Menu::create(shopButton, NULL);
     shop->setPosition(Point(0, 0));

     this->schedule(CC_SCHEDULE_SELECTOR(GameScene::countCheking));
     this->addChild(shop, 1);
     randomDelay = cocos2d::RandomHelper::random_int(20, 30);
     this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnRandomIvent), randomDelay);
     userScore = UserDefault::getInstance();
     userScore->setIntegerForKey("myScore", score);

     if(isMusicOn == true)
         musicOnButton = MenuItemImage::create("music_on.png", "music_off.png", CC_CALLBACK_1(GameScene::isMusicOnClick, this));
     else
         musicOnButton = MenuItemImage::create("music_off.png", "music_on.png", CC_CALLBACK_1(GameScene::isMusicOnClick, this));
     musicOnButton->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95));
     musicOnButton->setSelectedImage(Sprite::create("music_off.png"));
     auto musicOn = Menu::create(musicOnButton, NULL);
     musicOn->setPosition(Point(0, 0));
     this->addChild(musicOn, 2);

     ShopScene::loadInfo();
 
     return true;
}

bool GameScene::getMusicStatus()
{
     return isMusicOn;
}

 void GameScene::setMusicStatus(bool status)
 {
     isMusicOn = status;
     if (isMusicOn == false)
     {
         musicOnButton->setSelectedImage(Sprite::create("music_on.png"));
         musicOnButton->setNormalImage(Sprite::create("music_off.png"));
     }
     else {
         musicOnButton->setSelectedImage(Sprite::create("music_off.png"));
         musicOnButton->setNormalImage(Sprite::create("music_on.png"));
     }
 }

void GameScene::isMusicOnClick(cocos2d::Ref* sender)
{
    if (isMusicOn == true)
    {
        MainMenuScene::stopMusic();
        musicOnButton->setSelectedImage(Sprite::create("music_on.png"));
        musicOnButton->setNormalImage(Sprite::create("music_off.png"));
        isMusicOn = false;
    }
    else {
        MainMenuScene::startMusic();
        musicOnButton->setSelectedImage(Sprite::create("music_off.png"));
        musicOnButton->setNormalImage(Sprite::create("music_on.png"));
        isMusicOn = true;
    }
}

void GameScene::update(float dt)
{
    int currentposbg1 = bg1->getPosition().x - visibleSize.width / 2;
    int currentposbg2 = bg2->getPosition().x - visibleSize.width / 2;

   for (int i = 0; i < 5; i++)
   {
       if (roundf(bg1->getPosition().x - visibleSize.width / 2 - i) <= -visibleSize.width)
       {
           if (currentposbg2 == 0)
           {
               bg1->setPosition(Point(roundf(visibleSize.width * 1.5 + origin.x), visibleSize.height / 2 + origin.y));
               return;
           }
       }
       if (roundf(bg2->getPosition().x - visibleSize.width / 2 - i) <= -visibleSize.width)
       {
           if (currentposbg1 == 0)
           {
               bg2->setPosition(Point(roundf(visibleSize.width * 1.5 + origin.x), visibleSize.height / 2 + origin.y));
               return;
           }
       }
   }
}

void GameScene::removeMob(int index)
{
    sound->play2d("kill_mob_sound2.mp3", false, 0.5f);
    vec[index].mobs_count -= 1;
    vec.at(index).deleteSprite();
    int vecsize = vec.size();
    if (index != (vecsize - 1))
    {
        std::swap(vec[index], vec[vecsize - 1]);
    }

    if (vec.size() > 0)
    {
        vec[index].setTag(index);
    }
    vec.pop_back();
    mobsAlive--;
}

int GameScene::getScore()
{
     return score;
}

void GameScene::updateScoreLabel()
{
    scoreLabel->setString(std::to_string(score));
}

void GameScene::spawnRandomIvent(float dt)
{
    RandomEvent* ri = new RandomEvent(this);
    randomIvent = ri;
    randomIvent->spawnRandomIvent();
    ri = nullptr;
    delete ri;
}

void GameScene::countCheking(float dt)
{
    if (mobsAlive < mobsCount)
        GameScene::SpawnMob(0);
}

void GameScene::addMob()
{
    mobsCount++;
}

void GameScene::setScore(unsigned int tempscore)
{
    score = tempscore;
    userScore->setIntegerForKey("myScore", score);
}

void GameScene::startShopScene(cocos2d::Ref* sender)
{
    auto scene = ShopScene::createScene(score);
    Director::getInstance()->pushScene(scene);
}

void GameScene::SpawnMob(float dt)
{
    Mob mob;
    mob.spawnMob(this);
    vec.push_back(mob);
    mobsAlive++;
} 

void GameScene::killMob(int index)
{
    sound->play2d("kill_mob_sound2.mp3", false, 0.5f);
    vec[index].mobs_count -= 1;
    //add n points
    score += vec.at(index).cost;
    userScore->setIntegerForKey("myScore", score);
    vec.at(index).deleteSprite();
    int vecsize = vec.size();
    if (index != (vecsize - 1))
    {
        std::swap(vec[index], vec[vecsize - 1]);
    }

    if (vec.size() > 0)
    {
        vec[index].setTag(index);
    }
    vec.pop_back();
    scoreLabel->setString(std::to_string(score));
    mobsAlive--;
}

void GameScene::explosion(int index)
{
    vec[index].mobs_count -= 1;
    vec.at(index).deleteSprite();
    int vecsize = vec.size();
    if (index != (vecsize - 1))
    {
        std::swap(vec[index], vec[vecsize - 1]);
    }

    if (vec.size() > 0)
    {
        vec[index].setTag(index);
    }
    vec.pop_back();
    mobsAlive--;
    sound->play2d("explosion.mp3", false, 0.8f);

    //animation
    auto bgExplosionRight1 = MoveBy::create(0.03, Vec2(-150, 0));
    auto bgExplosionRight2 = MoveBy::create(0.03, Vec2(-150, 0));

    auto bgExplosionLeft1 = MoveBy::create(0.03, Vec2(150, 0));
    auto bgExplosionLeft2 = MoveBy::create(0.03, Vec2(150, 0));

    DelayTime* pause = DelayTime::create(1.3);
    DelayTime* between = DelayTime::create(0.03);
    DelayTime* secAction = DelayTime::create(1.4);
    DelayTime* thirdAction = DelayTime::create(1.5);
    DelayTime* fAction = DelayTime::create(1.6);

    bg1->runAction(Sequence::create(pause, bgExplosionLeft1, between, bgExplosionRight1, NULL));
    bg2->runAction(Sequence::create(pause, bgExplosionLeft2, between, bgExplosionRight2, NULL));

    bg1->runAction(Sequence::create(secAction, bgExplosionLeft1, between, bgExplosionRight1, NULL));
    bg2->runAction(Sequence::create(secAction, bgExplosionLeft2, between, bgExplosionRight2, NULL));

    bg1->runAction(Sequence::create(thirdAction, bgExplosionLeft1, between, bgExplosionRight1, NULL));
    bg2->runAction(Sequence::create(thirdAction, bgExplosionLeft2, between, bgExplosionRight2, NULL));

    bg1->runAction(Sequence::create(fAction, bgExplosionLeft1, between, bgExplosionRight1, NULL));
    bg2->runAction(Sequence::create(fAction, bgExplosionLeft2, between, bgExplosionRight2, NULL));

    scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::killAllMobs), 1.3);

}

void GameScene::multiplie(int index)
{
    sound->play2d("kill_mob_sound2.mp3", false, 0.5f);
    vec[index].mobs_count -= 1;
    //multiplie
    score = score * 1.1;
    userScore->setIntegerForKey("myScore", score);
    vec.at(index).deleteSprite();
    int vecsize = vec.size();
    if (index != (vecsize - 1))
    {
        std::swap(vec[index], vec[vecsize - 1]);
    }

    if (vec.size() > 0)
    {
        vec[index].setTag(index);
    }
    vec.pop_back();
    scoreLabel->setString(std::to_string(score));
    mobsAlive--;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto atag = contact.getShapeA()->getBody()->getTag();
    auto btag = contact.getShapeB()->getBody()->getTag();
 
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    

    if ((COLOB_COLLISION_BITMASK == a->getCollisionBitmask() && MOB_COLLISION_BITMASK == b->getCollisionBitmask()) 
        || (COLOB_COLLISION_BITMASK == b->getCollisionBitmask() && MOB_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        if (MOB_COLLISION_BITMASK == b->getCollisionBitmask())
        {
            killMob(btag);
            return true;
        }
        else
        {
            killMob(atag);
            return true;
        }
    } 

    if ((SPIKES_COLLISION_BITMASK == a->getCollisionBitmask() && COLOB_COLLISION_BITMASK == b->getCollisionBitmask())
        || (SPIKES_COLLISION_BITMASK == b->getCollisionBitmask() && COLOB_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
         sound->play2d("spikes_hit.mp3");
         GameScene::setScore(GameScene::getScore() * 0.75);
         GameScene::updateScoreLabel();
         userScore->setIntegerForKey("myScore", score);
         randomIvent->deleteRI();
         return true;
    }

    if ((SPIKES_COLLISION_BITMASK == a->getCollisionBitmask() && MOB_COLLISION_BITMASK == b->getCollisionBitmask())
       || (SPIKES_COLLISION_BITMASK == b->getCollisionBitmask() && MOB_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
         if (MOB_COLLISION_BITMASK == b->getCollisionBitmask())
         {
             removeMob(btag);
             return true;
         }
         else
         {
             removeMob(atag);
             return true;
         }
    }

    if ((SPIKES_COLLISION_BITMASK == a->getCollisionBitmask() && BOMB_COLLISION_BITMASK == b->getCollisionBitmask())
        || (SPIKES_COLLISION_BITMASK == b->getCollisionBitmask() && BOMB_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        sound->play2d("spikes_hit_bomb.mp3", false, 0.35f);
        randomIvent->deleteRI();
        randomIvent = nullptr;
    }

    if ((SPIKES_COLLISION_BITMASK == a->getCollisionBitmask() && EDGE_COLLISION_BITMASK == b->getCollisionBitmask())
        || (SPIKES_COLLISION_BITMASK == b->getCollisionBitmask() && EDGE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        
        randomIvent->deleteRI();
        randomIvent = nullptr;
    }

    if ((COLOB_COLLISION_BITMASK == a->getCollisionBitmask() && BOMB_COLLISION_BITMASK == b->getCollisionBitmask())
        || (COLOB_COLLISION_BITMASK == b->getCollisionBitmask() && BOMB_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        if (BOMB_COLLISION_BITMASK == b->getCollisionBitmask())
        {
            explosion(btag);
            return true;
        }
        else
        {
            explosion(atag);
            return true;
        }
    }

    if ((COLOB_COLLISION_BITMASK == a->getCollisionBitmask() && MULTIPLIER_COLLISION_BITMASK == b->getCollisionBitmask())
        || (COLOB_COLLISION_BITMASK == b->getCollisionBitmask() && MULTIPLIER_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        if (MULTIPLIER_COLLISION_BITMASK == b->getCollisionBitmask())
        {
            multiplie(btag);
            return true;
        }
        else
        {
            multiplie(atag);
            return true;
        }
    }

    return true;
}

void GameScene::replaceBg(const char* newSpriteName)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto  origin = Director::getInstance()->getVisibleOrigin();
    bg1->setTexture(newSpriteName);
    bg2->setTexture(newSpriteName);

    bg1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    bg1->setScale(visibleSize.width / bg1->getContentSize().width, visibleSize.height / bg1->getContentSize().height);

    bg2->setScale(visibleSize.width / bg2->getContentSize().width, visibleSize.height / bg2->getContentSize().height);
    bg2->setPosition(Point(roundf(visibleSize.width * 1.5 + origin.x), visibleSize.height / 2 + origin.y));
}

void GameScene::changeScoreColor(Color3B color)
{
    scoreLabel->setColor(color);
    
}

void GameScene::killAllMobs(float dt)
{
    for (auto& mob : vec)
    {
        sound->play2d("kill_mob_sound2.mp3", false, 0.3f);
        mob.mobs_count -= 1;
        mob.deleteSprite();
        score += mob.cost;
        userScore->setIntegerForKey("myScore", score);
        vec.pop_back();
        scoreLabel->setString(std::to_string(score));
        mobsAlive--;
    }
}

unsigned int GameScene::score = 0;
int GameScene::mobsCount = 15;
Label* GameScene::scoreLabel;
bool GameScene::isMusicOn = true;
MenuItemImage* GameScene::musicOnButton;
UserDefault* GameScene::userScore;
Sprite* GameScene::bg1;
Sprite* GameScene::bg2;