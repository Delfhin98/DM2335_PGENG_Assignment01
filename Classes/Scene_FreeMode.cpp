#include "Scene_FreeMode.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene_MainMenu.h"
//using namespace ui;

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

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	rd = new RecipeDatabase();

	//numOfRecipes = rd->iRecNum;
	// Creating a size that is valid.
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	isBoardInUse = false;
	isBoardFull = false;
	choppingBoardSpriteNames.resize(4);
	for (int i = 0; i < 4; ++i)
		choppingBoardSpriteNames[i] = "";

	iCuts = 0;

	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->setSwallowTouches(true);

	TouchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	TouchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	TouchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);

    screenWidth = visibleSize.width;
    screenHeight = visibleSize.height;

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
    Kitchen_Counter->setScale(Counter_X, Counter_Y * 0.8f);
    this->addChild(Kitchen_Counter);

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
	auto Ingredient_Egg = ui::Button::create("FreeMode/Egg_WholeEgg.png", "FreeMode/Egg_WholeEgg.png");
	Ingredient_Egg->setPosition(Vec2(screenWidth * 0.15f, screenHeight * 0.9f));
	// Scale Image
	float Egg_X = screenWidth / Ingredient_Egg->getContentSize().width;
	float Egg_Y = screenHeight / Ingredient_Egg->getContentSize().height;
	// Set Scale
	Ingredient_Egg->setScale(Egg_X * 0.05f, Egg_Y * 0.1f);
	Ingredient_Egg->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));
	// Set Name
	Ingredient_Egg->setName("EGG");

	this->addChild(Ingredient_Egg);

	// Potato
	auto Ingredient_Potato = ui::Button::create("FreeMode/Potato_Raw.png", "FreeMode/Potato_Raw.png");
	Ingredient_Potato->setPosition(Vec2(screenWidth * 0.21f, screenHeight * 0.9f));
	// Scale Image
	float Potato_X = screenWidth / Ingredient_Potato->getContentSize().width;
	float Potato_Y = screenHeight / Ingredient_Potato->getContentSize().height;
	// Set Name
	Ingredient_Potato->setName("POTATO");
	// Set Scale
	Ingredient_Potato->setScale(Potato_X * 0.05f, Potato_Y * 0.1f);
	Ingredient_Potato->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Potato);

	// Fish
	auto Ingredient_Fish = ui::Button::create("FreeMode/fish_raw.png", "FreeMode/fish_raw.png");
	Ingredient_Fish->setPosition(Vec2(screenWidth * 0.27f, screenHeight * 0.9f));
	// Scale Image
	float Fish_X = screenWidth / Ingredient_Fish->getContentSize().width;
	float Fish_Y = screenHeight / Ingredient_Fish->getContentSize().height;
	// Set Name
	Ingredient_Fish->setName("FISH");
	// Set Scale
	Ingredient_Fish->setScale(Fish_X * 0.05f, Fish_Y * 0.1f);
	Ingredient_Fish->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Fish);

	// Chicken
	auto Ingredient_Chicken = ui::Button::create("FreeMode/Chicken_Raw.png", "FreeMode/Chicken_Raw.png");
	Ingredient_Chicken->setPosition(Vec2(screenWidth * 0.33f, screenHeight * 0.9f));
	// Scale Image
	float Chicken_X = screenWidth / Ingredient_Chicken->getContentSize().width;
	float Chicken_Y = screenHeight / Ingredient_Chicken->getContentSize().height;
	// Set Name
	Ingredient_Chicken->setName("CHICKEN");
	// Set Scale
	Ingredient_Chicken->setScale(Chicken_X * 0.05f, Chicken_Y * 0.1f);
	Ingredient_Chicken->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Chicken);

	// Spinach
	auto Ingredient_Spinach = ui::Button::create("FreeMode/spinach_raw.png", "FreeMode/spinach_raw.png");
	Ingredient_Spinach->setPosition(Vec2(screenWidth * 0.39f, screenHeight * 0.9f));
	// Scale Image
	float Spinach_X = screenWidth / Ingredient_Spinach->getContentSize().width;
	float Spinach_Y = screenHeight / Ingredient_Spinach->getContentSize().height;
	// Set Name
	Ingredient_Spinach->setName("SPINACH");
	// Set Scale
	Ingredient_Spinach->setScale(Spinach_X * 0.05f, Spinach_Y * 0.1f);
	Ingredient_Spinach->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Spinach);

	// Carrot
	auto Ingredient_Carrot = ui::Button::create("FreeMode/carrot_raw.png", "FreeMode/carrot_raw.png");
	Ingredient_Carrot->setPosition(Vec2(screenWidth * 0.45f, screenHeight * 0.9f));
	// Scale Image
	float Carrot_X = screenWidth / Ingredient_Carrot->getContentSize().width;
	float Carrot_Y = screenHeight / Ingredient_Carrot->getContentSize().height;
	// Set Name
	Ingredient_Carrot->setName("CARROT");
	// Set Scale
	Ingredient_Carrot->setScale(Carrot_X * 0.05f, Carrot_Y * 0.1f);
	Ingredient_Carrot->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Carrot);

	// Tomato
	auto Ingredient_Tomato = ui::Button::create("FreeMode/tomato_raw.png", "FreeMode/tomato_raw.png");
	Ingredient_Tomato->setPosition(Vec2(screenWidth * 0.51f, screenHeight * 0.9f));
	// Scale Image
	float Tomato_X = screenWidth / Ingredient_Tomato->getContentSize().width;
	float Tomato_Y = screenHeight / Ingredient_Tomato->getContentSize().height;
	// Set Name
	Ingredient_Tomato->setName("TOMATO");
	// Set Scale
	Ingredient_Tomato->setScale(Tomato_X * 0.05f, Tomato_Y * 0.1f);
	Ingredient_Tomato->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Tomato);

	//// Butter
	//auto Ingredient_Butter = Sprite::create("FreeMode/SpicesSalt.png");
	//Ingredient_Butter->setPosition(Vec2(screenWidth * 0.57f, screenHeight * 0.9f));
	//// Scale Image
	//float Butter_X = screenWidth / Ingredient_Butter->getContentSize().width;
	//float Butter_Y = screenHeight / Ingredient_Butter->getContentSize().height;
	//// Set Name
	//Ingredient_Butter->setName("BUTTER");
	//// Set Scale
	//Ingredient_Butter->setScale(Butter_X * 0.05f, Butter_Y * 0.1f);

	//ingredientContainer.push_back(Ingredient_Butter);
	//this->addChild(Ingredient_Butter);

	//// Salt
	//auto Ingredient_Salt = Sprite::create("FreeMode/SpicesSalt.png");
	//Ingredient_Salt->setPosition(Vec2(screenWidth * 0.63f, screenHeight * 0.9f));
	//// Scale Image
	//float Salt_X = screenWidth / Ingredient_Salt->getContentSize().width;
	//float Salt_Y = screenHeight / Ingredient_Salt->getContentSize().height;
	//// Set Name
	//Ingredient_Salt->setName("SALT");
	//// Set Scale
	//Ingredient_Salt->setScale(Salt_X * 0.05f, Salt_Y * 0.1f);
	//this->addChild(Ingredient_Salt);

	//// Pepper
	//auto Ingredient_Pepper = Sprite::create("FreeMode/SpicesPepper.png");
	//Ingredient_Pepper->setPosition(Vec2(screenWidth * 0.69f, screenHeight * 0.9f));
	//// Scale Image
	//float Pepper_X = screenWidth / Ingredient_Pepper->getContentSize().width;
	//float Pepper_Y = screenHeight / Ingredient_Pepper->getContentSize().height;
	//// Set Name
	//Ingredient_Egg->setName("PEPPER");
	//// Set Scale
	//Ingredient_Pepper->setScale(Pepper_X * 0.05f, Pepper_Y * 0.1f);
	//this->addChild(Ingredient_Pepper);

	//// Fries
	//auto Ingredient_Fries = Sprite::create("FreeMode/SpicesSalt.png");
	//Ingredient_Fries->setPosition(Vec2(screenWidth * 0.75f, screenHeight * 0.9f));
	//// Scale Image
	//float Fries_X = screenWidth / Ingredient_Fries->getContentSize().width;
	//float Fries_Y = screenHeight / Ingredient_Fries->getContentSize().height;
	//// Set Name
	//Ingredient_Fries->setName("FRIES");
	//// Set Scale
	//Ingredient_Fries->setScale(Fries_X * 0.05f, Fries_Y * 0.1f);

	//ingredientContainer.push_back(Ingredient_Fries);
	//this->addChild(Ingredient_Fries);

	//// Fish Fillet
	//auto Ingredient_FishFillet = Sprite::create("FreeMode/SpicesSalt.png");
	//Ingredient_FishFillet->setPosition(Vec2(screenWidth * 0.81f, screenHeight * 0.9f));
	//// Scale Image
	//float FishFillet_X = screenWidth / Ingredient_FishFillet->getContentSize().width;
	//float FishFillet_Y = screenHeight / Ingredient_FishFillet->getContentSize().height;
	//// Set Name
	//Ingredient_FishFillet->setName("FISH_FILLET");
	//// Set Scale
	//Ingredient_FishFillet->setScale(FishFillet_X * 0.05f, FishFillet_Y * 0.1f);

	//ingredientContainer.push_back(Ingredient_FishFillet);
	//this->addChild(Ingredient_FishFillet);

	//// Roasted Chicken
	//auto Ingredient_RoastedChicken = Sprite::create("FreeMode/SpicesSalt.png");
	//Ingredient_RoastedChicken->setPosition(Vec2(screenWidth * 0.87f, screenHeight * 0.9f));
	//// Scale Image
	//float RoastedChicken_X = screenWidth / Ingredient_RoastedChicken->getContentSize().width;
	//float RoastedChicken_Y = screenHeight / Ingredient_RoastedChicken->getContentSize().height;
	//// Set Name
	//Ingredient_RoastedChicken->setName("ROASTED_CHICKEN");
	//// Set Scale
	//Ingredient_RoastedChicken->setScale(RoastedChicken_X * 0.05f, RoastedChicken_Y * 0.1f);

	//ingredientContainer.push_back(Ingredient_RoastedChicken);
	//this->addChild(Ingredient_RoastedChicken);

    // Kitchen Chopping Board
    Kitchen_ChoppingBoard = MenuItemImage::create("FreeMode/ChoppingBoard.png", "FreeMode/ChoppingBoard.png", CC_CALLBACK_1(GameScene::CuttingBoardEvent, this));
    Kitchen_ChoppingBoard->setPosition(Vec2(visibleSize.width * 0.75f, visibleSize.height * 0.35f));
    // Scale Image
    float Board_X = screenWidth / Kitchen_ChoppingBoard->getContentSize().width;
    float Board_Y = screenHeight / Kitchen_ChoppingBoard->getContentSize().height;
    // Set Scale
    Kitchen_ChoppingBoard->setScale(Board_X * 0.3f, Board_Y * 0.2f);
    Kitchen_ChoppingBoard->setName("Kitchen_ChoppingBoard");
	SelectedIngredient = "";


	// Chopping Board Pop Up Menu
    Popup_ChoppingBoard = MenuItemImage::create("FreeMode/PopUpChopBoard.png", "FreeMode/PopUpChopBoard.png", CC_CALLBACK_1(GameScene::PopupChoppingBoardEvent, this));
    Popup_ChoppingBoard->setPosition(visibleSize.width + Popup_ChoppingBoard->getContentSize().width, visibleSize.height / 2 + origin.y);
	Popup_ChoppingBoard->setScale(0.65f);
    Popup_ChoppingBoard->setLocalZOrder(2);
    Popup_ChoppingBoard->setName("Popup_ChoppingBoard");

	// Chopping Board Touch Counter Text
    Label_ChoppingBoard_Counter = Label::createWithTTF("", "fonts/Marker Felt.ttf", visibleSize.width * 0.04f);
    Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
    Label_ChoppingBoard_Counter->setTextColor(Color4B::BLACK);
    Label_ChoppingBoard_Counter->setLocalZOrder(3);
    this->addChild(Label_ChoppingBoard_Counter);

    auto menuitemholder = Menu::create(Kitchen_ChoppingBoard, Popup_ChoppingBoard, NULL);
    menuitemholder->setPosition(origin);
    menuitemholder->setName("menuitemholder");

    this->addChild(menuitemholder);

	// Button to Transfer Ingredient to Pot
	ui::Button* transferButton = ui::Button::create("MainMenu/button.png", "MainMenu/buttonselected.png");
	transferButton->setPosition(Vec2(Popup_ChoppingBoard->getContentSize().width * 0.5f, Popup_ChoppingBoard->getContentSize().height * 0.1f));
	transferButton->setTitleText("TRANSFER TO POT");
	transferButton->setTitleFontName("fonts/Marker Felt.ttf");
	transferButton->setTitleColor(Color3B::BLACK);
	transferButton->setTitleFontSize(25.f);
	transferButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	transferButton->setName("TRANSFER_BUTTON");

	float Transfer_X = screenWidth / transferButton->getContentSize().width;
	float Transfer_Y = screenHeight / transferButton->getContentSize().height;
	transferButton->setScale(Transfer_X * 0.25f, Transfer_Y * 0.1f);

	transferButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));
	Popup_ChoppingBoard->addChild(transferButton);

	//// FINISHED PRODUCT
	// Pop Up
	productPopUp = Sprite::create("FreeMode/PopUpMenu.png");
	productPopUp->setPosition(Vec2(screenWidth * 0.5f, screenHeight * 0.5f));
	productPopUp->setScale(0.f);
	productPopUp->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(productPopUp);

	// Salad
	auto Product_Salad = Sprite::create("FreeMode/Salad.png");
	Product_Salad->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Salad->setName("PRODUCT_SALAD");
	// Set Scale
	Product_Salad->setScale(0.f, 0.f);

	productContainer.push_back(Product_Salad);
	productPopUp->addChild(Product_Salad);

	// Fries
	auto Product_Fries = Sprite::create("FreeMode/Potato_Fries.png");
	Product_Fries->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Fries->setName("PRODUCT_FRIES");
	// Set Scale
	Product_Fries->setScale(0.f, 0.f);

	productContainer.push_back(Product_Fries);
	productPopUp->addChild(Product_Fries);

	// Wedges
	auto Product_Wedges = Sprite::create("FreeMode/Potato_Wedges.png");
	Product_Wedges->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Wedges->setName("PRODUCT_WEDGES");
	// Set Scale
	Product_Wedges->setScale(0.f, 0.f);

	productContainer.push_back(Product_Wedges);
	productPopUp->addChild(Product_Wedges);

	// Mashed Potato
	auto Product_Mashed = Sprite::create("FreeMode/Potato_BowlMashed.png");
	Product_Mashed->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Mashed->setName("PRODUCT_MASHED");
	// Set Scale
	Product_Mashed->setScale(0.f, 0.f);

	productContainer.push_back(Product_Mashed);
	productPopUp->addChild(Product_Mashed);

	//// Options on PopUp
	playerMoney = 0;
	sprintf(showPlayerMoney, "%d", playerMoney);

	moneyNumberButton = ui::Button::create("moneyArea.png");
	moneyNumberButton->setPosition(Vec2(screenWidth * 0.95f, screenHeight * 0.9f));
	moneyNumberButton->setTitleText(showPlayerMoney);
	moneyNumberButton->setTitleFontName("fonts/Marker Felt.ttf");
	moneyNumberButton->setTitleColor(Color3B::BLACK);
	moneyNumberButton->setTitleFontSize(30.f);
	moneyNumberButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	moneyNumberButton->setName("MONEY");

	float Money_X = screenWidth / moneyNumberButton->getContentSize().width;
	float Money_Y = screenHeight / moneyNumberButton->getContentSize().height;
	moneyNumberButton->setScale(Money_X * 0.05f, Money_Y * 0.1f);

	this->addChild(moneyNumberButton);

	// Serve Food
	ui::Button* serveFoodButton = ui::Button::create("MainMenu/button.png", "MainMenu/buttonselected.png");
	serveFoodButton->setPosition(Vec2(productPopUp->getContentSize().width * 0.1f, productPopUp->getContentSize().height * 0.1f));
	serveFoodButton->setTitleText("SERVE");
	serveFoodButton->setTitleFontName("fonts/Marker Felt.ttf");
	serveFoodButton->setTitleColor(Color3B::BLACK);
	serveFoodButton->setTitleFontSize(25.f);
	serveFoodButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	serveFoodButton->setName("SERVE_FOOD_BUTTON");

	float Serve_X = screenWidth / serveFoodButton->getContentSize().width;
	float Serve_Y = screenHeight / serveFoodButton->getContentSize().height;
	serveFoodButton->setScale(Serve_X * 0.1f, Serve_Y * 0.1f);

	// Adding Listener
	serveFoodButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));
	productPopUp->addChild(serveFoodButton);

	// Keep Food
	ui::Button* keepFoodButton = ui::Button::create("MainMenu/button.png", "MainMenu/buttonselected.png");
	keepFoodButton->setPosition(Vec2(productPopUp->getContentSize().width * 0.9f, productPopUp->getContentSize().height * 0.1f));
	keepFoodButton->setTitleText("KEEP");
	keepFoodButton->setTitleFontName("fonts/Marker Felt.ttf");
	keepFoodButton->setTitleColor(Color3B::BLACK);
	keepFoodButton->setTitleFontSize(25.f);
	keepFoodButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	keepFoodButton->setName("KEEP_FOOD_BUTTON");

	float Keep_X = screenWidth / keepFoodButton->getContentSize().width;
	float Keep_Y = screenHeight / keepFoodButton->getContentSize().height;
	keepFoodButton->setScale(Keep_X * 0.1f, Keep_Y * 0.1f);

	// Adding Listener
	keepFoodButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));
	productPopUp->addChild(keepFoodButton);


    //// Showing Recipe on GameScene - Liang Li
    // Recipe Button
    Sprite* recipeButton = Sprite::create("FreeMode/RecipeButton.png");
    recipeButton->setPosition(Vec2(playingSize.width * 0.05f, playingSize.height * 0.8f));
    objectContainer.push_back(make_pair("RECIPE_BUTTON", recipeButton));
    this->addChild(recipeButton);

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

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPos = touch->getLocation();
	//Vec2 touchInNodeSpace = (0, 0);
	Rect rect = this->getBoundingBox();

	if (isBoardInUse)
	{
		rect = Popup_ChoppingBoard->getBoundingBox();
		if (!rect.containsPoint(touchPos))
		{
			Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
			Kitchen_ChoppingBoard->setPositionX(visibleSize.width * 0.75f);
			Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
			if (isBoardFull == true)
				mainItem->setPosition(Popup_ChoppingBoard->getPosition());
			/*this->removeChildByName("potato");
			isBoardInUse = false;*/
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
	
	if (isBoardFull == false && SelectedIngredient != "")
	{
		if (SelectedIngredient == "POTATO")
		{
			mainItem = Sprite::create("FreeMode/Potato_Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("FreeMode/Potato_Peeled.png");
			choppingBoardSpriteNames[1] = ("FreeMode/Potato_Sliced.png");
			choppingBoardSpriteNames[2] = ("FreeMode/Potato_Diced.png");
			choppingBoardSpriteNames[3] = ("FreeMode/Potato_Mashed.png");
		}
		else if (SelectedIngredient == "EGG")
		{
			mainItem = Sprite::create("FreeMode/Egg_WholeEgg.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("FreeMode/Egg_UncookedFriedEgg.png");
			choppingBoardSpriteNames[1] = ("");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "TOMATO")
		{
			mainItem = Sprite::create("FreeMode/tomato_raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("FreeMode/tomato_sliced.png");
			choppingBoardSpriteNames[1] = ("FreeMode/tomato_diced.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "SPINACH")
		{
			mainItem = Sprite::create("FreeMode/spinach_raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("FreeMode/spinach_sliced.png");
			choppingBoardSpriteNames[1] = ("FreeMode/spinach_diced.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "CARROT")
		{
			mainItem = Sprite::create("FreeMode/carrot_raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("FreeMode/carrot_sliced.png");
			choppingBoardSpriteNames[1] = ("FreeMode/carrot_diced.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "FISH")
		{
			mainItem = Sprite::create("FreeMode/fish_raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("FreeMode/fish_sliced.png");
			choppingBoardSpriteNames[1] = ("FreeMode/Fish_Fillet.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "CHICKEN")
		{
			mainItem = Sprite::create("FreeMode/Chicken_Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("");
			choppingBoardSpriteNames[1] = ("");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		mainItem->setPosition(Popup_ChoppingBoard->getPosition());
		this->addChild(mainItem);
		isBoardFull = true;
	}
	else if (isBoardFull == true)
	{
		mainItem->setPosition(Popup_ChoppingBoard->getPosition());
	}
	SelectedIngredient = "";
	
}

void GameScene::PopupChoppingBoardEvent(Ref *pSender)
{
	if (isBoardFull == false)
		return;

	++iCuts;
	switch (iCuts)
	{
	case 5:
		if (choppingBoardSpriteNames[0] == "")
			break;
		mainItem->setTexture(choppingBoardSpriteNames[0]);
		mainItem->setName(choppingBoardSpriteNames[0]);
		break;
	case 10:
		if (choppingBoardSpriteNames[1] == "")
			break;
		mainItem->setTexture(choppingBoardSpriteNames[1]);
		mainItem->setName(choppingBoardSpriteNames[1]);
		break;
	case 15:
		if (choppingBoardSpriteNames[2] == "")
			break;
		mainItem->setTexture(choppingBoardSpriteNames[2]);
		mainItem->setName(choppingBoardSpriteNames[2]);
		break;
	case 20:
		if (choppingBoardSpriteNames[3] == "")
			break;
		mainItem->setTexture(choppingBoardSpriteNames[3]);
		mainItem->setName(choppingBoardSpriteNames[3]);
		break;
	}
	
	//Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
	//Kitchen_ChoppingBoard->setPositionX((visibleSize.width / 2 + origin.x) * 1.45f);
	//Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
}

void GameScene::update(float dt)
{
	Label_ChoppingBoard_Counter->setString(StringUtils::toString(iCuts));
}

// Key Pressed
void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	// Testing Purposes FOR POP UP
	if (keycode == EventKeyboard::KeyCode::KEY_1)
	{
		isProductFinish = true;
	}

	if (keycode == EventKeyboard::KeyCode::KEY_2)
	{
		isProductFinish = false;
	}

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

void GameScene::onButtonPressed(Ref * sender, ui::Widget::TouchEventType eventType)
{
	string buttonName;
	
	buttonName = ((ui::Button*) sender)->getName();

	if (ui::Widget::TouchEventType::BEGAN == eventType)
	{
		SelectedIngredient = buttonName;
	}

	if (ui::Widget::TouchEventType::ENDED == eventType)
	{
		// If Player Press TRANSFER
		if (buttonName == "TRANSFER_BUTTON")
		{
			CCLOG("TRANSFER");

			if (isBoardFull)
			{
				SelectedIngredient = mainItem->getName();
				CheckIfPlayerFinished(SelectedIngredient);
				isBoardFull = false;
				this->removeChild(mainItem);
			}

			// Close Pop Up
			Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
			Kitchen_ChoppingBoard->setPositionX(visibleSize.width * 0.75f);
			Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
		}
	}
}

// SHOWING POP UP FOR FINISHED PRODUCT
void GameScene::ShowFinalProduct(Sprite * _sprite)
{
	// Show Pop Up
	productPopUp->setScale(1.f);

	// Show Product
	float Sprite_X = screenWidth / _sprite->getContentSize().width;
	float Sprite_Y = screenHeight / _sprite->getContentSize().height;
	_sprite->setScale(Sprite_X * 0.3f, Sprite_Y * 0.3f);

	SetFinalProduct(_sprite);
}

void GameScene::CloseFinalProduct(Sprite * _sprite)
{
	// Close Pop Up
	productPopUp->setScale(0.f);

	// Close Product
	float Sprite_X = screenWidth / _sprite->getContentSize().width;
	float Sprite_Y = screenHeight / _sprite->getContentSize().height;
	_sprite->setScale(Sprite_X * 0.f, Sprite_Y * 0.f);
}

void GameScene::SetFinalProduct(Sprite * _sprite)
{
	finalProduct = _sprite;
}

Sprite * GameScene::GetFinalProduct()
{
	return finalProduct;
}

void GameScene::CheckIfPlayerFinished(string _name)
{
	for (auto it : productContainer)
	{
		// POTATO DISHES
		if (_name == "FreeMode/Potato_Sliced.png")
		{
			if (it->getName() == "PRODUCT_FRIES")
				ShowFinalProduct(it);

			CCLOG("FRENCH FRIES");
		}
		if (_name == "FreeMode/Potato_Diced.png")
		{
			CCLOG("WEDGES");
		}
		if (_name == "FreeMode/Potato_Mashed.png")
		{
			CCLOG("MASHED POTATO");
		}
	}
}
