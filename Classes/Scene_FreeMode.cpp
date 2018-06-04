#include "Scene_FreeMode.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene_MainMenu.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
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
	//auto titleLabel = Label::createWithTTF("Game Scene", "fonts/Marker Felt.ttf", visibleSize.width * 0.1f);
	//if (titleLabel == nullptr)
	//{
	//	problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
	//	// Position at the Center of the screen
	//	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//		origin.y + visibleSize.height - titleLabel->getContentSize().height));

	//	// Setting Title Color to be Orange + Shadow
	//	titleLabel->setTextColor(Color4B::ORANGE);
	//	titleLabel->enableOutline(Color4B::WHITE, 2);

	//	// add the label as a child to this layer
	//	this->addChild(titleLabel, 1);
	//}

	// Freemode Background + Kitchen
	// Background
	auto BG_Image = Sprite::create("FreeMode/Freemode_Background.png");
	BG_Image->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BG_Image, -1);
	// Scaling Factor to fill the screen size.
	float rX = visibleSize.width / BG_Image->getContentSize().width;
	float rY = visibleSize.height / BG_Image->getContentSize().height;
	// Set Scaling Factor to BG_Image.
	BG_Image->setScaleX(rX);
	BG_Image->setScaleY(rY);

	// Kitchen Counter
	auto Kitchen_Counter = Sprite::create("Freemode/Freemode_KitchenCounter.png");
	Kitchen_Counter->setPosition((visibleSize.width / 2 + origin.x), (visibleSize.height / 2 + origin.y) * 0.4f);
	BG_Image->addChild(Kitchen_Counter);
	// Set Scaling to Kitchen_Counter
	Kitchen_Counter->setScaleX(BG_Image->getScaleX());

	// Kitchen Spice Rack
	auto Kitchen_SpiceRack = Sprite::create("Freemode/Freemode_SpiceShelf.png");
	Kitchen_SpiceRack->setPosition((visibleSize.width / 2 + origin.x), (visibleSize.height / 2 + origin.y) * 2.5f);
	BG_Image->addChild(Kitchen_SpiceRack);
	// Set Scaling to Spice Rack
	Kitchen_SpiceRack->setScaleY(BG_Image->getScaleY() * 2.4f);

	// Kitchen Stove
	auto Kitchen_Stove = Sprite::create("Freemode/Freemode_Stove.png");
	Kitchen_Stove->setPosition((visibleSize.width / 2 + origin.x) * 0.6f, visibleSize.height / 2 + origin.y);
	Kitchen_Counter->addChild(Kitchen_Stove);

	// Kitchen Oven
	auto Kitchen_Oven = Sprite::create("Freemode/Freemode_Oven.png");
	Kitchen_Oven->setPosition((visibleSize.width / 2 + origin.x) * 0.605f, (visibleSize.height / 2 + origin.y) * 0.45f);
	Kitchen_Counter->addChild(Kitchen_Oven);

	// Chopping Board
	auto Kitchen_ChoppingBoard = Sprite::create("Freemode/Freemode_ChoppingBoard.png");
	Kitchen_ChoppingBoard->setPosition((visibleSize.width / 2 + origin.x) * 1.45f, (visibleSize.height / 2 + origin.y) * 1.2f);
	Kitchen_Counter->addChild(Kitchen_ChoppingBoard);

	//// Cooking Animation
	//cookingAnim = new CookingAnimation();
	//cookingAnim->init();
	//cookingAnim->playAnimation(this, "WaterAboutToBoil", 1.0f / 8, Vec2(Kitchen_Stove->getPositionX(), Kitchen_Stove->getPositionY() * 0.5f), 1.f);

	// Spices
	auto Spices_Salt = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(std::make_pair("salt", Spices_Salt));
	auto Spices_Pepper = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(std::make_pair("pepper", Spices_Pepper));

	// Scrolling Spice Shelf
	ui::ScrollView *Scroll_SpiceShelf = ui::ScrollView::create();
	Scroll_SpiceShelf->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	Scroll_SpiceShelf->setContentSize(Size(500, 200));
	Scroll_SpiceShelf->setInnerContainerSize(Size(1000, 200));
	Scroll_SpiceShelf->setBounceEnabled(true);
	Scroll_SpiceShelf->setAnchorPoint(Vec2(0.5, 0.5));
	Scroll_SpiceShelf->setPosition(Vec2(Kitchen_SpiceRack->getPositionX(), Kitchen_SpiceRack->getPositionY() * 0.8f));

	for (auto it = objectContainer.begin(); it != objectContainer.end();)
	{
		for (int i = 0; i < objectContainer.size(); i++)
		{
			it->second->setPosition(Vec2(i * 100, Scroll_SpiceShelf->getContentSize().height * 0.3f));
			Scroll_SpiceShelf->addChild(it->second);
			
			it++;
		}
	}

	this->addChild(Scroll_SpiceShelf);
	
	auto buttonBack = ui::Button::create("backbutton.png", "backbuttonselected.png");
	buttonBack->setPosition(Vec2((visibleSize.width / 2 + origin.x) * 0.15f, (visibleSize.height / 2 + origin.y) * 1.85f));
	buttonBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			menuChangeScene(1.0f, MainMenu::createScene());
		}
	});
	this->addChild(buttonBack);

	// KeyPressed
	auto Keyboardlistener = EventListenerKeyboard::create();
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

	//// Touch
	//auto TouchListener = EventListenerTouchOneByOne::create();
	//TouchListener->onTouchBegan = CC_CALLBACK_2(GameScene::InteractWSpices, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{

}

// Key Pressed
void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
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

void GameScene::menuCloseCallback(Ref* pSender)
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

void GameScene::menuChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionJumpZoom::create(time, scene));
}

//bool GameScene::InteractWSpices(Touch * touch, Event * event)
//{
//	Vec2 p = touch->getLocation();
//	Rect rect = this->getBoundingBox();
//
//	for (auto it = objectContainer.begin(); it != objectContainer.end(); it++)
//	{
//		if (it->first == "pepper")
//		{
//			rect = it->second->getBoundingBox();
//			if (rect.containsPoint(p))
//			{
//				menuChangeScene(1.5f, MainMenu::createScene());				
//				return true;
//			}
//		}
//	}
//
//	return false;
//}