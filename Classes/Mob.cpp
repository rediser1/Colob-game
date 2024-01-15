#include "Mob.h";
#include "Definitions.h";
#include <iostream>
#include <vector>
#include <cmath>

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
		 cost = blue_cost;
		break;
	case 2:
		 mobSprite = Sprite::create("colob_green.png");
		 cost = green_cost;
		break;
	case 3:
		 mobSprite = Sprite::create("colob_red.png");
		 cost = red_cost;
		break;
	case 4:
		 mobSprite = Sprite::create("colob_purple.png");
		 cost = purple_cost;
		break;
	case 5:
		 mobSprite = Sprite::create("colob_yellow.png");
		 cost = yellow_cost;
		break;
	}
	
	bool normalSpawn = false;
	int random_y;
	int random_x;
	while (normalSpawn == false)
	{
		random_y = cocos2d::RandomHelper::random_int(0, static_cast<int>(visibleSize.height));
		random_x = cocos2d::RandomHelper::random_int(0, static_cast<int>(visibleSize.width));
		if ((abs(random_y - (visibleSize.height / 4 + origin.y)) > 100) || (abs(random_x - (origin.x + visibleSize.width * 0.9)) > 100))
		{
			normalSpawn = true;
		}
	}
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

 void Mob::setRedCost(int cost)
{
	red_cost = cost;
}

 void Mob::setBlueCost(int cost)
{
	 blue_cost = cost;
}
 void Mob::setYellowCost(int cost)
{
	 yellow_cost = cost;
}
 void Mob::setGreenCost(int cost)
{
	 green_cost = cost;
}
 void Mob::setPurpleCost(int cost)
{
	purple_cost = cost;
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
int Mob::red_cost = 1;
int Mob::blue_cost = 1;
int Mob::yellow_cost = 1;
int Mob::green_cost = 1;
int Mob::purple_cost = 1;