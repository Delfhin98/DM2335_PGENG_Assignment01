#include "Scene_Testing.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene_MainMenu.h"

USING_NS_CC;

Scene* TestingScene::createScene()
{
	return TestingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TestingScene::init()
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
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(TestingScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);
	
	// Touch
	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->setSwallowTouches(true);
	
	TouchListener->onTouchBegan = CC_CALLBACK_2(TestingScene::onTouchBegan, this);
	TouchListener->onTouchMoved = CC_CALLBACK_2(TestingScene::onTouchMoved, this);
	TouchListener->onTouchEnded = CC_CALLBACK_2(TestingScene::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);

	//// Scrolling Spice Shelf
	// Shelf
	auto Kitchen_SpiceRack = Sprite::create("Freemode/Freemode_SpiceShelf.png");
	Kitchen_SpiceRack->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height * 1.f));
	this->addChild(Kitchen_SpiceRack);

	Vec2 SpiceRackPos = Kitchen_SpiceRack->getPosition();

	// Scrolling
	ui::ScrollView *Spices_ScrollingShelf = ui::ScrollView::create();
	Spices_ScrollingShelf->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	Spices_ScrollingShelf->setContentSize(Size(Kitchen_SpiceRack->getContentSize().width * 0.9f, Kitchen_SpiceRack->getContentSize().height));
	Spices_ScrollingShelf->setInnerContainerSize(Size((Spices_ScrollingShelf->getContentSize().width * objectContainer.size()), (Spices_ScrollingShelf->getContentSize().height * objectContainer.size())));
	Spices_ScrollingShelf->setBounceEnabled(true);
	Spices_ScrollingShelf->setSwallowTouches(true);
	Spices_ScrollingShelf->setAnchorPoint(Vec2(0.5, 0.5));
	Spices_ScrollingShelf->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height * 1.02f));

	// Spices
	auto Spices_Salt = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(make_pair(make_pair("SPICES", "SALT"), Spices_Salt));
	auto Spices_Pepper = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(make_pair(make_pair("SPICES", "PEPPER"), Spices_Pepper));

	for (auto it = objectContainer.begin(); it != objectContainer.end();)
	{
		for (int i = 1; i < objectContainer.size() + 1; i++)
		{
			it->second->setPosition(Vec2(i * 100, Spices_ScrollingShelf->getContentSize().height * 0.5f));
			Spices_ScrollingShelf->addChild(it->second);

			_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener->clone(), it->second);
			it++;
		}
	}

	this->addChild(Spices_ScrollingShelf);

	// Spices Pop Up Menu
	spicesPopUpMenu = Sprite::create("methodpanel.png");
	spicesPopUpMenu->setPosition(playingSize * 0.5f);
	spicesPopUpMenu->setScale(0.f);
	isSpicesPopUpMenu = false;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener->clone(), spicesPopUpMenu);
	this->addChild(spicesPopUpMenu);

	// Testing out reading from Spices text file - Will be moved into a class


	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void TestingScene::update(float dt)
{

}

// Key Pressed
void TestingScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Testing Purposes
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		menuChangeScene(1.5f, MainMenu::createScene());
	}

	// Closing the Application
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		menuCloseCallback(this);
	}
}

bool TestingScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Vec2 pInNodeSpace = Vec2(0, 0);
	Vec2 p = touch->getLocation();
	Rect rect = this->getBoundingBox();

	if (!isSpicesPopUpMenu)
	{
		for (auto it = objectContainer.begin(); it != objectContainer.end(); it++)
		{
			// if 'it' is SPICES
			if (it->first.first == "SPICES")
			{
				if (!it->second->getParent())
				{
					return false;
				}

				// Change Cursor Position to 'it' Parent Node Space Position
				pInNodeSpace = it->second->getParent()->convertToNodeSpace(p);
				rect = it->second->getBoundingBox();

				// If the Cursor is touching something that's SPICES
				if (rect.containsPoint(pInNodeSpace))
				{
					CCLOG("TOUCHING SPICES OBJECT");

					// Check what SPICE is Cursor Touching
					if (it->first.second == "SALT")
					{
						CCLOG("TOUCHED SALT");
						openPopUpMenu(it->first.second);
						return true;
					}

					if (it->first.second == "PEPPER")
					{
						CCLOG("TOUCHED PEPPER");
						openPopUpMenu(it->first.second);
						return true;
					}
				}
			}
		}
	}

	if (isSpicesPopUpMenu)
	{
		Rect SpiceRect = spicesPopUpMenu->getBoundingBox();
		if (SpiceRect.containsPoint(p))
		{
			CCLOG("TOUCHED POP UP");
			return true;
		}

		if (!SpiceRect.containsPoint(p))
		{
			CCLOG("NOT TOUCHING POP UP");
			closePopUpMenu();
			return true;
		}
	}

	CCLOG("NO TOUCHED SPICES");

	return false;
}

bool TestingScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Vec2 p = touch->getLocation();
	Rect rect = this->getBoundingBox();

	//for (auto it = objectContainer.begin(); it != objectContainer.end(); it++)
	//{
	//	if (it->first.second == "salt")
	//	{
	//		rect = it->second->getBoundingBox();

	//		if (rect.containsPoint(p))
	//		{
	//			CCLOG("MOVING SALT");

	//			it->second->setPosition(Vec2(p));

	//			return true;
	//		}
	//	}

	//	if (it->first == "pepper")
	//	{
	//		rect = it->second->getBoundingBox();

	//		if (rect.containsPoint(p))
	//		{
	//			CCLOG("MOVING PEPPER");

	//			it->second->setPosition(Vec2(p));

	//			return true;
	//		}
	//	}
	//}

	//CCLOG("NO MOVING SPICES");

	return false;
}

void TestingScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	//CCLOG("onTouchEnded x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
}

void TestingScene::openPopUpMenu(const char * objectID)
{
	isSpicesPopUpMenu = true;
	spicesPopUpMenu->setScale(4.f);

	if (objectID == "SALT")
	{
	}

	if (objectID == "PEPPER")
	{

	}
}

void TestingScene::closePopUpMenu()
{
	isSpicesPopUpMenu = false;
	spicesPopUpMenu->setScale(0.f);
}

void TestingScene::menuCloseCallback(Ref* pSender)
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

void TestingScene::menuChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionJumpZoom::create(time, scene));
}