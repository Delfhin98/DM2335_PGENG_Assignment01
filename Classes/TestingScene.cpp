#include "testingScene.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Testing::createScene()
{
	return Testing::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TestingScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Testing::init()
{
	// Super Init First
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Creating a size that is valid.
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// Adding a label shows "Main Menu"
	// Create and initialize a label
	auto titleLabel = Label::createWithTTF("Testing Scene", "fonts/Marker Felt.ttf", visibleSize.width * 0.1f);
	if (titleLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// Position at the Center of the screen
		titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - titleLabel->getContentSize().height));

		// Setting Title Color to be Orange + Shadow
		titleLabel->setTextColor(Color4B::ORANGE);
		titleLabel->enableOutline(Color4B::WHITE, 2);

		// add the label as a child to this layer
		this->addChild(titleLabel, 1);
	}

	cookingAnim = new CookingAnimation();
	cookingAnim->setSpriteSheet("Animation/LowHeatSpriteSheet.png","Animation/LowHeatSpriteSheet.plist");
	cookingAnim->createAnimation("LowFlame", "LowHeatSprite0", 2);
	cookingAnim->playAnimation(this, "LowFlame", 1.0f / 3, Vec2(100, 200));

	//cookingAnim = new CookingAnimation();
	cookingAnim->setSpriteSheet("Animation/HighHeatSpriteSheet.png", "Animation/HighHeatSpriteSheet.plist");
	cookingAnim->createAnimation("HighFlame", "HighHeatSprite0", 2);
	cookingAnim->playAnimation(this, "HighFlame", 1.0f / 3, Vec2(400, 200));

	//cookingAnim->playAnimation(this, "HighFlame", 1.0f / 3, Vec2(400, 200));
	//cookingAnim->playAnimation(this, "HighFlame", 1.0f / 3, Vec2(500, 500));
	//cookingAnim->playAnimation(this, "HighFlame", 1.0f / 3, Vec2(300, 300));


	// KeyPressed
	auto Keyboardlistener = EventListenerKeyboard::create();
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(Testing::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void Testing::update(float dt)
{

}

// Key Pressed
void Testing::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Testing Purposes
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		menuChangeScene(1.5f, Testing::createScene());
	}

	// Closing the Application
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		menuCloseCallback(this);
	}
}

void Testing::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void Testing::menuChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionJumpZoom::create(time, scene));
}
