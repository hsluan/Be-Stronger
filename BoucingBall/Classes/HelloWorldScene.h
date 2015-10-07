#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "Ball.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
private:
	bool _isPlaying;
	bool _isGameOver;
	bool _isGravity;

	int _nScore;

	Ball* _pBall;
	
	CCMotionStreak* _streak;
	CCLabelTTF* _pLabelTTFScore;
	CCLabelBMFont* _pLabelBMFScore;

	CCNode* _pNodeContaintHorizital;

	std::vector< CCSprite* > _vtObstacle;

public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    
	void createObstacle();
	void setPause();
	void setResume();
	bool getPlaying();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
	virtual void registerWithTouchDispatcher();
	virtual void update(float dt);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
