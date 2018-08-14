#include "Scene_FreeMode.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene_MainMenu.h"
//using namespace ui;

USING_NS_CC;
RecipeDatabase* recipeDatabase = RecipeDatabase::GetInstance();

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

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//numOfRecipes = RD->iRecNum;
	// Creating a size that is valid.
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	isBoardInUse = false;
	iCuts = 0;

	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->setSwallowTouches(true);

	TouchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	TouchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	TouchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);

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

    float screenWidth = visibleSize.width;
    float screenHeight = visibleSize.height;

	// Freemode Background + Kitchen
	// Background
	auto BG_Image = Sprite::create("FreeMode/Background.png");
	BG_Image->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    // Scale Image
	float BG_X = screenWidth / BG_Image->getContentSize().width;
	float BG_Y = screenHeight / BG_Image->getContentSize().height;
	// Set Scaling Factor to BG_Image.
    BG_Image->setScale(BG_X, BG_Y);
    this->addChild(BG_Image);

	// Kitchen Counter
	auto Kitchen_Counter = Sprite::create("FreeMode/KitchenCounter.png");
	Kitchen_Counter->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.1f));
    Kitchen_Counter->setAnchorPoint(Vec2(0.5, 0.5));
    // Scale Image
    float Counter_X = screenWidth / Kitchen_Counter->getContentSize().width;
    float Counter_Y = screenHeight / Kitchen_Counter->getContentSize().height;
    // Set Scale
    Kitchen_Counter->setScaleX(Counter_X);
    this->addChild(Kitchen_Counter);

    // Kitchen Spice Rack
    /*
	auto Kitchen_SpiceRack = Sprite::create("FreeMode/SpiceShelf.png");
	Kitchen_SpiceRack->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.9f));
    // Scale Image
    float SpiceRack_X = screenWidth / Kitchen_SpiceRack->getContentSize().width;
    float SpiceRack_Y = screenHeight / Kitchen_SpiceRack->getContentSize().height;
    // Set Scale
    Kitchen_SpiceRack->setScale(SpiceRack_Y * 0.2f ,SpiceRack_X * 0.75f);
    this->addChild(Kitchen_SpiceRack);
    */

	// Kitchen Stove
	auto Kitchen_Stove = Sprite::create("FreeMode/Stove.png");
	Kitchen_Stove->setPosition(Vec2(visibleSize.width * 0.35f, visibleSize.height * 0.25f));
    // Scale Image
    float Stove_X = screenWidth / Kitchen_Stove->getContentSize().width;
    float Stove_Y = screenHeight / Kitchen_Stove->getContentSize().height;
    // Set Scale
    Kitchen_Stove->setScale(Stove_X * 0.4f, Stove_Y * 0.2f);
	this->addChild(Kitchen_Stove);

	// Kitchen Oven
	auto Kitchen_Oven = Sprite::create("FreeMode/Oven.png");
	Kitchen_Oven->setPosition(Vec2(visibleSize.width * 0.35f, visibleSize.height * 0.10f));
    // Scale Image
    float Oven_X = screenWidth / Kitchen_Oven->getContentSize().width;
    float Oven_Y = screenHeight / Kitchen_Oven->getContentSize().height;
    // Set Scale
    Kitchen_Oven->setScale(Oven_X * 0.4f, Oven_Y * 0.2f);
	this->addChild(Kitchen_Oven);

    //// Ingredient on Scene
    // Egg
    auto Ingredient_Egg = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Egg->setPosition(Vec2(visibleSize.width * 0.15f, visibleSize.height * 0.9f));
    // Scale Image
    float Egg_X = screenWidth / Ingredient_Egg->getContentSize().width;
    float Egg_Y = screenHeight / Ingredient_Egg->getContentSize().height;
    // Set Scale
    Ingredient_Egg->setScale(Egg_X * 0.05f, Egg_Y * 0.1f);
    this->addChild(Ingredient_Egg);

    // Potato
    auto Ingredient_Potato = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Potato->setPosition(Vec2(visibleSize.width * 0.21f, visibleSize.height * 0.9f));
    // Scale Image
    float Potato_X = screenWidth / Ingredient_Potato->getContentSize().width;
    float Potato_Y = screenHeight / Ingredient_Potato->getContentSize().height;
    // Set Scale
    Ingredient_Potato->setScale(Potato_X * 0.05f, Potato_Y * 0.1f);
    this->addChild(Ingredient_Potato);

    // Fish
    auto Ingredient_Fish = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Fish->setPosition(Vec2(visibleSize.width * 0.27f, visibleSize.height * 0.9f));
    // Scale Image
    float Fish_X = screenWidth / Ingredient_Fish->getContentSize().width;
    float Fish_Y = screenHeight / Ingredient_Fish->getContentSize().height;
    // Set Scale
    Ingredient_Fish->setScale(Fish_X * 0.05f, Fish_Y * 0.1f);
    this->addChild(Ingredient_Fish);

    // Chicken
    auto Ingredient_Chicken = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Chicken->setPosition(Vec2(visibleSize.width * 0.33f, visibleSize.height * 0.9f));
    // Scale Image
    float Chicken_X = screenWidth / Ingredient_Chicken->getContentSize().width;
    float Chicken_Y = screenHeight / Ingredient_Chicken->getContentSize().height;
    // Set Scale
    Ingredient_Chicken->setScale(Chicken_X * 0.05f, Chicken_Y * 0.1f);
    this->addChild(Ingredient_Chicken);

    // Spinach
    auto Ingredient_Spinach = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Spinach->setPosition(Vec2(visibleSize.width * 0.39f, visibleSize.height * 0.9f));
    // Scale Image
    float Spinach_X = screenWidth / Ingredient_Spinach->getContentSize().width;
    float Spinach_Y = screenHeight / Ingredient_Spinach->getContentSize().height;
    // Set Scale
    Ingredient_Spinach->setScale(Spinach_X * 0.05f, Spinach_Y * 0.1f);
    this->addChild(Ingredient_Spinach);

    // Carrot
    auto Ingredient_Carrot = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Carrot->setPosition(Vec2(visibleSize.width * 0.45f, visibleSize.height * 0.9f));
    // Scale Image
    float Carrot_X = screenWidth / Ingredient_Carrot->getContentSize().width;
    float Carrot_Y = screenHeight / Ingredient_Carrot->getContentSize().height;
    // Set Scale
    Ingredient_Carrot->setScale(Carrot_X * 0.05f, Carrot_Y * 0.1f);
    this->addChild(Ingredient_Carrot);

    // Tomato
    auto Ingredient_Tomato = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Tomato->setPosition(Vec2(visibleSize.width * 0.51f, visibleSize.height * 0.9f));
    // Scale Image
    float Tomato_X = screenWidth / Ingredient_Tomato->getContentSize().width;
    float Tomato_Y = screenHeight / Ingredient_Tomato->getContentSize().height;
    // Set Scale
    Ingredient_Tomato->setScale(Tomato_X * 0.05f, Tomato_Y * 0.1f);
    this->addChild(Ingredient_Tomato);

    // Butter
    auto Ingredient_Butter = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Butter->setPosition(Vec2(visibleSize.width * 0.57f, visibleSize.height * 0.9f));
    // Scale Image
    float Butter_X = screenWidth / Ingredient_Butter->getContentSize().width;
    float Butter_Y = screenHeight / Ingredient_Butter->getContentSize().height;
    // Set Scale
    Ingredient_Butter->setScale(Butter_X * 0.05f, Butter_Y * 0.1f);
    this->addChild(Ingredient_Butter);

    // Salt
    auto Ingredient_Salt = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Salt->setPosition(Vec2(visibleSize.width * 0.63f, visibleSize.height * 0.9f));
    // Scale Image
    float Salt_X = screenWidth / Ingredient_Salt->getContentSize().width;
    float Salt_Y = screenHeight / Ingredient_Salt->getContentSize().height;
    // Set Scale
    Ingredient_Salt->setScale(Salt_X * 0.05f, Salt_Y * 0.1f);
    this->addChild(Ingredient_Salt);

    // Pepper
    auto Ingredient_Pepper = Sprite::create("FreeMode/SpicesPepper.png");
    Ingredient_Pepper->setPosition(Vec2(visibleSize.width * 0.69f, visibleSize.height * 0.9f));
    // Scale Image
    float Pepper_X = screenWidth / Ingredient_Pepper->getContentSize().width;
    float Pepper_Y = screenHeight / Ingredient_Pepper->getContentSize().height;
    // Set Scale
    Ingredient_Pepper->setScale(Pepper_X * 0.05f, Pepper_Y * 0.1f);
    this->addChild(Ingredient_Pepper);

    // Fries
    auto Ingredient_Fries = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_Fries->setPosition(Vec2(visibleSize.width * 0.75f, visibleSize.height * 0.9f));
    // Scale Image
    float Fries_X = screenWidth / Ingredient_Fries->getContentSize().width;
    float Fries_Y = screenHeight / Ingredient_Fries->getContentSize().height;
    // Set Scale
    Ingredient_Fries->setScale(Fries_X * 0.05f, Fries_Y * 0.1f);
    this->addChild(Ingredient_Fries);

    // Fish Fillet
    auto Ingredient_FishFillet = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_FishFillet->setPosition(Vec2(visibleSize.width * 0.81f, visibleSize.height * 0.9f));
    // Scale Image
    float FishFillet_X = screenWidth / Ingredient_FishFillet->getContentSize().width;
    float FishFillet_Y = screenHeight / Ingredient_FishFillet->getContentSize().height;
    // Set Scale
    Ingredient_FishFillet->setScale(FishFillet_X * 0.05f, FishFillet_Y * 0.1f);
    this->addChild(Ingredient_FishFillet);

    // Roasted Chicken
    auto Ingredient_RoastedChicken = Sprite::create("FreeMode/SpicesSalt.png");
    Ingredient_RoastedChicken->setPosition(Vec2(visibleSize.width * 0.87f, visibleSize.height * 0.9f));
    // Scale Image
    float RoastedChicken_X = screenWidth / Ingredient_RoastedChicken->getContentSize().width;
    float RoastedChicken_Y = screenHeight / Ingredient_RoastedChicken->getContentSize().height;
    // Set Scale
    Ingredient_RoastedChicken->setScale(RoastedChicken_X * 0.05f, RoastedChicken_Y * 0.1f);
    this->addChild(Ingredient_RoastedChicken);

	//// Cooking Animation
	//cookingAnim = new CookingAnimation();
	//cookingAnim->init();
	//cookingAnim->playAnimation(this, "WaterAboutToBoil", 1.0f / 8, Vec2(Kitchen_Stove->getPositionX(), Kitchen_Stove->getPositionY() * 0.75f), 1.f);

    /*
	// Spices
	auto Spices_Salt = Sprite::create("FreeMode/SpicesSalt.png");
	objectContainer.push_back(std::make_pair("salt", Spices_Salt));
	auto Spices_Pepper = Sprite::create("FreeMode/SpicesPepper.png");
	objectContainer.push_back(std::make_pair("pepper", Spices_Pepper));

	//i assume both are same png for offset in the slider( Raph )-----------------------------------------------------------------------------------------<<<<<<<<<<<<<<<<<<<
	//auto Spice_offset = Spices_Salt->getContentSize().width * 0.5;

    //float testingX = Kitchen_SpiceRack->getContentSize().width * 0.9f;
    //float testingY = Kitchen_SpiceRack->getContentSize().height * 2.f;

    // Scrolling Spice Shelf
	ui::ScrollView *Scroll_SpiceShelf = ui::ScrollView::create();
	Scroll_SpiceShelf->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	Scroll_SpiceShelf->setContentSize(Size(testingX, testingY));
	Scroll_SpiceShelf->setInnerContainerSize(Size(1000, 200));
	Scroll_SpiceShelf->setBounceEnabled(true);
	Scroll_SpiceShelf->setAnchorPoint(Vec2(0.5, 0.5));
	Scroll_SpiceShelf->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));

	for (auto it = objectContainer.begin(); it != objectContainer.end();)
	{
		for (int i = 0; i < objectContainer.size(); i++)
		{
			it->second->setPosition(Vec2(i * 100 + Spice_offset, Scroll_SpiceShelf->getContentSize().height * 0.3f));
			Scroll_SpiceShelf->addChild(it->second);
			
			it++;
		}
	}

	this->addChild(Scroll_SpiceShelf);
    */

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

    /*
	popmenu = 42;//i set randomly so no taking my tag
	auto popupmen = ui::Button::create("backbutton.png", "backbuttonselected.png");
	popupmen->setPosition(Vec2((visibleSize.width / 2), (visibleSize.height / 2 ) * 1.85f));
	popupmen->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (!this->getChildByTag(popmenu))
			{
				openpop();
			}
			else
			{
				closepop();
				//this->removeChildByTag(popmenu);

			}
		}
	});
	this->addChild(popupmen);
    */

	Kitchen_ChoppingBoard = MenuItemImage::create("FreeMode/ChoppingBoard.png", "FreeMode/ChoppingBoard.png", CC_CALLBACK_1(GameScene::CuttingBoardEvent, this));
	Kitchen_ChoppingBoard->setPosition((visibleSize.width / 2 + origin.x) * 1.45f, (visibleSize.height / 2 + origin.y) * 0.5f);
	Kitchen_ChoppingBoard->setName("Kitchen_ChoppingBoard");

	Popup_ChoppingBoard = MenuItemImage::create("FreeMode/PopUpChopBoard.png", "FreeMode/PopUpChopBoard.png", CC_CALLBACK_1(GameScene::PopupChoppingBoardEvent, this));
	Popup_ChoppingBoard->setScale(0.65f);
	Popup_ChoppingBoard->setPosition(visibleSize.width + Popup_ChoppingBoard->getContentSize().width, visibleSize.height / 2 + origin.y);
	Popup_ChoppingBoard->setLocalZOrder(2);
	Popup_ChoppingBoard->setName("Popup_ChoppingBoard");
	
	Label_ChoppingBoard_Counter = Label::createWithTTF("", "fonts/Marker Felt.ttf", visibleSize.width * 0.04f);
	Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
	Label_ChoppingBoard_Counter->setTextColor(Color4B::BLACK);
	Label_ChoppingBoard_Counter->setLocalZOrder(3);
	this->addChild(Label_ChoppingBoard_Counter);

	auto menuitemholder = Menu::create(Kitchen_ChoppingBoard, Popup_ChoppingBoard, NULL);
	menuitemholder->setPosition(origin);
	menuitemholder->setName("menuitemholder");

	this->addChild(menuitemholder);

	//// Showing Recipe on GameScene - Liang Li
	// Recipe Button
	Sprite* recipeButton = Sprite::create("FreeMode/RecipeButton.png");
	recipeButton->setPosition(Vec2(playingSize.width * 0.05f, playingSize.height * 0.8f));
	objectContainer.push_back(make_pair("RECIPE_BUTTON", recipeButton));
	this->addChild(recipeButton);

	// Common Pop Up Menu
	popUp = Sprite::create("FreeMode/PopUpMenu.png");
	popUp->setPosition(playingSize * 0.5f);
	popUp->setScale(0.f);
	popUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	isPopUpOpen = false;

	objectContainer.push_back(make_pair("POPUP", popUp));
	this->addChild(popUp);

	// Scrolling Recipe Buttons
	ui::ScrollView* recipeButtons = ui::ScrollView::create();
	recipeButtons->setDirection(ui::ScrollView::Direction::VERTICAL);
	recipeButtons->setContentSize(Size(popUp->getContentSize().width * 0.5f, popUp->getContentSize().height));
	recipeButtons->setInnerContainerSize(Size(popUp->getContentSize().width * 0.5f, popUp->getContentSize().height * recipeDatabase->iRecNum));
	recipeButtons->setBounceEnabled(true);
	recipeButtons->setSwallowTouches(true);

	// Putting Recipe Buttons into ScrollView
	for (int i = 0; i < recipeDatabase->iRecNum; i++)
	{
		ui::Button* button = ui::Button::create("recipebutton.png");
		button->setPosition(Vec2(popUp->getPosition().x * 0.05f, i * 60));
		button->setTitleText(recipeDatabase->list_recipes[i]->GetRecipeName());
		button->setTitleFontName("fonts/Marker Felt.ttf");
		button->setTitleColor(Color3B::BLACK);
		button->setTitleFontSize(20.0f);
		button->setAnchorPoint(Vec2(0, 0));
		button->setName(recipeDatabase->list_recipes[i]->GetRecipeName());

		recipeDatabase->list_recipes[i]->SetMethod();
		button->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));
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

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPos = touch->getLocation();
	//Vec2 touchInNodeSpace = (0, 0);
	
	if (isBoardInUse)
	{
		Rect boardRect = Popup_ChoppingBoard->getBoundingBox();
		if (!boardRect.containsPoint(touchPos))
		{
			iCuts = 0;
			Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
			Kitchen_ChoppingBoard->setPositionX((visibleSize.width / 2 + origin.x) * 1.45f);
			Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
			this->removeChildByName("potato");
			isBoardInUse = false;
			return true;
		}
	}

	//// Showing Recipe on Gamescene - Liang Li
	Rect rect = this->getBoundingBox();

	for (auto it = objectContainer.begin(); it != objectContainer.end(); it++)
	{
		// If PopUp is CLOSED
		if (!isPopUpOpen)
		{
			rect = it->second->getBoundingBox();

			if (it->first == "RECIPE_BUTTON")
			{
				// If User touches Recipe Button
				if (rect.containsPoint(touchPos))
				{
					openPopUpMenu(it->first);
					return true;
				}
			}
		}
	}

	// If POP UP MENU IS OPEN - Liang Li
	if (isPopUpOpen)
	{
		Rect popUpRect = popUp->getBoundingBox();

		// If user TOUCHES POP UP
		if (popUpRect.containsPoint(touchPos))
		{
			// NOTHING HAPPENS
			return true;
		}

		// If user TOUCHES OUTSIDE OF POP UP
		if (!popUpRect.containsPoint(touchPos))
		{
			closePopUpMenu();
			return true;
		}
	}

	return false;
}
bool GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return false;
}
void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void GameScene::CuttingBoardEvent(Ref *pSender)
{
	if(isBoardInUse == false)
		isBoardInUse = true;
	Popup_ChoppingBoard->setPositionX(visibleSize.width / 2);
	Kitchen_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
	Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
	SelectedIngredient = Sprite::create("FreeMode/Potato_Raw.png");
	SelectedIngredient->setPosition(Popup_ChoppingBoard->getPosition());
	SelectedIngredient->setName("potato");
	this->addChild(SelectedIngredient);
}

