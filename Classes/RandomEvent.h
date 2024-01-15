#ifndef __RANDOMEVENT_H__
#define __RANDOMEVENT_H__

#include "cocos2d.h"

USING_NS_CC;
class RandomEvent
{
public:

	RandomEvent(Layer* layer);
	void spawnRandomIvent();
	void deleteRI();
private:

	Sprite* randomIventSprite;
	PhysicsBody* randomIventBody;
	Vec2 origin;
	Size visibleSize;
	int randomDelay;
	Layer* gameLayer;
};

#endif // __RANDOMEVENT_H__
