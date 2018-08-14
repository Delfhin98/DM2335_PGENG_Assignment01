#ifndef _SCENE_FREE_MODE_H_
#define _SCENE_FREE_MODE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CookingAnimation.h"
#include "Recipe_Database.h"
using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
private:
	CookingAnimation* cookingAnim;
	RecipeDatabase* rd;
	Size visibleSize;
	Vec2 origin;
	MenuItemImage* Kitchen_ChoppingBoard;
	MenuItemImage* Popup_ChoppingBoard;
	Label* Label_ChoppingBoard_Counter;
	string SelectedIngredient;
	int iCuts;
	bool isBoardInUse;
	bool isBoardFull;

	// TESTING FOR GRABBING INGREDIENT
	std::vector<Sprite*> ingredientContainer;

	// Showing Recipe on Gamescene
	std::vector <std::pair<const char*, Sprite*>> objectContainer;
	std::vector <string> choppingBoardSpriteNames;
	
	Sprite* mainItem;
	string recipeDetailsText;
	Label* recipeDetailsLabel;
	bool isPopUpOpen;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeScene(float time, cocos2d::Scene *scene);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	
	// Update Every Frame
	virtual void update(float);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void CuttingBoardEvent(Ref *pSender);
	void PopupChoppingBoardEvent(Ref *pSender);

	// Touch for Button Type
	void onButtonPressed(Ref* sender, ui::Widget::TouchEventType eventType);

	//------------
    CREATE_FUNC(GameScene);
};

#endif // _MAINMENU_SCENE_H_
