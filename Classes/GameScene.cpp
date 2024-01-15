
#include "GameScene.h";
#include "Colob.h";
#include "ui/CocosGUI.h";
#include "Mob.h";
#include "Definitions.h";

USING_NS_CC;

Scene* GameScene::createScene()
{
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
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //background
    auto bgsprite = Sprite::create("gamebg.png");
    bgsprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width, visibleSize.height / bgsprite->getContentSize().height);
    this->addChild(bgsprite);

    colob = new Colob(this);

    //later....

   // auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
   //edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    //edgeBody->setContactTestBitmask(true);
   

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

    left_button->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 4 + origin.y));
    this->addChild(left_button);

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

    right_button->setPosition(Point(visibleSize.width / 3 + origin.x, visibleSize.height / 4 + origin.y));
    this->addChild(right_button);

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

    up_button->setPosition(Point(visibleSize.width / 3.45 + origin.x, visibleSize.height / 3.1 + origin.y));
    this->addChild(up_button);

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

    down_button->setPosition(Point(visibleSize.width / 3.45 + origin.x, (up_button->getPositionY() -(up_button->getPositionY() - right_button->getPositionY()) * 2)));
    this->addChild(down_button);
    
    vec.reserve(40);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SpawnMob), 3);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

}

void GameScene::SpawnMob(float dt)
{
    Mob mob;
    mob.spawnMob(this);
    vec.push_back(mob);
} 

void GameScene::killMob(int index)
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

}

void GameScene::killingMobs(float dt)
{
    killMob(0);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
     auto atag = contact.getShapeA()->getBody()->getTag();
     auto btag = contact.getShapeB()->getBody()->getTag();
 
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    


    if ((COLOB_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) 
        || (COLOB_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        if (OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask())
          
            killMob(btag);
        else
            killMob(atag);
    }

    return true;
}