void GameScene::PopupChoppingBoardEvent(Ref *pSender)
{
	++iCuts;
	if (iCuts == 5)
	{
		SelectedIngredient->setTexture("FreeMode/Potato_Peeled.png");
	}
	else if (iCuts == 10)
	{
		SelectedIngredient->setTexture("FreeMode/Potato_Sliced.png");
	}
	else if (iCuts == 15)
	{
		SelectedIngredient->setTexture("FreeMode/Potato_Diced.png");
	}
	//Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
	//Kitchen_ChoppingBoard->setPositionX((visibleSize.width / 2 + origin.x) * 1.45f);
	//Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
}

//void GameScene::SetRecipeMethodText(string val)
//{
//	for (int i = 0; i < numOfRecipes; ++i)
//	{
//		if (val == RD->list_recipes[i]->GetRecipeName())
//		{
//			selected_method = RD->list_recipes[i]->GetMethod();
//		}
//	}
//}
void GameScene::update(float dt)
{
	Label_ChoppingBoard_Counter->setString(StringUtils::toString(iCuts));
	recipeDetailsLabel->setString(recipeDetailsText);
}

// Key Pressed
void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Testing Purposes
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		//menuChangeScene(1.5f, MainMenu::createScene());
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
	CCDirector::getInstance()->replaceScene(TransitionFade::create(time, scene));
}

