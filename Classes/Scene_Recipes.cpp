#include "Scene_Recipes.h"

#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
using namespace ui;
USING_NS_CC;

Scene* RecipeScene::createScene()
{
	return RecipeScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool RecipeScene::init()
{
	// Super Init First
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	RecipeDatabase* rd = RecipeDatabase::GetInstance();
	numOfRecipes = rd->iRecNum;
	
	// Creating a size that is valid.
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	//string test = to_string(numOfRecipes);
	// Create and initialize a label
	auto titleLabel = Label::createWithTTF("RECIPES", "fonts/Marker Felt.ttf", visibleSize.width * 0.05f);
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

	Vec2 pos_middle = visibleSize / 2;
	//Vec2 pos_offset = Vec2(0, -50);

	auto btns = Button::create("recipebutton.png", "recipebuttonselected.png");
	ScrollView* RecipeScrollView = ScrollView::create();
	RecipeScrollView->setDirection(ScrollView::Direction::VERTICAL);
	RecipeScrollView->setContentSize(Size(visibleSize.width, visibleSize.height - 150));
	RecipeScrollView->setInnerContainerSize(Size(btns->getContentSize().width + 10,
		(btns->getContentSize().height * numOfRecipes) + (btns->getContentSize().height)));
	//RecipeScrollView->setBackGroundImage("scrollpanel.png");
	RecipeScrollView->setBounceEnabled(false);
	RecipeScrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	RecipeScrollView->setPosition(Vec2(pos_middle.x, pos_middle.y));
	Vec2 pos_btns = (Vec2(visibleSize.width - btns->getContentSize().width / 2 + 10, RecipeScrollView->getInnerContainerSize().height - (btns->getContentSize().height/2)));
	for (int i = 0; i < numOfRecipes; ++i)
	{
		btns = Button::create("recipebutton.png", "recipebuttonselected.png");
		btns->setScale(0.5f);
		btns->setPosition(Vec2(pos_btns.x,pos_btns.y - ((btns->getContentSize().height / 2) * i)));
		btns->setTitleText(rd->list_recipes[i]->GetRecipeName());
		btns->setTitleFontName("fonts/Marker Felt.ttf");
		btns->setTitleColor(Color3B::BLACK);
		btns->setTitleFontSize(20.0f);
		RecipeScrollView->addChild(btns);
	}
	this->addChild(RecipeScrollView);

	auto btn_back = Button::create("backbutton.png", "backbuttonselected.png");
	btn_back->setPosition(Vec2(titleLabel->getPositionX() - (titleLabel->getContentSize().width / 2)
		- btn_back->getContentSize().width, titleLabel->getPositionY()));
	btn_back->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			RecipeDatabaseChangeScene(1.0f, MainMenu::createScene());
		}
	});
	this->addChild(btn_back);

	auto Keyboardlistener = EventListenerKeyboard::create();
	Keyboardlistener->onKeyPressed = CC_CALLBACK_2(RecipeScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboardlistener, this);

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void RecipeScene::update(float dt)
{
	
}

void RecipeScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Closing the Application
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		menuCloseCallback(this);
	}
}

void RecipeScene::menuCloseCallback(Ref* pSender)
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

void RecipeScene::RecipeDatabaseChangeScene(float time, cocos2d::Scene * scene)
{
	CCDirector::getInstance()->replaceScene(TransitionFade::create(time, scene));
}
