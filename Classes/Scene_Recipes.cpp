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
	
	rd = new RecipeDatabase();
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
	Vec2 midCoords = Director::getInstance()->getWinSize();
	int offsetCounter = 0;

	auto btns = Button::create("recipebutton.png", "recipebuttonselected.png");
	ScrollView* RecipeScrollView = ScrollView::create();
	RecipeScrollView->setDirection(ScrollView::Direction::VERTICAL);
	RecipeScrollView->setContentSize(Size(visibleSize.width, visibleSize.height - 150));
	RecipeScrollView->setInnerContainerSize(Size(btns->getContentSize().width + 10,
		(btns->getContentSize().height * numOfRecipes) + (btns->getContentSize().height)));
	RecipeScrollView->setBounceEnabled(false);
	RecipeScrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	RecipeScrollView->setPosition(Vec2(pos_middle.x, pos_middle.y));
	RecipeScrollView->setSwallowTouches(true);
	Vec2 pos_btns = (Vec2(visibleSize.width - btns->getContentSize().width / 2 + 10, RecipeScrollView->getInnerContainerSize().height - (btns->getContentSize().height/2)));

	selected_method = "";
	text_methodtext = Label::createWithTTF(selected_method, "fonts/Marker Felt.ttf", 20);
	text_methodtext->setPosition(pos_middle);
	text_methodtext->setTextColor(Color4B::BLACK);
	text_methodtext->setAlignment(TextHAlignment::LEFT);
	this->addChild(text_methodtext, 3);
	
	auto btn0 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn0->setScale(0.5f);
	btn0->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn0->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn0->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn0->setTitleFontName("fonts/Marker Felt.ttf");
	btn0->setTitleColor(Color3B::BLACK);
	btn0->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn0);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Fried Egg";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn1 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn1->setScale(0.5f);
	btn1->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn1->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn1->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn1->setTitleFontName("fonts/Marker Felt.ttf");
	btn1->setTitleColor(Color3B::BLACK);
	btn1->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn1);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Boiled Egg";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn2 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn2->setScale(0.5f);
	btn2->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn2->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn2->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn2->setTitleFontName("fonts/Marker Felt.ttf");
	btn2->setTitleColor(Color3B::BLACK);
	btn2->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn2);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Mashed Potato";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn3 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn3->setScale(0.5f);
	btn3->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn3->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn3->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn3->setTitleFontName("fonts/Marker Felt.ttf");
	btn3->setTitleColor(Color3B::BLACK);
	btn3->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn3);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Potato Wedges";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn4 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn4->setScale(0.5f);
	btn4->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn4->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn4->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn4->setTitleFontName("fonts/Marker Felt.ttf");
	btn4->setTitleColor(Color3B::BLACK);
	btn4->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn4);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn4->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Fries";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn5 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn5->setScale(0.5f);
	btn5->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn5->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn5->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn5->setTitleFontName("fonts/Marker Felt.ttf");
	btn5->setTitleColor(Color3B::BLACK);
	btn5->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn5);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn5->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Fish Fillet";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn6 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn6->setScale(0.5f);
	btn6->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn6->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn6->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn6->setTitleFontName("fonts/Marker Felt.ttf");
	btn6->setTitleColor(Color3B::BLACK);
	btn6->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn6);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn6->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Roasted Chicken";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn7 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn7->setScale(0.5f);
	btn7->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn7->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn7->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn7->setTitleFontName("fonts/Marker Felt.ttf");
	btn7->setTitleColor(Color3B::BLACK);
	btn7->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn7);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn7->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Simple Salad";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn8 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn8->setScale(0.5f);
	btn8->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn8->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn8->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn8->setTitleFontName("fonts/Marker Felt.ttf");
	btn8->setTitleColor(Color3B::BLACK);
	btn8->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn8);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn8->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Fish Fillet Platter";
			SetRecipeMethodText(temp);
		}
	});
	++offsetCounter;

	auto btn9 = Button::create("recipebutton.png", "recipebuttonselected.png");
	btn9->setScale(0.5f);
	btn9->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	btn9->setTitleText(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn9->setCallbackName(rd->list_recipes[offsetCounter]->GetRecipeName());
	btn9->setTitleFontName("fonts/Marker Felt.ttf");
	btn9->setTitleColor(Color3B::BLACK);
	btn9->setTitleFontSize(20.0f);
	RecipeScrollView->addChild(btn9);
	rd->list_recipes[offsetCounter]->SetMethod();
	btn9->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			string temp = "Roasted Chicken Platter";
			SetRecipeMethodText(temp);
		}
	});
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

	auto sprite_methodpanel = Sprite::create("methodpanel.png");
	sprite_methodpanel->setAnchorPoint(Vec2(0.5f, 0.5f));
	sprite_methodpanel->setContentSize(visibleSize / 2);
	sprite_methodpanel->setPosition(pos_middle);
	this->addChild(sprite_methodpanel, 1);

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
	text_methodtext->setString(selected_method);
}

void RecipeScene::SetRecipeMethodText(string val)
{
	for (int i = 0; i < numOfRecipes; ++i)
	{
		if (val == rd->list_recipes[i]->GetRecipeName())
		{
			selected_method = rd->list_recipes[i]->GetMethod();
			break;
		}
	}
}

void RecipeScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Closing the Application
	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		menuCloseCallback(this);
	}
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		
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
