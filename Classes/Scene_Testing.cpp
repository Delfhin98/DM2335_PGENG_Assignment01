#include "Scene_Testing.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

Scene* SceneTesting::createScene()
{
	return SceneTesting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SceneTesting::init()
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

	// KeyPressed
	auto Keyboardlistener = EventListenerKeyboard::create();
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(SceneTesting::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

	// Touch
	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->setSwallowTouches(true);

	TouchListener->onTouchBegan = CC_CALLBACK_2(SceneTesting::onTestTouchBegan, this);
	TouchListener->onTouchMoved = CC_CALLBACK_2(SceneTesting::onTestTouchMoved, this);
	TouchListener->onTouchEnded = CC_CALLBACK_2(SceneTesting::onTestTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);

	// Common Pop Up Menu
	popUp = Sprite::create("Freemode/PopUp_CommonMenu.png");
	popUp->setPosition(playingSize * 0.5f);
	popUp->setScale(0.f);
	isPopUpOpen = false;

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener->clone(), popUp);
	objectContainer.push_back(std::make_pair(std::make_pair("POPUP", "POPUP_MENU"), popUp));
	this->addChild(popUp);

	// Recipe Drop Down Button
	Sprite* DropDown_RecipeButton = Sprite::create("Freemode/DropDown_RecipeButton.png");
	DropDown_RecipeButton->setPosition(Vec2(playingSize.width * 0.2f, playingSize.height * 0.8f));
	objectContainer.push_back(std::make_pair(std::make_pair("BUTTON", "BUTTON_RECIPE"), DropDown_RecipeButton));
	this->addChild(DropDown_RecipeButton);

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void SceneTesting::update(float dt)
{

}

// Key Pressed
void SceneTesting::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Closing the Application
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		menuCloseCallback(this);
	}
}

// Touch Began
bool SceneTesting::onTestTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Vec2 pInNodeSpace = Vec2(0, 0);
	Vec2 p = touch->getLocation();
	Rect rect = this->getBoundingBox();

	for (auto it = objectContainer.begin(); it != objectContainer.end(); it++)
	{
		// If 'it' is BUTTON
		if (it->first.first == "BUTTON")
		{
			// If POP UP is CLOSED
			if (!isPopUpOpen)
			{
				rect = it->second->getBoundingBox();

				// If TOUCH is INSIDE 'BUTTON' SPRITE BOUNDING BOX
				if (rect.containsPoint(p))
				{
					CCLOG("TOUCHING BUTTON TYPE OBJECT");

					// Check what BUTTON am I touching
					if (it->first.second == "BUTTON_RECIPE")
					{
						CCLOG("TOUCHING RECIPE BUTTON");
						openPopUpMenu(it->first.second);

						return true;
					}
				}
			}
		}
	}


	// If POP UP MENU IS OPEN
	if (isPopUpOpen)
	{
		Rect popUpRect = popUp->getBoundingBox();
		if (popUpRect.containsPoint(p))
		{
			CCLOG("TOUCHED POP UP");
			return true;
		}

		if (!popUpRect.containsPoint(p))
		{
			CCLOG("NOT TOUCHING POP UP");
			closePopUpMenu();
			return true;
		}
	}

	return false;
}

// Touch Moved
bool SceneTesting::onTestTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return false;
}

// Touch Ended
void SceneTesting::onTestTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
}

void SceneTesting::menuCloseCallback(Ref* pSender)
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

void SceneTesting::menuChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionJumpZoom::create(time, scene));
}

void SceneTesting::openPopUpMenu(const char * objectID)
{
	isPopUpOpen = true;
	popUp->setScale(1.f);

	// Touched Recipe Button
	if (objectID == "BUTTON_RECIPE")
	{

	}
}

void SceneTesting::closePopUpMenu()
{
	isPopUpOpen = false;
	popUp->setScale(0.f);
}