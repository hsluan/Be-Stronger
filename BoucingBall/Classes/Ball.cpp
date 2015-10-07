#include "Ball.h"


Ball::Ball( CCPoint pos )
{
	_posBegin	= pos;
	isCollision = false;
	isGravity	= false;
	//_streak		= NULL;
}

Ball::~Ball()
{

}

Ball* Ball::createBall(CCPoint pos)
{
	auto pBall = new Ball(pos);
	if (pBall)
	{
		pBall->initBall();
		pBall->autorelease();
		return pBall;
	}
	CC_SAFE_DELETE(pBall);
	return nullptr;
}

void Ball::initBall()
{	

	this->initWithFile(IMG_BALL);
	this->setPosition(_posBegin);
}

void Ball::updateBall(float dt)
{
	//if (_streak)
	//{		

	//	_streak->setPositionY(this->getPositionY() /*- HEIGHT_SPRITE(this)*0.5f*SCALE_FACTOR*/);		
	//	CCLOG("x=%f y=%f | %f %f", this->getPositionX(), this->getPositionY(), _streak->getPositionX(), _streak->getPositionY());
	//}
}