void GameScene::openpop()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite_methodpanel = Sprite::create("methodpanel.png");
	sprite_methodpanel->setAnchorPoint(Vec2(0.5f, 0.5f));
	sprite_methodpanel->setContentSize(visibleSize / 200);
	sprite_methodpanel->setPosition(Vec2((visibleSize.width / 2), (visibleSize.height / 2) * 1.85f));
	sprite_methodpanel->setTag(popmenu);
	auto sprite_methodpanel1 = Sprite::create("strawberry.png");
	sprite_methodpanel1->setAnchorPoint(Vec2(0.5f, 0.5f));
	sprite_methodpanel1->setContentSize(visibleSize / 200);
	sprite_methodpanel1->setPosition(Vec2((visibleSize.width / 2), (visibleSize.height / 2) * 1.85f));
	sprite_methodpanel1->setTag(popmenu);
	this->addChild(sprite_methodpanel, 1);
	this->addChild(sprite_methodpanel1, 1);

	//move to center
	auto moveEvent = MoveTo::create(0.25f, Vec2((visibleSize.width / 2), (visibleSize.height / 2)));
	auto moveEvent1 = MoveTo::create(0.25f, Vec2((visibleSize.width / 2), (visibleSize.height / 2)));

	//scale to menu size
	auto increasesize = ScaleTo::create(0.25f, 100);
	auto increasesize1 = ScaleTo::create(0.25f, 90);
	//action
	sprite_methodpanel->runAction(moveEvent);
	sprite_methodpanel->runAction(increasesize);
	sprite_methodpanel1->runAction(moveEvent1);
	sprite_methodpanel1->runAction(increasesize1);
}

