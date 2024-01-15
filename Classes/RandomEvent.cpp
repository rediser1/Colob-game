#include "RandomEvent.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

RandomEvent::RandomEvent(Layer* layer)
{
	 visibleSize = Director::getInstance()->getVisibleSize();
	 origin = Director::getInstance()->getVisibleOrigin();
	 gameLayer = layer;
	 int randomIvent = cocos2d::RandomHelper::random_int(1, 1);
	 randomDelay = cocos2d::RandomHelper::random_int(5, 10);
	switch (randomIvent)
	{
		//small spikes
	case 1:
		randomIventSprite = Sprite::create("spikes.png");
	}

	randomIventBody = PhysicsBody::createBox(randomIventSprite->getContentSize());
	randomIventBody->setCollisionBitmask(SPIKES_COLLISION_BITMASK);
	randomIventBody->setContactTestBitmask(true);
	randomIventBody->setRotationEnable(false);
	randomIventSprite->setPhysicsBody(randomIventBody);
}


void RandomEvent::spawnRandomIvent()
{
	int randomX = cocos2d::RandomHelper::random_int(static_cast<int>(visibleSize.width * 0.2), static_cast<int>(visibleSize.width * 0.8));
	randomIventSprite->setPosition(randomX, visibleSize.height * 0.96 + origin.x);
	gameLayer->addChild(randomIventSprite, 2);
}


void RandomEvent::deleteRI()
{
	randomIventSprite->removeFromParent();
}