#ifndef _COOKING_ANIMATION_H
#define _COOKING_ANIMATION_H

#include "cocos2d.h"
using namespace cocos2d;


class CookingAnimation
{
private:
	const char* spriteSheetImageDirectory;
	const char* spriteSheetDataDirectory;

	SpriteBatchNode* spriteBatch;
	SpriteFrameCache* cache;
	std::vector<std::pair<const char*, Vector<SpriteFrame*>>> animationContainer;

public:
	//void init(const char* _spriteSheetImageDirectory, const char* _spriteSheetDataDirectory, std::string _spriteSheet1stPicName, const char* _animationID, int _animationVectorSize);
	
	// First Step - Setting Sprite Sheet Directories
	void setSpriteSheet(const char* _spriteSheetImageDirectory, const char* _spriteSheetDataDirectory);
	// Second Step - Loading Animation from Sprite Sheet
	void createAnimation(const char* _animationID, std::string _firstPictureName, int _animaFramesVectorSize);
	// Third Step - Saving the Animation into a Container
	void addAnimationIntoVector(const char* _animationID, int _animationContainerVectorSize, Vector<SpriteFrame*> _animFrames);


	// Check to see if that animation have been created or not.
	bool isAnimCreated(const char* _animationID);
	// Play Animation
	void playAnimation(Scene* _scene, const char* _animationID, float _animDelayTime, Vec2 _spritePosition);
	void playAnimation(Sprite* _sprite, const char* _animationID, float _animDelayTime, Vec2 _spritePosition);
};

#endif // !_COOKING_ANIMATION_H