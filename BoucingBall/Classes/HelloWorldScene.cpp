#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
		

	this->setTouchEnabled(true);
	
	_isPlaying	= true;
	_isGameOver = false;
	_isGravity = false;

	_nScore		= 0;

	auto pBg = CCSprite::create(IMG_BACKGROUND);
	pBg->setPosition(POS_BACKGROUND);
	this->addChild(pBg, (int)ZOrder::One);


	_pNodeContaintHorizital = CCNode::create();
	this->addChild(_pNodeContaintHorizital, (int)ZOrder::Two);


	_pBall = Ball::createBall(POS_BALL);
	_pNodeContaintHorizital->addChild(_pBall, _pNodeContaintHorizital->getZOrder());

	//_streak = CCMotionStreak::create(0.4, 1, 15, ccc3(255, 255, 255), "images/streak.png");
	//_streak->setPosition(ccp(_pBall->getPositionX(),
	//							_pBall->getPositionY() - HEIGHT_SPRITE(_pBall)*0.5f) );
	//_streak->setBlendFunc(ADDITIVE);
	//_pBall->setTrail(pStreak);
	//addChild(_streak, (int)ZOrder::Two);


	_pLabelTTFScore = CCLabelTTF::create("Score: ", "arial.ttf", 50);
	_pLabelTTFScore->setPosition(ccp(_pLabelTTFScore->getContentSize().width*0.5f, HEIGHT_SCREEN - _pLabelTTFScore->getContentSize().height*0.5f));
	_pLabelTTFScore->setColor(COLOR_FONT_SCORE);
	this->addChild(_pLabelTTFScore, (int)ZOrder::Highest);
	
	/*_pLabelBMFScore = CCLabelTTF::create("Score: ", "arial.ttf", 30);
	_pLabelTTFScore->setPosition(ccp(_pLabelTTFScore->getContentSize().width*0.5f, HEIGHT_SCREEN - _pLabelTTFScore->getContentSize().height*0.5f));
	this->addChild(_pLabelTTFScore, (int)ZOrder::Highest);*/
	createObstacle();
	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
	if (!_isPlaying) return;

	_pBall->updateBall(dt);

	if (_pBall->getPositionY() > 600)
	{
		_pNodeContaintHorizital->setPositionY(_pNodeContaintHorizital->getPositionY() - 300);
	}
	//_streak->setPositionY(_pBall->getPositionY() - HEIGHT_SPRITE(_pBall)*0.5f*SCALE_FACTOR);
}