void GameScene::closepop()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite_methodpanel = this->getChildByTag(popmenu);
	//sprite_methodpanel->setContentSize(visibleSize / 200);
	//sprite_methodpanel->setPosition(Vec2((visibleSize.width / 2), (visibleSize.height / 2) * 1.85f));

	//this->addChild(sprite_methodpanel, 1);
	//move to center
	auto moveEvent = MoveTo::create(0.25f, Vec2((visibleSize.width / 2), (visibleSize.height / 2) * 1.85f));
	//scale to menu size
	auto increasesize = ScaleTo::create(0.25f, 0);
	//action

	sprite_methodpanel->runAction(moveEvent);
	sprite_methodpanel->runAction(increasesize);
	
	
	//DelayTime().setDuration(0.25f);
	//DelayTime();
	this->removeChildByTag(popmenu);
	this->removeChildByTag(popmenu);
		//return true;
}

//// Showing Recipe on GameScene - Liang Li
void GameScene::openPopUpMenu(const char * objectID)
{
	isPopUpOpen = true;
	popUp->setScale(1.2f);

}

void GameScene::closePopUpMenu()
{
	isPopUpOpen = false;
	recipeDetailsText = "";
	popUp->setScale(0.f);
}

// Button Pressed - Liang Li
void GameScene::onButtonPressed(Ref * sender, ui::Widget::TouchEventType eventType)
{
	string buttonName;
	string recipeName;

	if (ui::Widget::TouchEventType::BEGAN == eventType)
	{
		buttonName = ((ui::Button*) sender)->getName();

		for (int i = 0; i < recipeDatabase->iRecNum; i++)
		{
			recipeName = recipeDatabase->list_recipes[i]->GetRecipeName();

			// If Selected Button is inside the Recipe Database
			if (buttonName == recipeName)
			{
				recipeDetailsText = recipeDatabase->list_recipes[i]->GetMethod();
			}
		}
	}
}

