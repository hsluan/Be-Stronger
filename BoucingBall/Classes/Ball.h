#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"
#include "GameDefine.h"
USING_NS_CC;

class Ball : public CCSprite
{
private:
	CCPoint _posBegin;

	CC_SYNTHESIZE(bool, isCollision, IsCollision);
	CC_SYNTHESIZE(bool, isGravity, IsGravity);
	//CC_SYNTHESIZE(CCMotionStreak*, _streak, Trail);
public:
	Ball(CCPoint pos);
	~Ball();
	static Ball* createBall(CCPoint pos);
	void initBall();
	void updateBall(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
