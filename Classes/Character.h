#pragma once

#include "cocos2d.h"

using namespace cocos2d;

enum EAction 
{
	eLeft = -1,
	eStop,
	eRight
};

class GameChar
{
private:
	cocos2d::Sprite* mainSprite;
	EAction eDir;
	float fSpeed;
	Vector<SpriteFrame*> frontFrames;
	Vector<SpriteFrame*> rightFrames;
	Vector<SpriteFrame*> leftFrames;
	Vector<SpriteFrame*> backFrames;

public:
	void init(const char*, const char*, float, float);
	void MoveChar(EAction);
	void MoveCharByCoord(float, float);
	void Stop();
	void Update(float);
	Sprite* getSprite(void) { return mainSprite; };
};