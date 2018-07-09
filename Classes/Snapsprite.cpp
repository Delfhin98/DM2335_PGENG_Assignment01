#include "SnapSprite.h"
#include <cocos2d.h>
//using namespace std;
//using cocos2d namespace;
USING_NS_CC;

Scene* OHsnap::createScene()
{
	auto scene = Scene::create();
	auto layer = OHsnap::create();
	scene->addChild(layer);

	return scene;
}

bool OHsnap::init()
{

	if (!Layer::init())
	{
		return false;
	}
	onsprite = false;
	auto sprite1 = Sprite::create("strawberry.png");
	sprite1->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 3, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(sprite1, 0);

	//this is the image to snap to
	auto sprite2 = Sprite::create("strawberry.png");
	sprite2->setPosition(Vec2(Director::getInstance()->getVisibleSize().width*2 / 3, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(sprite2, 0);
	//image to click and drag

	//auto mypoint = Vec2(10.0f,10.0f);
	//add touch event
	//auto touchListener = EventListenerTouchOneByOne::create();
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(OHsnap::onTouchBegan, this);
	listener1->onTouchEnded = CC_CALLBACK_2(OHsnap::onTouch_Ended, this);
	listener1->onTouchMoved = CC_CALLBACK_2(OHsnap::onTouch_Moved, this);
	listener1->onTouchCancelled = CC_CALLBACK_2(OHsnap::onTouch_Cancelled, this);


	listener1->onTouchBegan = [](Touch* touch, Event*event)->bool {
		auto bounds = event->getCurrentTarget()->getBoundingBox();

		if (bounds.containsPoint(touch->getLocation())) {
			cocos2d::log("sprite clicked");

			cocos2d::log("makesprite move");
			return true;
			//do something to sprite
		}
		
	};
	// trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event) {
		
		cocos2d::log("moving1");
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		if (bounds.containsPoint(touch->getLocation())) {

			auto Touchpos = touch->getLocation();
			/*auto Imagepos = event->getCurrentTarget()->getPosition();
			auto offset = Touchpos - Imagepos;*/
			
			event->getCurrentTarget()->setPosition(Touchpos );
		}
		
	};
	// trigger when you let up
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		// your code
		cocos2d::log("end1");
		
		auto bounds2 = sprite2->getBoundingBox();
		if (bounds2.containsPoint(touch->getLocation())) {
			auto Imagepos2 = sprite2->getPosition();
			sprite1->setPosition(Imagepos2);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, sprite1);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, sprite2);





	return true;



	//  Create a "one by one" touch event listener
	// (processes one touch at a time)
	//auto listener1 = EventListenerTouchOneByOne::create();
	////auto touchListener = EventListenerTouchOneByOne::create();
	//listener1->onTouchBegan = CC_CALLBACK_2(OHsnap::onTouchBegan, this);
	//listener1->onTouchEnded = CC_CALLBACK_2(OHsnap::onTouch_Ended, this);
	//listener1->onTouchMoved = CC_CALLBACK_2(OHsnap::onTouch_Moved, this);
	//listener1->onTouchCancelled = CC_CALLBACK_2(OHsnap::onTouch_Cancelled, this);
	//// trigger when you push down
	//listener1->onTouchBegan = [](Touch* touch, Event* event) {
	//	// your code
	//	cocos2d::log("touch1");
	//	return true; // if you are consuming it
	//};
	//// trigger when moving touch
	//listener1->onTouchMoved = [](Touch* touch, Event* event) {
	//	// your code
	//	cocos2d::log("moving1");
	//	//ninja::onTouch_Moved(touch, event);
	//};
	//// trigger when you let up
	//listener1->onTouchEnded = [=](Touch* touch, Event* event) {
	//	// your code
	//	cocos2d::log("end1");
	//};
	//// Add listener
	////_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	////cocos2d::log("init went true");
	//std::string s = "my var";
	//cocos2d::log("string is %s", s);
	//return true;
}
//void OHsnap::modifySpriteposition(Touch*touch,Event * event)
//{ 
//	auto sprite = event->getCurrentTarget();
//	sprite->setPosition = touch->getLocation();
// }

// Update Every Frame
void OHsnap::update(float dt)
{
	//log("aaaaaaaaabbbbbss");
}

bool OHsnap::onTouch_Began(Touch* touch, Event* event)
{
	cocos2d::log("touch2");
	return true;
}
bool OHsnap::onTouch_Moved(Touch* touch, Event* event)
{
	cocos2d::log("moving2");
	return true;
}
bool OHsnap::onTouch_Ended(Touch* touch, Event* event)
{
	cocos2d::log("end2");
	return true;
}
void OHsnap::onTouch_Cancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled2");
}

