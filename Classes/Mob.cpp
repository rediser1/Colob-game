#include "Mob.h";
#include "Definitions.h";
#include <iostream>
#include <vector>

USING_NS_CC;


Mob::Mob()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Mob::spawnMob(Layer* layer)
{
	int random_number = cocos2d::RandomHelper::random_int(1, 5);

	switch (random_number)
	{
	case 1:
		 mobSprite = Sprite::create("colob_blue.png");
		break;
	case 2:
		 mobSprite = Sprite::create("colob_green.png");
		break;
	case 3:
		 mobSprite = Sprite::create("colob_red.png");
		break;
	case 4:
		 mobSprite = Sprite::create("colob_purple.png");
		break;
	case 5:
		 mobSprite = Sprite::create("colob_yellow.png");
		break;
	}

	int random_y = cocos2d::RandomHelper::random_int(100, 868);
	int random_x = cocos2d::RandomHelper::random_int(170, 1568);
	mobSprite->setPosition(random_x, random_y);

    mobBody = PhysicsBody::createCircle(mobSprite->getContentSize().width / 2);
	mobBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	mobBody->setContactTestBitmask(true);
	mobBody->setGravityEnable(false);

	tag = mobs_count;
	mobs_count += 1;
	mobBody->setTag(tag);

	mobSprite->setPhysicsBody(mobBody);

	layer->addChild(mobSprite);
}

void Mob::deleteSprite()
{
	mobSprite->removeFromParent();
}

Mob* Mob::operator->()
{
	return this;
}

void Mob::setTag(int number)
{
	mobBody->setTag(number);
}

int Mob::mobs_count = 0;