//INVENTORY
bool GameScene::CHECKstore()
{
	if (storage.size() == countsize)
	{
		return true;//if the storage has no duplicates with the item thats being added
	}
	else {

		return false;
	}
}
void GameScene::addstore(pair<string, int> lel)
{
	storage.insert(lel);
	countsize++;
	if (!CHECKstore())
	{
		pair<string, int> temp;
		int temp2;
		temp = lel;
		temp2 = storage.find(lel.first)->second;
		//cout << "THIS IS MY TEMP   " << temp.first << " : " << temp.second << endl;
		
		temp.second = temp.second + temp2;
		//cout << "this is temp now " << temp.second << endl;
		storage.erase(temp.first);
		storage.insert(temp);

		countsize--;
	}
}
void GameScene::addstoreB(pair<string, int> lelB)
{
	storageB.insert(lelB);
	Bcountsize++;
}
void GameScene::add_both(pair<string, int> lOl)
{
	addstore(lOl);
	addstoreB(lOl);
}
/*
void GameScene::PRINT()
{
	cout << "MAP 1" << endl;
	for (auto& x : storage)
	{

		cout << x.first << " : " << x.second << '\n';
	}

	cout << "MAP 2" << endl;
	for (auto&x : storageB)
	{
		cout << x.first << " : " << x.second << '\n';
	}


	cout << "-----------------------------------------------------------------------------------" << endl;
}
*/
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