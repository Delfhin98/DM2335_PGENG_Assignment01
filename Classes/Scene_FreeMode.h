#ifndef _SCENE_FREE_MODE_H_
#define _SCENE_FREE_MODE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CookingAnimation.h"
#include "Recipe_Database.h"
using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
	CookingAnimation* cookingAnim;
	std::vector <std::pair<const char*, Sprite*>> objectContainer;
	Size visibleSize;
	Vec2 origin;
	MenuItemImage* Kitchen_ChoppingBoard;
	MenuItemImage* Popup_ChoppingBoard;
	Label* Label_ChoppingBoard_Counter;
	int iCuts;
	bool isBoardInUse;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeScene(float time, cocos2d::Scene *scene);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	//virtual bool InteractWSpices(cocos2d::Touch*, cocos2d::Event*);
	
	// Update Every Frame
	virtual void update(float);

	//Raph needs this for pop menu
	void openpop();
	void closepop();
	int popmenu;
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void CuttingBoardEvent(Ref *pSender);
	void PopupChoppingBoardEvent(Ref *pSender);
	void PopupIngredient(Ref *pSender);
	//void InteractWSpices(EventKeyboard::KeyCode keycode, Event * event);
	//string selected_method;
	//Label* text_methodtext;
	//int numOfRecipes;
	//void SetRecipeMethodText(string val);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // _MAINMENU_SCENE_H_
