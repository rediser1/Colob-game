
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

	int cost;
	static int red_cost;
	static int blue_cost;
	static int yellow_cost;
	static int purple_cost;
	static int green_cost;

	static void setRedCost(int cost);
	static void setBlueCost(int cost);
	static void setYellowCost(int cost);
    static void setGreenCost(int cost);
	static void setPurpleCost(int cost);
private:
	Sprite* mobSprite;
	Vec2 origin;
	Size visibleSize;
	PhysicsBody* mobBody;
};


#endif // __MOB_H__

