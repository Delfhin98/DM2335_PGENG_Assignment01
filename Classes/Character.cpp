#include "Character.h"
#include "HelloWorldScene.h"

void GameChar::init(const char* imageName, const char* spriteName, float sX, float sY)
{
	mainSprite = Sprite::create(imageName);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(sX, sY);
	mainSprite->setName(spriteName);

	eDir = eStop;
	fSpeed = 0.5f;
	
	frontFrames.reserve(4);
	frontFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
	frontFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	frontFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	frontFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	

	rightFrames.reserve(4);
	rightFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 65, 81)));
	rightFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
	rightFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 65, 81)));
	rightFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));

	leftFrames.reserve(4);
	leftFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 65, 81)));
	leftFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
	leftFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 65, 81)));
	leftFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
	

	backFrames.reserve(4);
	backFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
	backFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	backFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
	backFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	

	Animation* frontAnim = Animation::createWithSpriteFrames(frontFrames, 0.05f);
	Animate* animateFront = Animate::create(frontAnim);
	
	this->getSprite()->runAction(RepeatForever::create(animateFront));
}

void GameChar::MoveChar(EAction DirX)
{
	eDir = DirX;
	this->Stop();
	if (eDir == eRight)
	{
		Animation* rightAnim = Animation::createWithSpriteFrames(rightFrames, 0.05f);
		Animate* animateRight = Animate::create(rightAnim);
		this->getSprite()->runAction(RepeatForever::create(animateRight));
	}
	else if (eDir == eLeft)
	{
		Animation* leftAnim = Animation::createWithSpriteFrames(leftFrames, 0.05f);
		Animate* animateLeft = Animate::create(leftAnim);
		this->getSprite()->runAction(RepeatForever::create(animateLeft));
	}
}

void GameChar::MoveCharByCoord(float fX, float fY)
{
	mainSprite->stopAllActions();
	float diffX = fX - mainSprite->getPosition().x;
	float diffY = fY - mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
	mainSprite->runAction(moveEvent);

	auto callbackStop = CallFunc::create([]() 
	{
		auto scene = Director::getInstance()->getRunningScene();
		HelloWorld* HWScene = dynamic_cast<HelloWorld*>(scene);
		if (HWScene != NULL)
			HWScene->getChar()->Stop();
	});

	auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
	mainSprite->runAction(seq);

	if (diffY > 0)
	{
		Animation* backAnim = Animation::createWithSpriteFrames(backFrames, 0.05f);
		Animate* animateBack = Animate::create(backAnim);
		this->getSprite()->runAction(RepeatForever::create(animateBack));
	}
	else
	{
		Animation* frontAnim = Animation::createWithSpriteFrames(frontFrames, 0.05f);
		Animate* animateFront = Animate::create(frontAnim);
		this->getSprite()->runAction(RepeatForever::create(animateFront));
	}
		
}

void GameChar::Stop()
{
	mainSprite->stopAllActions();
}

void GameChar::Update(float delta)
{
	if (eDir != eStop)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(1.0f, 0.0f) * eDir);
		mainSprite->runAction(moveEvent);
	}
}
