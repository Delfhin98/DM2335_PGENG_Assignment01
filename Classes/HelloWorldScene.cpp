#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(0, 0);
	nodeItems->addChild(sprite, 0);
	this->addChild(nodeItems, 1);

	int m_iLimit = std::ceil(visibleSize.width / sprite->getContentSize().width);
	for (int i = 0; i < m_iLimit; ++i)
	{
		auto secondSprite = Sprite::createWithTexture(sprite->getTexture());
		secondSprite->setAnchorPoint(Vec2::ZERO);
		secondSprite->setPosition(0 + (i * sprite->getContentSize().width * sprite->getScaleX()), 0);
		nodeItems->addChild(secondSprite, 1);
	}
	
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	bluething = new GameChar();
	bluething->init("Blue_Front1.png", "mainSprite", 100, (visibleSize.height - playingSize.height));

	spriteNode->addChild(bluething->getSprite(), 1);
	this->addChild(spriteNode, 1);

	/*auto moveEvent = MoveBy::create(5, Vec2(200, 0));
	mainSprite->runAction(moveEvent);

	auto delay = DelayTime::create(5.0f);
	auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	mainSprite->runAction(sequence);*/

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto listener2 = EventListenerMouse::create();
	listener2->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
    //                                       "CloseNormal.png",
    //                                       "CloseSelected.png",
    //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    //if (closeItem == nullptr ||
    //    closeItem->getContentSize().width <= 0 ||
    //    closeItem->getContentSize().height <= 0)
    //{
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}
    //else
    //{
    //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    //    float y = origin.y + closeItem->getContentSize().height/2;
    //    closeItem->setPosition(Vec2(x,y));
    //}

    //// create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}
	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
	bluething->Update(dt);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		bluething->MoveChar(eRight);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		bluething->MoveChar(eLeft);
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		bluething->MoveChar(eStop);
	}
}

void HelloWorld::onMouseDown(Event* event)
{
	EventMouse * e = (EventMouse*)event;

	bluething->MoveCharByCoord(e->getCursorX(), e->getCursorY());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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