void HelloWorld::createObstacle()
{
	
	float fSpriteX = 0.0f;
	float fSpriteY = 0.0f;
	float fDistanceNeedMove = 0.0f;
	float fTimeRandom = 0.5f + CCRANDOM_0_1();

	for (int i = 0; i < 4; i++)
	{
		auto pObstacleTemp = CCSprite::create("images/horizital.png");
		if (i == 2)
		{
			fTimeRandom = CCRANDOM_0_1();
		}

		if ( i % 2 == 0 )
		{
			fSpriteX = WIDTH_SCREEN + WIDTH_SPRITE(pObstacleTemp) * 1 / 3 - rand() % 50; // obstacle right
		}
		else
		{			
			fSpriteX = -WIDTH_SPRITE(pObstacleTemp) * 1 / 3 + rand() % 50; // obstacle left
		}		
		fSpriteY = 600 * (i > 1 ? 2 : 1);		
		pObstacleTemp->setPosition(ccp(fSpriteX, fSpriteY));
		_pNodeContaintHorizital->addChild(pObstacleTemp, _pNodeContaintHorizital->getZOrder());
		_vtObstacle.push_back(pObstacleTemp);

		if (i % 2 != 0)
		{
			fDistanceNeedMove = HALF_WIDTH_SCREEN - (pObstacleTemp->getPositionX() + WIDTH_SPRITE(pObstacleTemp)*0.5f);
			auto pMoveRight = CCMoveBy::create(fTimeRandom, ccp(fDistanceNeedMove, 0));
			auto pSequence = CCSequence::create(pMoveRight, pMoveRight->reverse(), NULL);
			pObstacleTemp->runAction(CCRepeatForever::create(pSequence));
		}
		else
		{
			fDistanceNeedMove = (pObstacleTemp->getPositionX() - WIDTH_SPRITE(pObstacleTemp)*0.5f) - HALF_WIDTH_SCREEN;
			auto pMoveLeft = CCMoveBy::create(fTimeRandom, ccp(-fDistanceNeedMove, 0));
			auto pSequence = CCSequence::create(pMoveLeft, pMoveLeft->reverse(), NULL);
			pObstacleTemp->runAction(CCRepeatForever::create(pSequence));
		}

	}

	/*auto pObstacleLeft = CCSprite::create("images/horizital.png");
	float fSpriteLeftX = -WIDTH_SPRITE(pObstacleLeft) * 1/3 + rand() % 20;
	float fSpriteY = 600;
	pObstacleLeft->setPosition(ccp(fSpriteLeftX, fSpriteY));
	_pNodeContaintHorizital->addChild(pObstacleLeft);
	_vtObstacle.push_back(pObstacleLeft);

	auto pObstacleRight = CCSprite::create("images/horizital.png");
	float fSpriteRighX = WIDTH_SCREEN + WIDTH_SPRITE(pObstacleRight) * 1 / 3 - rand() % 20;
	pObstacleRight->setPosition(ccp(fSpriteRighX, fSpriteY));
	_pNodeContaintHorizital->addChild(pObstacleRight);
	_vtObstacle.push_back(pObstacleRight);

	float fTimeRandom = CCRANDOM_0_1();

	float fDistanceNeedMove = HALF_WIDTH_SCREEN - (pObstacleLeft->getPositionX() + WIDTH_SPRITE(pObstacleLeft)*0.5f);
	auto pMoveRight = CCMoveBy::create(fTimeRandom, ccp(fDistanceNeedMove, 0));
	auto pSequence = CCSequence::create(pMoveRight, pMoveRight->reverse(), NULL);
	pObstacleLeft->runAction(CCRepeatForever::create(pSequence));


	fDistanceNeedMove = (pObstacleRight->getPositionX() - WIDTH_SPRITE(pObstacleRight)*0.5f) - HALF_WIDTH_SCREEN;
	auto pMoveLeft = CCMoveBy::create(fTimeRandom, ccp(-fDistanceNeedMove, 0));
	pSequence = CCSequence::create(pMoveLeft, pMoveLeft->reverse(), NULL);
	pObstacleRight->runAction(CCRepeatForever::create(pSequence));*/
	
}

bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{	
	if ( _pBall->getActionByTag(TAG_JUMP_ACTION) )
	{
		_pBall->stopAllActions();
	}
	
	auto pJumpUp	= CCJumpBy::create(1.0f, ccp(0, 300), 300, 1);
	auto pEasyOut	= CCEaseOut::create(pJumpUp, 1.0f);
	auto pFallDown	= CCJumpBy::create(1.0f, ccp(0, - ( _pBall->getPositionY() + WIDTH_SPRITE(_pBall)*0.5f) ), -150, 1);
	auto pEasyIn	= CCEaseIn::create(pFallDown, 0.75f);
	auto pSequence	= CCSequence::create(pEasyOut, pEasyIn, NULL);
	pSequence->setTag(TAG_JUMP_ACTION);
	
	_pBall->runAction(pSequence);
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{

}

void HelloWorld::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
	ccTouchEnded(pTouch, pEvent);
}

void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{

}

void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);
}

void HelloWorld::setPause()
{
	_isPlaying = false;
}

void HelloWorld::setResume()
{
	_isPlaying = true;
}

bool HelloWorld::getPlaying()
{
	return _isPlaying;
}
