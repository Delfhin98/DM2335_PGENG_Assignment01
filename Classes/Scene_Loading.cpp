#include "Scene_Loading.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene_MainMenu.h"
#include "Scene_FreeMode.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
	// Super Init First
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	hasFinished = false;
	// Creating a size that is valid.
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// Create and initialize a label
	auto titleLabel = Label::createWithTTF("Loading Scene...", "fonts/Marker Felt.ttf", visibleSize.width * 0.1f);
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
	
	currResource = 0;
	// Add resources here
	Resources.push_back("testpic.png");
	Resources.push_back("testpic.png");
	Resources.push_back("testpic.png");
	Resources.push_back("testpic.png");
	Resources.push_back("testpic.png");
	numOfResource = 5;

	textLabel = Label::createWithTTF("0%", "fonts/Marker Felt.ttf", 24);
	textLabel->setPosition(Vec2((int)visibleSize.width >> 1, ((int)visibleSize.height >> 1) - 30));
	this->addChild(textLabel, 1);

	auto Keyboardlistener = EventListenerKeyboard::create();
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(LoadingScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

	auto director = Director::getInstance();
	TextureCache* textureCache = director->getTextureCache();
	textureCache->addImageAsync(Resources[0], CC_CALLBACK_1(LoadingScene::loadingTextureFinished, this));

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void LoadingScene::update(float dt)
{
	auto scene = GameScene::createScene();
	auto director = Director::getInstance();
	if (percentage == 100)
	{
		textLabel->setString("Press Spacebar");
	}
	if (hasFinished)
	{
		director->replaceScene(scene);
	}
}

void LoadingScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		hasFinished = true;
	}
}

void LoadingScene::menuCloseCallback(Ref* pSender)
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

void LoadingScene::menuChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionFade::create(time, scene));
}

void LoadingScene::loadingTextureFinished(Texture2D * texture)
{
	auto director = Director::getInstance();
	auto scene = GameScene::createScene();
	currResource++;

	percentage = currResource * 100 / numOfResource;
	textLabel->setString(CCString::createWithFormat("%d%%", percentage)->getCString());
	if (currResource < numOfResource)
	{
		TextureCache* textureCache = director->getTextureCache();
		textureCache->addImageAsync(Resources[currResource], CC_CALLBACK_1(LoadingScene::loadingTextureFinished, this));
	}
	else
	{
		return;
	}
}
