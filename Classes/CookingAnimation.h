#ifndef _COOKING_ANIMATION_H
#define _COOKING_ANIMATION_H

#include "cocos2d.h"
using namespace cocos2d;


class CookingAnimation
{
private:
	SpriteBatchNode* spriteBatch;
	SpriteFrameCache* cache;
	std::vector<std::pair<const char*, Vector<SpriteFrame*>>> animationContainer;

public:
	void init();
	
	// First Step - Setting Sprite Sheet Directories
	void setSpriteSheet(const char* _spriteSheetImageDirectory, const char* _spriteSheetDataDirectory);
	// Second Step - Loading Animation from Sprite Sheet
	void loadAnimation(const char* _animationID, std::string _firstPictureName, int _animaFramesVectorSize);
	// Third Step - Saving the Animation into a Container
	void addAnimationIntoVector(const char* _animationID, int _animationContainerVectorSize, Vector<SpriteFrame*> _animFrames);


	// Check to see if that animation have been created or not.
	bool isAnimCreated(const char* _animationID);
	// Play Animation
	void playAnimation(Scene* _scene, const char* _animationID, float _animDelayTime, Vec2 _spritePosition, float _spriteScale);
	void playAnimation(Sprite* _sprite, const char* _animationID, float _animDelayTime, Vec2 _spritePosition, float _spriteScale);
};

#endif // !_COOKING_ANIMATION_H