#include "Scene_Testing.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
RecipeDatabase* recipeData = RecipeDatabase::GetInstance();

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

	// Spice Rack
	auto rack = Sprite::create("Freemode/Freemode_SpiceShelf.png");
	rack->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height));
	this->addChild(rack);

	// Recipe Paper Sprite
	recipePaper = Sprite::create("Freemode/recipePaper.png");
	recipePaper->setPosition(Vec2(playingSize.width * 0.5f, playingSize.height * 0.82f));
	recipePaper->setScale(0.f);
	isRecipePaperShown = false;

	objectContainer.push_back(std::make_pair("RECIPE_PAPER", recipePaper));
	this->addChild(recipePaper);

	// Details on Recipe Paper Sprite
	recipeOnPaperText = "";
	recipeOnPaperLabel = Label::createWithTTF(recipeOnPaperText, "fonts/Marker Felt.ttf", 15);
	recipeOnPaperLabel->setPosition(Vec2(recipePaper->getContentSize().width * 0.5f, recipePaper->getContentSize().height * 0.5f));
	recipeOnPaperLabel->setTextColor(Color4B::BLACK);
	recipeOnPaperLabel->setAlignment(TextHAlignment::LEFT);
	recipePaper->addChild(recipeOnPaperLabel);

	// Recipe Drop Down Button
	Sprite* DropDown_RecipeButton = Sprite::create("Freemode/DropDown_RecipeButton.png");
	DropDown_RecipeButton->setPosition(Vec2(playingSize.width * 0.1f, playingSize.height * 0.8f));
	objectContainer.push_back(std::make_pair("BUTTON_RECIPE", DropDown_RecipeButton));
	this->addChild(DropDown_RecipeButton);

	// Common Pop Up Menu
	popUp = Sprite::create("Freemode/PopUp_CommonMenu.png");
	popUp->setPosition(playingSize * 0.5f);
	popUp->setScale(0.f);
	popUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	isPopUpOpen = false;

	objectContainer.push_back(std::make_pair("POPUP_MENU", popUp));
	this->addChild(popUp);

	// Scrolling Recipe Buttons
	ui::ScrollView* recipeButtons = ui::ScrollView::create();
	recipeButtons->setDirection(ui::ScrollView::Direction::VERTICAL);
	recipeButtons->setContentSize(Size(popUp->getContentSize().width * 0.5f, popUp->getContentSize().height));
	recipeButtons->setInnerContainerSize(Size(popUp->getContentSize().width * 0.5f, popUp->getContentSize().height * recipeData->iRecNum));
	recipeButtons->setBounceEnabled(true);
	recipeButtons->setSwallowTouches(true);

	// Putting Recipe Buttons into ScrollView
	for (int i = 0; i < recipeData->iRecNum; i++)
	{
		ui::Button* button = ui::Button::create("recipebutton.png");
		button->setPosition(Vec2(popUp->getPosition().x * 0.05f, i * 60));
		button->setTitleText(recipeData->list_recipes[i]->GetRecipeName());
		button->setTitleFontName("fonts/Marker Felt.ttf");
		button->setTitleColor(Color3B::BLACK);
		button->setTitleFontSize(20.0f);
		button->setAnchorPoint(Vec2(0, 0));
		button->setName(recipeData->list_recipes[i]->GetRecipeName());
		
		recipeData->list_recipes[i]->SetMethod();
		button->addTouchEventListener(CC_CALLBACK_2(SceneTesting::onTestButtonPressed, this));
		recipeButtons->addChild(button);
	}

	popUp->addChild(recipeButtons);

	// Text for Recipe Details
	recipeDetailsText = "";
	recipeDetailsLabel = Label::createWithTTF(recipeDetailsText, "fonts/Marker Felt.ttf", 15);
	recipeDetailsLabel->setPosition(Vec2(popUp->getPosition().x * 0.75f, popUp->getPosition().y * 0.75f));
	recipeDetailsLabel->setTextColor(Color4B::BLACK);
	recipeDetailsLabel->setAlignment(TextHAlignment::LEFT);
	popUp->addChild(recipeDetailsLabel);

	// Sprite to 'Pin' up Selected Recipe
	Sprite* recipePin = Sprite::create("Freemode/recipePin.png");
	recipePin->setPosition(Vec2(popUp->getPosition().x * 0.75f, popUp->getPosition().y * 0.2f));
	recipePin->setScale(0.f);
	isPinShown = false;

	objectContainer.push_back(make_pair("POPUP_RECIPE_PIN", recipePin));
	popUp->addChild(recipePin);

	// In order to display the chosen recipe
	chosenRecipe = 0;

	// Setting up camera
	auto cam = Camera::create();
	cam->setPosition(this->getPosition());

	this->scheduleUpdate();
	return true;
}

void SceneTesting::update(float dt)
{
	recipeDetailsLabel->setString(recipeDetailsText);

	for (auto it : objectContainer)
	{
		if (it.first == "POPUP_RECIPE_PIN" && isPinShown)
		{
			// Show the Pin
			it.second->setScale(1.f);
		}

		if (it.first == "RECIPE_PAPER" && isRecipePaperShown)
		{
			// Show the Paper
			it.second->setScale(1.f);
		}
	}
	
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
		// If POP UP is CLOSED
		if (!isPopUpOpen)
		{
			rect = it->second->getBoundingBox();

			// If TOUCH is INSIDE 'BUTTON' SPRITE BOUNDING BOX
			if (rect.containsPoint(p))
			{
				// Check what am I touching
				if (it->first == "BUTTON_RECIPE")
				{
					CCLOG("TOUCHING RECIPE BUTTON");
					openPopUpMenu(it->first);

					return true;
				}
			}
		}
		// If POP UP MENU IS OPEN
		else
		{
			pInNodeSpace = it->second->getParent()->convertToNodeSpace(p);
			rect = it->second->getBoundingBox();

			if (rect.containsPoint(pInNodeSpace))
			{
				// Check what am I touching
				if (it->first == "POPUP_RECIPE_PIN")
				{
					CCLOG("TOUCHING PIN");
					
					// Show Recipe Paper
					isRecipePaperShown = true;
					// Set Text
					recipeOnPaperLabel->setString(recipeData->list_recipes[chosenRecipe]->GetRecipeName());
					// Close Pop Up Immediately
					closePopUpMenu();

					return true;
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

void SceneTesting::onTestButtonPressed(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType eventType)
{
	string buttonName;
	string recipeName;

	if (ui::Widget::TouchEventType::BEGAN == eventType)
	{
		buttonName = ((ui::Button*) sender)->getName();

		for (int i = 0; i < recipeData->iRecNum; i++)
		{
			recipeName = recipeData->list_recipes[i]->GetRecipeName();

			// If Selected Button is inside the Recipe Database
			if (buttonName == recipeName)
			{
				recipeDetailsText = recipeData->list_recipes[i]->GetMethod();
				chosenRecipe = i;
				isPinShown = true;
			}
		}
	}
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
	popUp->setScale(1.2f);
}

void SceneTesting::closePopUpMenu()
{
	isPopUpOpen = false;
	recipeDetailsText = "";
	popUp->setScale(0.f);
}