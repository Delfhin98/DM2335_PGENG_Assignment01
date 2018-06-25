#include "Scene_MainMenu.h"
#include "SimpleAudioEngine.h"
#include "Scene_FreeMode.h"
#include "Scene_Loading.h"
#include "Scene_Recipes.h"
#include "SimpleAudioEngine.h"

using namespace ui;

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{	
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	// Super Init First
	if (!Scene::init())
	{
		return false;
	}

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	audio->playBackgroundMusic("Kalimba.mp3", true);
	// Creating a size that is valid.
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// Adding a label shows "Main Menu"
	// Create and initialize a label
	auto titleLabel = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", visibleSize.width * 0.1f);
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
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 pos_buttons = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 pos_offset = Vec2(0, -50);

	auto btn_FreeMode = Button::create("button.png", "buttonselected.png", "buttondisabled.png");
	btn_FreeMode->setTitleText("Free Mode");
	btn_FreeMode->setTitleFontName("fonts/Marker Felt.ttf");
	btn_FreeMode->setTitleFontSize(20.0f);
	btn_FreeMode->setPosition(pos_buttons);
	btn_FreeMode->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			MainMenuChangeScene(1.0f, LoadingScene::createScene());
		}
	});
	this->addChild(btn_FreeMode);
	pos_buttons += pos_offset;

	auto btn_RecipeDatabase = Button::create("button.png", "buttonselected.png", "buttondisabled.png");
	btn_RecipeDatabase->setTitleText("Recipes");
	btn_RecipeDatabase->setTitleFontName("fonts/Marker Felt.ttf");
	btn_RecipeDatabase->setTitleFontSize(20.0f);
	btn_RecipeDatabase->setPosition(pos_buttons);
	btn_RecipeDatabase->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			MainMenuChangeScene(2.0f, RecipeScene::createScene());
		}
	});
	this->addChild(btn_RecipeDatabase);
	pos_buttons += pos_offset;

	auto btn_Quit = Button::create("button.png", "buttonselected.png", "buttondisabled.png");
	btn_Quit->setTitleText("Quit Game");
	btn_Quit->setTitleFontName("fonts/Marker Felt.ttf");
	btn_Quit->setTitleFontSize(20.0f);
	btn_Quit->setPosition(pos_buttons);
	btn_Quit->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			menuCloseCallback(this);
		}
	});
	this->addChild(btn_Quit);

	// KeyPressed
	auto Keyboardlistener = EventListenerKeyboard::create();
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void MainMenu::update(float dt)
{

}

// Key Pressed
void MainMenu::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Testing Purposes
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		
	}

	// Closing the Application
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		
	}
}

void MainMenu::menuCloseCallback(Ref* pSender)
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

void MainMenu::MainMenuChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionFade::create(time, scene));
}
