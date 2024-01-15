
#ifndef __MOB_H__
#define __MOB_H__

#include "cocos2d.h"



USING_NS_CC;
class Mob
{
public:
	Mob();
    void spawnMob(Layer* layer);
	void deleteSprite();
	Mob* operator->();
	void setTag(int number);
	int tag;
    static int mobs_count;

private:
	Sprite* mobSprite;
	Vec2 origin;
	Size visibleSize;
	PhysicsBody* mobBody;
};


#endif // __MOB_H__

