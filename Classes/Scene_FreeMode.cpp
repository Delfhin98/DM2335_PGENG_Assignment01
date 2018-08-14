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

	// Kitchen Shelf
	auto Kitchen_Shelf = Sprite::create("FreeMode/SpiceShelf.png");
	Kitchen_Shelf->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.9f));
	// Scale Image
	float Shelf_X = screenWidth / Kitchen_Shelf->getContentSize().width;
	float Shelf_Y = screenHeight / Kitchen_Shelf->getContentSize().height;
	// Set Scale
	Kitchen_Shelf->setScale(Shelf_X * 0.72f, Shelf_Y * 0.2f);
	this->addChild(Kitchen_Shelf);

	//// Ingredient on Scene
	// Egg
	auto Ingredient_Egg = ui::Button::create("Egg/WholeEgg.png", "Egg/WholeEgg.png");
	Ingredient_Egg->setPosition(Vec2(screenWidth * 0.2f, screenHeight * 0.9f));
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
	auto Ingredient_Potato = ui::Button::create("Potato/Raw.png", "Potato/Raw.png");
	Ingredient_Potato->setPosition(Vec2(screenWidth * 0.3f, screenHeight * 0.9f));
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
	auto Ingredient_Fish = ui::Button::create("Fish/Raw.png", "Fish/Raw.png");
	Ingredient_Fish->setPosition(Vec2(screenWidth * 0.4f, screenHeight * 0.9f));
	// Scale Image
	float Fish_X = screenWidth / Ingredient_Fish->getContentSize().width;
	float Fish_Y = screenHeight / Ingredient_Fish->getContentSize().height;
	// Set Name
	Ingredient_Fish->setName("FISH");
	// Set Scale
	Ingredient_Fish->setScale(Fish_X * 0.05f, Fish_Y * 0.1f);
	Ingredient_Fish->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Fish);

	//// Chicken
	//auto Ingredient_Chicken = ui::Button::create("FreeMode/Chicken_Raw.png", "FreeMode/Chicken_Raw.png");
	//Ingredient_Chicken->setPosition(Vec2(screenWidth * 0.5f, screenHeight * 0.9f));
	//// Scale Image
	//float Chicken_X = screenWidth / Ingredient_Chicken->getContentSize().width;
	//float Chicken_Y = screenHeight / Ingredient_Chicken->getContentSize().height;
	//// Set Name
	//Ingredient_Chicken->setName("CHICKEN");
	//// Set Scale
	//Ingredient_Chicken->setScale(Chicken_X * 0.05f, Chicken_Y * 0.1f);
	//Ingredient_Chicken->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	//this->addChild(Ingredient_Chicken);

	// Spinach
	auto Ingredient_Spinach = ui::Button::create("Spinach/Raw.png", "Spinach/Raw.png");
	Ingredient_Spinach->setPosition(Vec2(screenWidth * 0.6f, screenHeight * 0.9f));
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
	auto Ingredient_Carrot = ui::Button::create("Carrot/Raw.png", "Carrot/Raw.png");
	Ingredient_Carrot->setPosition(Vec2(screenWidth * 0.7f, screenHeight * 0.9f));
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
	auto Ingredient_Tomato = ui::Button::create("Tomato/Raw.png", "Tomato/Raw.png");
	Ingredient_Tomato->setPosition(Vec2(screenWidth * 0.8f, screenHeight * 0.9f));
	// Scale Image
	float Tomato_X = screenWidth / Ingredient_Tomato->getContentSize().width;
	float Tomato_Y = screenHeight / Ingredient_Tomato->getContentSize().height;
	// Set Name
	Ingredient_Tomato->setName("TOMATO");
	// Set Scale
	Ingredient_Tomato->setScale(Tomato_X * 0.05f, Tomato_Y * 0.1f);
	Ingredient_Tomato->addTouchEventListener(CC_CALLBACK_2(GameScene::onButtonPressed, this));

	this->addChild(Ingredient_Tomato);

	isPopUp = false;

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
	// Scale Pop Up Menu
	float PopUp_X = screenWidth / Popup_ChoppingBoard->getContentSize().width;
	float PopUp_Y = screenHeight / Popup_ChoppingBoard->getContentSize().height;
	// Set Scale
	Popup_ChoppingBoard->setScale(PopUp_X * 0.75f, PopUp_Y * 0.75f);
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
	transferButton->setTitleText("TRANSFER");
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
	auto Product_Fries = Sprite::create("Potato/Fries.png");
	Product_Fries->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Fries->setName("PRODUCT_FRIES");
	// Set Scale
	Product_Fries->setScale(0.f, 0.f);

	productContainer.push_back(Product_Fries);
	productPopUp->addChild(Product_Fries);

	// Wedges
	auto Product_Wedges = Sprite::create("Potato/Wedges.png");
	Product_Wedges->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Wedges->setName("PRODUCT_WEDGES");
	// Set Scale
	Product_Wedges->setScale(0.f, 0.f);

	productContainer.push_back(Product_Wedges);
	productPopUp->addChild(Product_Wedges);

	// Mashed Potato
	auto Product_Mashed = Sprite::create("Potato/MashBowl.png");
	Product_Mashed->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Mashed->setName("PRODUCT_MASHED");
	// Set Scale
	Product_Mashed->setScale(0.f, 0.f);

	productContainer.push_back(Product_Mashed);
	productPopUp->addChild(Product_Mashed);

	// Fish Fillet
	auto Product_Fillet = Sprite::create("Fish/Cooked.png");
	Product_Fillet->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Fillet->setName("PRODUCT_FISH");
	// Set Scale
	Product_Fillet->setScale(0.f, 0.f);

	productContainer.push_back(Product_Fillet);
	productPopUp->addChild(Product_Fillet);

	//// Roasted Chicken
	//auto Product_Chicken = Sprite::create("Chicken/Roasted.png");
	//Product_Chicken->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	//// Set Name
	//Product_Chicken->setName("PRODUCT_CHICKEN");
	//// Set Scale
	//Product_Chicken->setScale(0.f, 0.f);

	//productContainer.push_back(Product_Chicken);
	//productPopUp->addChild(Product_Chicken);

	// Fried Egg
	auto Product_Egg = Sprite::create("Egg/FriedEgg.png");
	Product_Egg->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Egg->setName("PRODUCT_EGG");
	// Set Scale
	Product_Egg->setScale(0.f, 0.f);

	productContainer.push_back(Product_Egg);
	productPopUp->addChild(Product_Egg);

	// Spinach
	auto Product_Spinach = Sprite::create("Spinach/Diced.png");
	Product_Spinach->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Spinach->setName("PRODUCT_SPINACH");
	// Set Scale
	Product_Spinach->setScale(0.f, 0.f);

	productContainer.push_back(Product_Spinach);
	productPopUp->addChild(Product_Spinach);

	// Tomato
	auto Product_Tomato = Sprite::create("Tomato/Diced.png");
	Product_Tomato->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Tomato->setName("PRODUCT_TOMATO");
	// Set Scale
	Product_Tomato->setScale(0.f, 0.f);

	productContainer.push_back(Product_Tomato);
	productPopUp->addChild(Product_Tomato);

	// Carrot
	auto Product_Carrot = Sprite::create("Carrot/Diced.png");
	Product_Carrot->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_Carrot->setName("PRODUCT_CARROT");
	// Set Scale
	Product_Carrot->setScale(0.f, 0.f);

	productContainer.push_back(Product_Carrot);
	productPopUp->addChild(Product_Carrot);

	// Fish Platter (Fish + Fries)
	auto Product_FishPlatter = Sprite::create("Fish/Platter.png");
	Product_FishPlatter->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	// Set Name
	Product_FishPlatter->setName("PRODUCT_FISH_PLATTER");
	// Set Scale
	Product_FishPlatter->setScale(0.f, 0.f);

	productContainer.push_back(Product_FishPlatter);
	productPopUp->addChild(Product_FishPlatter);

	//// Chicken Platter (Chicken + Fries)
	//auto Product_ChickenPlatter = Sprite::create("Chicken/Platter.png");
	//Product_ChickenPlatter->setPosition(Vec2(productPopUp->getContentSize().width * 0.5f, productPopUp->getContentSize().height * 0.5f));
	//// Set Name
	//Product_ChickenPlatter->setName("PRODUCT_CHICKEN_PLATTER");
	//// Set Scale
	//Product_ChickenPlatter->setScale(0.f, 0.f);

	//productContainer.push_back(Product_ChickenPlatter);
	//productPopUp->addChild(Product_ChickenPlatter);

	// Storing Mixed Dish
	isSpinachDiced = false;
	isTomatoDiced = false;
	isCarrotDiced = false;
	isFriesReady = false;
	isChickenReady = false;
	isFishReady = false;

	// Salad Ingredient
	mixedDishContainer.push_back(make_pair("Spinach/Diced.png", 0));
	mixedDishContainer.push_back(make_pair("Carrot/Diced.png", 0));
	mixedDishContainer.push_back(make_pair("Tomato/Diced.png", 0));

	// Platter Ingredients
	mixedDishContainer.push_back(make_pair("Potato/Fries.png", 0));
	mixedDishContainer.push_back(make_pair("Fish/Cooked.png", 0));
	mixedDishContainer.push_back(make_pair("Chicken/Roasted.png", 0));

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


	auto buttonBack = ui::Button::create("backbutton.png", "backbuttonselected.png");
	buttonBack->setPosition(Vec2(screenWidth * 0.05f, screenHeight * 0.9f));
	// Scale Image
	float Back_X = screenWidth / keepFoodButton->getContentSize().width;
	float Back_Y = screenHeight / keepFoodButton->getContentSize().height;
	buttonBack->setScale(Back_X * 0.2f, Back_Y * 0.1f);

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
			mainItem = Sprite::create("Potato/Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("Potato/Peeled.png");
			choppingBoardSpriteNames[1] = ("Potato/Sliced.png");
			choppingBoardSpriteNames[2] = ("Potato/Diced.png");
			choppingBoardSpriteNames[3] = ("Potato/Mashed.png");
		}
		else if (SelectedIngredient == "EGG")
		{
			mainItem = Sprite::create("Egg/WholeEgg.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("Egg/UnFriedEgg.png");
			choppingBoardSpriteNames[1] = ("");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "TOMATO")
		{
			mainItem = Sprite::create("Tomato/Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("Tomato/Sliced.png");
			choppingBoardSpriteNames[1] = ("Tomato/Diced.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "SPINACH")
		{
			mainItem = Sprite::create("Spinach/Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("Spinach/Sliced.png");
			choppingBoardSpriteNames[1] = ("Spinach/Diced.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "CARROT")
		{
			mainItem = Sprite::create("Carrot/Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("Carrot/Sliced.png");
			choppingBoardSpriteNames[1] = ("Carrot/Diced.png");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		else if (SelectedIngredient == "FISH")
		{
			mainItem = Sprite::create("Fish/Raw.png");
			mainItem->setName(SelectedIngredient);
			choppingBoardSpriteNames[0] = ("Fish/Fillet.png");
			choppingBoardSpriteNames[1] = ("");
			choppingBoardSpriteNames[2] = ("");
			choppingBoardSpriteNames[3] = ("");
		}
		//else if (SelectedIngredient == "CHICKEN")
		//{
		//	mainItem = Sprite::create("Chicken/Raw.png");
		//	mainItem->setName(SelectedIngredient);
		//	choppingBoardSpriteNames[0] = ("");
		//	choppingBoardSpriteNames[1] = ("");
		//	choppingBoardSpriteNames[2] = ("");
		//	choppingBoardSpriteNames[3] = ("");
		//}
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

	for (auto it : productContainer)
	{
		// Check if ALL SALAD INGREDIENT ARE IN then SHOW SALAD
		if (isSpinachDiced && isCarrotDiced && isTomatoDiced)
		{
			if (it->getName() == "PRODUCT_SALAD")
			{
				if (!isPopUp)
					ShowFinalProduct(it);
			}
		}
		
		//// Check if ALL CHICKEN PLATTER INGREDIENT ARE IN then SHOW PLATTER
		//if (isFriesReady && isChickenReady)
		//{
		//	if (it->getName() == "PRODUCT_CHICKEN_PLATTER")
		//	{
		//		if (!isPopUp)
		//			ShowFinalProduct(it);
		//	}
		//}

		// Check if ALL FISH PLATTER INGREDIENT ARE IN then SHOW PLATTER
		if (isFriesReady && isFishReady)
		{
			if (it->getName() == "PRODUCT_FISH_PLATTER")
			{
				if (!isPopUp)
					ShowFinalProduct(it);
			}
		}
	}
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

void GameScene::onButtonPressed(Ref * sender, ui::Widget::TouchEventType eventType)
{
	string buttonName;
	string ingredientName;

	buttonName = ((ui::Button*) sender)->getName();

	if (ui::Widget::TouchEventType::BEGAN == eventType)
	{
		SelectedIngredient = buttonName;

		// If SERVE PRODUCT is pressed.
		if (buttonName == "SERVE_FOOD_BUTTON")
		{
			// Add to Player Money
			playerMoney += 20;
			CCLOG("PRODUCT: %d", playerMoney);
			// Show on Scene
			sprintf(showPlayerMoney, "%d", playerMoney);
			moneyNumberButton->setTitleText(showPlayerMoney);		
			SelectedIngredient = "";

		}

		// If KEEP PRODUCT is pressed.
		if (buttonName == "KEEP_FOOD_BUTTON")
		{
			// USE PAIR VECTOR TO CHECK IF FIRST VARIABLE NAME IS THE SAME, THEN INCREASE THE SECOND VARIABLE NUMBER TO 1
			for (auto it : mixedDishContainer)
			{
				ingredientName = GetFinalProduct()->getName();

				// Diced Spinach
				if (it.first == "Spinach/Diced.png" && ingredientName == "PRODUCT_SPINACH")
				{
					it.second = 1;
					isSpinachDiced = true;
				}

				// Diced Carrot
				if (it.first == "Carrots/Diced.png" && ingredientName == "PRODUCT_CARROT")
				{
					it.second = 1;
					isCarrotDiced = true;
				}

				// Diced Tomato
				if (it.first == "Tomato/Diced.png" && ingredientName == "PRODUCT_TOMATO")
				{
					it.second = 1;
					isTomatoDiced = true;
				}

				// Fries
				if (it.first == "Potato/Fries.png" && ingredientName == "PRODUCT_FRIES")
				{
					it.second = 1;
					isFriesReady = true;
				}

				// Cooked Fish
				if (it.first == "Fish/Cooked.png" && ingredientName == "PRODUCT_FISH")
				{
					it.second = 1;
					isFishReady = true;
				}

				//// Cooked Chicken
				//if (it.first == "Chicken/Roasted.png" && ingredientName == "PRODUCT_CHICKEN")
				//{
				//	it.second = 1;
				//	isChickenReady = true;
				//}

			}

			SelectedIngredient = "";
		}

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
				SelectedIngredient = "";
				this->removeChild(mainItem);
			}

			iCuts = 0;

			// Close Pop Up
			Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
			Kitchen_ChoppingBoard->setPositionX(visibleSize.width * 0.75f);
			Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
		}

		for (auto it : productContainer)
		{
			if (buttonName == "SERVE_FOOD_BUTTON" || buttonName == "KEEP_FOOD_BUTTON")
			{
				if (GetFinalProduct()->getName() == "PRODUCT_SALAD" /*|| GetFinalProduct()->getName() == "PRODUCT_CHICKEN_PLATTER"*/ || GetFinalProduct()->getName() == "PRODUCT_FISH_PLATTER")
				{
					isSpinachDiced = false;
					isCarrotDiced = false;
					isTomatoDiced = false;
					isFriesReady = false;
					isChickenReady = false;
					isFishReady = false;

					CloseFinalProduct(it);
				}
			}

			// If SERVE PRODUCT is pressed.
			if (buttonName == "SERVE_FOOD_BUTTON")
			{
				// Close Pop Up
				CloseFinalProduct(it);
			}

			// If KEEP PRODUCT is pressed.
			if (buttonName == "KEEP_FOOD_BUTTON")
			{
				// Close Pop Up
				CloseFinalProduct(it);
			}
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
	isPopUp = true;
}

void GameScene::CloseFinalProduct(Sprite * _sprite)
{
	// Close Pop Up
	productPopUp->setScale(0.f);
	_sprite->setScale(0.f);
	isPopUp = false;
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
		if (_name == "Potato/Sliced.png")
		{
			if (it->getName() == "PRODUCT_FRIES")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_FRIES");
		}
		if (_name == "Potato/Diced.png")
		{
			if (it->getName() == "PRODUCT_WEDGES")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_WEDGES");
		}
		if (_name == "Potato/Mashed.png")
		{
			if (it->getName() == "PRODUCT_MASHED")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_MASHED");
		}

		// FISH DISH
		if (_name == "Fish/Fillet.png")
		{
			if (it->getName() == "PRODUCT_FISH")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_FISH");
		}

		//// CHICKEN DISH
		//if (_name == "Chicken/Raw.png")
		//{
		//	if (it->getName() == "PRODUCT_CHICKEN")
		//		ShowFinalProduct(it);

		//	CCLOG("PRODUCT_CHICKEN");
		//}

		if (_name == "Egg/UnFriedEgg.png")
		{
			if (it->getName() == "PRODUCT_EGG")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_EGG");
		}

		//// VEGETABLE DISH
		// DICED SPINACH
		if (_name == "Spinach/Diced.png")
		{
			if (it->getName() == "PRODUCT_SPINACH")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_SPINACH");
		}

		// DICED TOMATO
		if (_name == "Tomato/Diced.png")
		{
			if (it->getName() == "PRODUCT_TOMATO")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_TOMATO");
		}

		// DICED CARROT
		if (_name == "Carrot/Diced.png")
		{
			if (it->getName() == "PRODUCT_CARROT")
				ShowFinalProduct(it);

			CCLOG("PRODUCT_CARROT");
		}
	}
}
