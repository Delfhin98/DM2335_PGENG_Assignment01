#include "Scene_MainMenu.h"
#include "Scene_FreeMode.h"
#include "Scene_Loading.h"
#include "Scene_Recipes.h"

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
    // If Platform is Windows
    if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    {
        isWindows = true;
        isAndroid = false;
    }
    // If Platform is Android
    if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    {
        isAndroid = true;
        isWindows = false;
    }

	// Super Init First
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float screenWidth = visibleSize.width;
	float screenHeight = visibleSize.height;
	
	//// Background
	auto BG_Image = Sprite::create("MainMenu/Background.png");
	BG_Image->setPosition(Vec2(screenWidth * 0.5f, screenHeight * 0.5f));
	// Scale Image
	float BG_X = screenWidth / BG_Image->getContentSize().width;
	float BG_Y = screenHeight / BG_Image->getContentSize().height;
	// Set Scaling Factor to BG_Image.
	BG_Image->setScale(BG_X, BG_Y);
	this->addChild(BG_Image);

	//// Game Title
	auto titleLabel = Label::createWithTTF("CookFree!", "fonts/Marker Felt.ttf", screenWidth * 0.1f);
	if (titleLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// Position
		titleLabel->setPosition(Vec2(screenWidth * 0.7f, screenHeight * 0.85f));
		// Setting Title Color to be Orange + Shadow
		titleLabel->setTextColor(Color4B::ORANGE);
		titleLabel->enableOutline(Color4B::WHITE, 2);
		// add the label as a child to this layer
		this->addChild(titleLabel, 1);
	}

	//// Start Button
	ui::Button* startButton = ui::Button::create("MainMenu/button.png", "MainMenu/buttonselected.png");
    startButton->setPosition(Vec2(screenWidth * 0.7f, screenHeight * 0.55f));
	startButton->setTitleText("PLAY");
	startButton->setTitleFontName("fonts/Marker Felt.ttf");
	startButton->setTitleColor(Color3B::BLACK);
	startButton->setTitleFontSize(20.f);
	startButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	startButton->setName("PLAY_BUTTON");

	float Start_X = screenWidth / startButton->getContentSize().width;
	float Start_Y = screenHeight / startButton->getContentSize().height;
	startButton->setScale(Start_X * 0.2f, Start_Y * 0.1f);

	// Adding Listener
	startButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::onButtonPressed, this));
	this->addChild(startButton);

    // If it's windows, show Recipe
    if(isWindows && !isAndroid)
    {
        //// Recipe Button
        ui::Button* recipeButton = ui::Button::create("MainMenu/button.png", "MainMenu/buttonselected.png");
        recipeButton->setPosition(Vec2(screenWidth * 0.7f, screenHeight * 0.4f));
        recipeButton->setTitleText("RECIPES");
        recipeButton->setTitleFontName("fonts/Marker Felt.ttf");
        recipeButton->setTitleColor(Color3B::BLACK);
        recipeButton->setTitleFontSize(20.f);
        recipeButton->setAnchorPoint(Vec2(0.5f, 0.5f));
        recipeButton->setName("RECIPE_BUTTON");

        float Recipe_X = screenWidth / recipeButton->getContentSize().width;
        float Recipe_Y = screenHeight / recipeButton->getContentSize().height;
        recipeButton->setScale(Recipe_X * 0.2f, Recipe_Y * 0.1f);

        // Adding Listener
        recipeButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::onButtonPressed, this));
        this->addChild(recipeButton);
    }

	//// Quit Button
	ui::Button* quitButton = ui::Button::create("MainMenu/button.png", "MainMenu/buttonselected.png");
    if(isWindows && !isAndroid)
    {
        quitButton->setPosition(Vec2(screenWidth * 0.7f, screenHeight * 0.25f));
    }
    else if(isAndroid && !isWindows)
    {
        quitButton->setPosition(Vec2(screenWidth * 0.7f, screenHeight * 0.35f));
    }
	quitButton->setTitleText("QUIT");
	quitButton->setTitleFontName("fonts/Marker Felt.ttf");
	quitButton->setTitleColor(Color3B::BLACK);
	quitButton->setTitleFontSize(20.f);
	quitButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	quitButton->setName("QUIT_BUTTON");

	float Quit_X = screenWidth / quitButton->getContentSize().width;
	float Quit_Y = screenHeight / quitButton->getContentSize().height;
	quitButton->setScale(Quit_X * 0.2f, Quit_Y * 0.1f);

	// Adding Listener
	quitButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::onButtonPressed, this));
	this->addChild(quitButton);

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void MainMenu::update(float dt)
{

}

void MainMenu::onButtonPressed(Ref * sender, ui::Widget::TouchEventType eventType)
{
	string buttonName;

	if (ui::Widget::TouchEventType::ENDED == eventType)
	{
		buttonName = ((ui::Button*) sender)->getName();

		// Go to GameScene
		if (buttonName == "PLAY_BUTTON")
		{
			MainMenuChangeScene(1.f, GameScene::createScene());
		}
		
		// Go to RecipeScene
		if (buttonName == "RECIPE_BUTTON")
		{
			MainMenuChangeScene(1.f, RecipeScene::createScene());
		}

		// Quit the Game
		if (buttonName == "QUIT_BUTTON")
		{
			menuCloseCallback(this);
		}
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
