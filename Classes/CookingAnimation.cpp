#include "CookingAnimation.h"


void CookingAnimation::init()
{
	// Stove Fire Animation
	// Low Heat
	setSpriteSheet("Animation/StoveFire_LowHeat.png", "Animation/StoveFire_LowHeat.plist");
	loadAnimation("StoveFire_Low", "StoveFire_LowHeat", 2);
	// Medium Heat
	setSpriteSheet("Animation/StoveFire_MediumHeat.png", "Animation/StoveFire_MediumHeat.plist");
	loadAnimation("StoveFire_Medium", "StoveFire_MediumHeat", 2);
	// High Heat
	setSpriteSheet("Animation/StoveFire_HighHeat.png", "Animation/StoveFire_HighHeat.plist");
	loadAnimation("StoveFire_High", "StoveFire_HighHeat", 2);

	// About to Boil Water Animation - W Pot
	setSpriteSheet("Animation/AboutToBoilWater.png", "Animation/AboutToBoilWater.plist");
	loadAnimation("WaterAboutToBoil", "AboutToBoil_OnPot", 8);

	// Boiling Water Animation - W Pot
	setSpriteSheet("Animation/BoilingWater.png", "Animation/BoilingWater.plist");
	loadAnimation("WaterBoiling", "Boiling_OnPot", 8);
}

void CookingAnimation::setSpriteSheet(const char * _spriteSheetImageDirectory, const char * _spriteSheetDataDirectory)
{
	// Sprite Sheet
	spriteBatch = SpriteBatchNode::create(_spriteSheetImageDirectory);
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(_spriteSheetDataDirectory);
}

void CookingAnimation::loadAnimation(const char* _animationID, std::string _firstPictureName, int _animaFramesVectorSize)
{
	// Loading Animation from Sprite Sheet
	Vector<SpriteFrame*> animFrames(_animaFramesVectorSize);
	char str[100] = { 0 };

	std::string _lastLink = "%d.png";
	_firstPictureName.append(_lastLink);

	for (int i = 1; i < _animaFramesVectorSize + 1; i++)
	{
		sprintf(str, _firstPictureName.c_str(), i);
		//SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(cache->getSpriteFrameByName(str)); // it's this part got problem
	}

	addAnimationIntoVector(_animationID, _animaFramesVectorSize, animFrames);
}

void CookingAnimation::addAnimationIntoVector(const char * _animationID, int _animationContainerVectorSize, Vector<SpriteFrame*> _animFrames)
{
	// If there are no same ID
	if (!isAnimCreated(_animationID))
	{
		animationContainer.push_back(std::make_pair(_animationID, _animFrames));
	}
	else
	{
		cocos2d::log("This word/name cannot be used as an ID as it exists already.");
	}
}

void CookingAnimation::playAnimation(Scene * _scene, const char * _animationID, float _animDelayTime, Vec2 _spritePosition)
{
	// Search for the Animation
	for (auto it = animationContainer.begin(); it != animationContainer.end(); it++)
	{
		if (it->first == _animationID)
		{
			// Sprite
			auto sprite = Sprite::createWithSpriteFrame(it->second.front());
			_scene->addChild(sprite);
			sprite->setPosition(_spritePosition);

			// Animation
			auto animation = Animation::createWithSpriteFrames(it->second, _animDelayTime);
			sprite->runAction(RepeatForever::create(Animate::create(animation)));
		}
		else
		{
			cocos2d::log("No such ID in the storage.");
		}
	}
}

void CookingAnimation::playAnimation(Sprite * _sprite, const char * _animationID, float _animDelayTime, Vec2 _spritePosition)
{
	// Search for the Animation
	for (auto it = animationContainer.begin(); it != animationContainer.end(); it++)
	{
		if (it->first == _animationID)
		{
			// Sprite
			auto sprite = Sprite::createWithSpriteFrame(it->second.front());
			_sprite->addChild(sprite);
			sprite->setPosition(_spritePosition);

			// Animation
			auto animation = Animation::createWithSpriteFrames(it->second, _animDelayTime);
			sprite->runAction(RepeatForever::create(Animate::create(animation)));
		}
		else
		{
			cocos2d::log("No such ID in the storage.");
		}
	}
}

bool CookingAnimation::isAnimCreated(const char * _animationID)
{
	// If animationContainer Vector contains something
	if (!animationContainer.empty())
	{
		for (auto it = animationContainer.begin(); it != animationContainer.end(); it++)
		{
			if (it->first == _animationID)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}