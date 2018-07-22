#include "Scene_FreeMode.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Scene_MainMenu.h"
//using namespace ui;
USING_NS_CC;
//RecipeDatabase* RD = RecipeDatabase::GetInstance();
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
	//auto Kitchen_ChoppingBoard = Sprite::create("Freemode/Freemode_ChoppingBoard.png");
	//Kitchen_ChoppingBoard->setPosition((visibleSize.width / 2 + origin.x) * 1.45f, (visibleSize.height / 2 + origin.y) * 1.2f);
	//Kitchen_ChoppingBoard->setName("Kitchen_ChoppingBoard");

	//this->addChild(Kitchen_ChoppingBoard);
	
	
	Kitchen_ChoppingBoard = MenuItemImage::create("Freemode/Freemode_ChoppingBoard.png", "Freemode/Freemode_ChoppingBoard.png", CC_CALLBACK_1(GameScene::CuttingBoardEvent, this));
	Kitchen_ChoppingBoard->setPosition((visibleSize.width / 2 + origin.x) * 1.45f, (visibleSize.height / 2 + origin.y) * 0.5f);
	Kitchen_ChoppingBoard->setName("Kitchen_ChoppingBoard");
	
	Popup_ChoppingBoard = MenuItemImage::create("Freemode/Popup_ChoppingBoard.png", "Freemode/Popup_ChoppingBoard.png", CC_CALLBACK_1(GameScene::PopupChoppingBoardEvent, this));
	Popup_ChoppingBoard->setScale(0.65f);
	Popup_ChoppingBoard->setPosition(visibleSize.width + Popup_ChoppingBoard->getContentSize().width, visibleSize.height / 2 + origin.y);
	Popup_ChoppingBoard->setZOrder(2);
	Popup_ChoppingBoard->setName("Popup_ChoppingBoard");

	Label_ChoppingBoard_Counter = Label::createWithTTF("", "fonts/Marker Felt.ttf", visibleSize.width * 0.04f);
	Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
	Label_ChoppingBoard_Counter->setTextColor(Color4B::BLACK);
	Label_ChoppingBoard_Counter->setZOrder(3);
	this->addChild(Label_ChoppingBoard_Counter);

	auto menuitemholder = Menu::create(Kitchen_ChoppingBoard, Popup_ChoppingBoard, NULL);
	menuitemholder->setPosition(origin);
	menuitemholder->setName("menuitemholder");

	this->addChild(menuitemholder);

	//// Cooking Animation
	//cookingAnim = new CookingAnimation();
	//cookingAnim->init();
	//cookingAnim->playAnimation(this, "WaterAboutToBoil", 1.0f / 8, Vec2(Kitchen_Stove->getPositionX(), Kitchen_Stove->getPositionY() * 0.75f), 1.f);

	// Spices
	auto Spices_Salt = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(std::make_pair("salt", Spices_Salt));
	auto Spices_Pepper = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(std::make_pair("pepper", Spices_Pepper));
	
	auto Spices_Salt1 = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(std::make_pair("salt1", Spices_Salt1));
	auto Spices_Pepper1 = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(std::make_pair("pepper1", Spices_Pepper1));

	auto Spices_Salt2 = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(std::make_pair("salt2", Spices_Salt2));
	auto Spices_Pepper2 = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(std::make_pair("pepper2", Spices_Pepper2));
	auto Spices_Salt3 = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(std::make_pair("salt3", Spices_Salt3));
	auto Spices_Pepper3 = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(std::make_pair("pepper3", Spices_Pepper3));

	auto Spices_Salt4 = Sprite::create("FreeMode/Spices_Salt.png");
	objectContainer.push_back(std::make_pair("salt4", Spices_Salt4));
	auto Spices_Pepper4 = Sprite::create("FreeMode/Spices_Pepper.png");
	objectContainer.push_back(std::make_pair("pepper4", Spices_Pepper4));

	//i assume both are same png for offset in the slider( Raph )-----------------------------------------------------------------------------------------<<<<<<<<<<<<<<<<<<<
	auto Spice_offset = Spices_Salt->getContentSize().width * 0.5;
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
			it->second->setPosition(Vec2(i * 100 + Spice_offset, Scroll_SpiceShelf->getContentSize().height * 0.3f));
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

	//Vec2 pos_middle = visibleSize / 2;
	//Vec2 midCoords = Director::getInstance()->getWinSize();
	//int offsetCounter = 0;

	//auto btns = Button::create("recipebutton.png", "recipebuttonselected.png");
	//ScrollView* RecipeScrollView = ScrollView::create();
	//RecipeScrollView->setDirection(ScrollView::Direction::VERTICAL);
	//RecipeScrollView->setContentSize(Size(visibleSize.width, visibleSize.height - 150));
	//RecipeScrollView->setInnerContainerSize(Size(btns->getContentSize().width + 10,
	//	(btns->getContentSize().height * numOfRecipes) + (btns->getContentSize().height)));
	//RecipeScrollView->setBounceEnabled(false);
	//RecipeScrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	//RecipeScrollView->setPosition(Vec2(pos_middle.x, pos_middle.y));
	//RecipeScrollView->setSwallowTouches(true);
	//Vec2 pos_btns = (Vec2(visibleSize.width - btns->getContentSize().width / 2 + 10, RecipeScrollView->getInnerContainerSize().height - (btns->getContentSize().height / 2)));

	//selected_method = "";
	//text_methodtext = Label::createWithTTF(selected_method, "fonts/Marker Felt.ttf", 20);
	//text_methodtext->setPosition(pos_middle);
	//text_methodtext->setTextColor(Color4B::BLACK);
	//text_methodtext->setAlignment(TextHAlignment::LEFT);
	//this->addChild(text_methodtext, 3);
	////auto Default_buttnScale = 0.5f;

	//auto btn0 = Button::create("recipebutton.png", "recipebuttonselected.png");
	//btn0->setScale(0.5f);
	//btn0->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	//btn0->setTitleText(RD->list_recipes[offsetCounter]->GetRecipeName());
	//btn0->setCallbackName(RD->list_recipes[offsetCounter]->GetRecipeName());
	//btn0->setTitleFontName("fonts/Marker Felt.ttf");
	//btn0->setTitleColor(Color3B::BLACK);
	//btn0->setTitleFontSize(20.0f);
	//RecipeScrollView->addChild(btn0);
	//RD->list_recipes[offsetCounter]->SetMethod();
	//btn0->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	//{
	//	if (type == ui::Widget::TouchEventType::ENDED)
	//	{
	//		string temp = "Fried Egg";
	//		SetRecipeMethodText(temp);
	//	}
	//});
	//++offsetCounter;

	//auto btn1 = Button::create("recipebutton.png", "recipebuttonselected.png");
	//btn1->setScale(0.5f);
	//btn1->setPosition(Vec2(pos_btns.x, pos_btns.y - ((btns->getContentSize().height / 2) * offsetCounter)));
	//btn1->setTitleText(RD->list_recipes[offsetCounter]->GetRecipeName());
	//btn1->setCallbackName(RD->list_recipes[offsetCounter]->GetRecipeName());
	//btn1->setTitleFontName("fonts/Marker Felt.ttf");
	//btn1->setTitleColor(Color3B::BLACK);
	//btn1->setTitleFontSize(20.0f);
	//RecipeScrollView->addChild(btn1);
	//RD->list_recipes[offsetCounter]->SetMethod();
	//btn1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	//{
	//	if (type == ui::Widget::TouchEventType::ENDED)
	//	{
	//		string temp = "Boiled Egg";
	//		SetRecipeMethodText(temp);
	//	}
	//});
	//this->addChild(RecipeScrollView);

	//auto sprite_methodpanel = Sprite::create("methodpanel.png");
	//sprite_methodpanel->setAnchorPoint(Vec2(0.5f, 0.5f));
	//sprite_methodpanel->setContentSize(visibleSize / 2);
	//sprite_methodpanel->setPosition(pos_middle);
	//this->addChild(sprite_methodpanel, 1);

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
	isBoardInUse = !isBoardInUse;
	Popup_ChoppingBoard->setPositionX(visibleSize.width / 2);
	Kitchen_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
	Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
}
void GameScene::PopupChoppingBoardEvent(Ref *pSender)
{
	++iCuts;
	Popup_ChoppingBoard->setPositionX(visibleSize.width + Popup_ChoppingBoard->getContentSize().width);
	Kitchen_ChoppingBoard->setPositionX((visibleSize.width / 2 + origin.x) * 1.45f);
	Label_ChoppingBoard_Counter->setPosition(Popup_ChoppingBoard->getPositionX() - visibleSize.width * 0.25f, Popup_ChoppingBoard->getPositionY() + visibleSize.height * 0.3f);
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
	Label_ChoppingBoard_Counter->setString(to_string(iCuts));
	/*if (this->getChildByTag(popmenu)->getScale <= 0)
	{
		
	}*/
	
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
	CCDirector::getInstance()->replaceScene(TransitionJumpZoom::create(time, scene));
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