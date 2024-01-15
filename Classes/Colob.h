
#ifndef __COLOB_H__
#define __COLOB_H__

#include "cocos2d.h"

USING_NS_CC;
class Colob
{
public:
	Colob(cocos2d::Layer * scene);

	void moveleft(float dt);
	void moveright(float dt);
	void moveup(float dt);
	void movedown(float dt);

	void stopmovingleft();
	void stopmovingright();
	void stopmovingup();
	void stopmovingdown();
	
	Sprite* getSprite();
	
	static void setSpeed(int speed);
	static void changeSprite(const char* newSpriteName);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	static cocos2d::Sprite* colobSprite;

	ActionInterval* left_moving;
	ActionInterval* right_moving;
	ActionInterval* down_moving;
	ActionInterval* up_moving;

	Action* forever_left_moving;
	Action* forever_right_moving;
	Action* forever_down_moving;
	Action* forever_up_moving;

	static int m_speed;
};

#endif // __COLOB_H__
