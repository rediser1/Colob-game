#include "Colob.h"
#include "Definitions.h"

USING_NS_CC;

Colob::Colob(cocos2d::Layer *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	colobSprite = Sprite::create("colob_new.png");
	colobSprite->setScale(0.3);
	colobSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto colobBody = PhysicsBody::createCircle(colobSprite->getContentSize().width / 2);
	colobBody->setCollisionBitmask(COLOB_COLLISION_BITMASK);
	colobBody->setContactTestBitmask(true);
	colobBody->setGravityEnable(false);
	colobBody->setMass(99999999);
	colobBody->setRotationEnable(false);

	colobSprite->setPhysicsBody(colobBody);

	scene->addChild(colobSprite, 10);
}

void Colob::setSpeed(int speed)
{
	m_speed = speed;
}

void Colob::moveleft(float dt)
{
	left_moving = MoveBy::create(dt, Vec2(-m_speed, 0));
	forever_left_moving = cocos2d::RepeatForever::create(left_moving);
	colobSprite->runAction(forever_left_moving);
}

void Colob::moveright(float dt)
{
	 right_moving = MoveBy::create(dt, Vec2(m_speed, 0));
	 forever_right_moving = cocos2d::RepeatForever::create(right_moving);
	 colobSprite->runAction(forever_right_moving);
}

void Colob::moveup(float dt)
{
	 up_moving = MoveBy::create(dt, Vec2(0, m_speed));
	 forever_up_moving = cocos2d::RepeatForever::create(up_moving);
	colobSprite->runAction(forever_up_moving);
}

void Colob::movedown(float dt)
{
	 down_moving = MoveBy::create(dt, Vec2(0, -m_speed));
	 forever_down_moving = cocos2d::RepeatForever::create(down_moving);
	colobSprite->runAction(forever_down_moving);
}

 
 

void Colob::stopmovingleft()
{
	colobSprite->stopAction(left_moving);
	colobSprite->stopAction(forever_left_moving);
}

void Colob::stopmovingright()
{
	colobSprite->stopAction(right_moving);
	colobSprite->stopAction(forever_right_moving);
}

void Colob::stopmovingup()
{
	colobSprite->stopAction(up_moving); 
	colobSprite->stopAction(forever_up_moving);
}

void Colob::stopmovingdown()
{
	colobSprite->stopAction(down_moving);
	colobSprite->stopAction(forever_down_moving);
}

void Colob::changeSprite(const char* newSpriteName)
{
	colobSprite->setTexture(newSpriteName);
}

int Colob::m_speed = 150;
cocos2d::Sprite* Colob::colobSprite;