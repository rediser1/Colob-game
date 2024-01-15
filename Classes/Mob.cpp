#include "Mob.h"
#include "Definitions.h"
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

	int super_random = cocos2d::RandomHelper::random_int(1, 75);
	if (super_random == 1)
	{
		switch (super_level)
		{
		case 1:
			mobSprite = Sprite::create("colob_super.png");
			break;
		case 2:
			mobSprite = Sprite::create("colob_super_100.png");
			break;
		case 3:
			mobSprite = Sprite::create("colob_super_250.png");
			break;
		case 4:
			mobSprite = Sprite::create("colob_super_500.png");
			break;
		case 5:
			mobSprite = Sprite::create("colob_super_1000.png");
			break;
		}
		cost = super_cost;
	}
	else if (super_random == 2)
	{
		mobSprite = Sprite::create("bomb.png");
		cost = 0;
	}
	else if (super_random == 3)
	{
		mobSprite = Sprite::create("mob_0,1.png");
		cost = 0;
	}
	else {
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
	}
	
	bool normalSpawn = false;
	int random_y;
	int random_x;
	while (normalSpawn == false)
	{
		random_y = cocos2d::RandomHelper::random_int(static_cast<int>(visibleSize.height * 0.001), static_cast<int>(visibleSize.height));
		random_x = cocos2d::RandomHelper::random_int(static_cast<int>(visibleSize.width * 0.001), static_cast<int>(visibleSize.width)); //static_cast<int>(visibleSize.width * 0.1 + origin.x)
		if ((abs(random_y - (visibleSize.height / 4 + origin.y)) > 100) & (abs(random_x - (origin.x + visibleSize.width * 0.9)) > 100))
		{
			normalSpawn = true;
		}

		if ((abs(random_y - (origin.y + visibleSize.height * 0.95)) > 25) & (abs(random_x - (origin.x + visibleSize.width * 0.95)) > 25))
		{
			normalSpawn = true;
		}
	}
	mobSprite->setPosition(random_x + origin.x, random_y + origin.y);

    mobBody = PhysicsBody::createCircle(mobSprite->getContentSize().width / 2);
	mobBody->setContactTestBitmask(true);
	if (mobSprite->getResourceName() == "bomb.png")
		mobBody->setCollisionBitmask(BOMB_COLLISION_BITMASK);
	else if(mobSprite->getResourceName() == "mob_0,1.png")
		mobBody->setCollisionBitmask(MULTIPLIER_COLLISION_BITMASK);
	else
		mobBody->setCollisionBitmask(MOB_COLLISION_BITMASK);
	mobBody->setGravityEnable(false);
	mobBody->setDynamic(false);
	tag = mobs_count;
	mobs_count += 1;
	mobBody->setTag(tag);

	mobSprite->setPhysicsBody(mobBody);

	layer->addChild(mobSprite, 2);
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

void Mob::setSuperCost(int cost)
{
	super_cost = cost;
}

void Mob::setSuperLevel(int level)
{
	super_level = level;
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
int Mob::super_cost = 50;
int Mob::super_level = 1;