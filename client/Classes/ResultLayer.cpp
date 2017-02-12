//
//  ResultLayer.cpp
//  Quoridor
//
//  Created by shiyi on 2016/11/20.
//
//

#include "ResultLayer.h"
#include "GlobalDefine.h"
#include "GameWithCmpLayer.h"
#include "ChoosePlayLayer.h"

Texture2D* ResultLayer::_head;
std::string ResultLayer::_name;
int ResultLayer::_score;
int ResultLayer::_level;
int ResultLayer::_type;
bool ResultLayer::_isStart;

Scene* ResultLayer::createScene(RenderTexture* render, int type, std::string name, int level, int score, Texture2D* head)
{
    _type = type;
    _name = name;
    _level = level;
    _score = score;
    _head = head;
    
    Sprite* bg = Sprite::createWithTexture(render->getSprite()->getTexture());
    bg->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
    bg->setFlippedY(true);
    bg->setColor(Color3B(100, 100, 100));
    
    auto layer = ResultLayer::create();
    layer->addChild(bg, 0);
    auto scene = Scene::create();
    scene->addChild(layer);
    
    return scene;

}

bool ResultLayer::init()
{
    if( !Layer::init() )
        return false;
    
    std::string loadingName;
    if(ResultLayer::_type == 0)
        loadingName = "w";
    else if(ResultLayer::_type == 1)
        loadingName = "p";
    else
        loadingName = "l";
    loadingName += "ResultLayer.csb";

    auto rootNode = CSLoader::createNode(loadingName);
    auto bgSprite = (Sprite*)rootNode->getChildByName("bgSprite");
    
    bgSprite->removeFromParent();
    bgSprite->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
    addChild(bgSprite, 1);
    
    Button* head = (Button*)bgSprite->getChildByName("head");
    Text* name = (Text*)bgSprite->getChildByName("name");
    Text* level = (Text*)bgSprite->getChildByName("level");
    Text* num = (Text*)bgSprite->getChildByName("score")->getChildByName("num");
    
    name->setString(_name);
    std::string s = NUM[_level] + "级";
    level->setString(s);
    num->setString(StringUtils::format("%d", _score));
    
//    auto t = Sprite::createWithTexture(_head);
//    t->setPosition(head->getContentSize().width/2, t->getContentSize().height/2+2);
//    head->addChild(t);
    
    Button* button = (Button*)bgSprite->getChildByName("continue");
    button->addTouchEventListener(CC_CALLBACK_2(ResultLayer::touchButton, this));

    auto listen = EventListenerTouchOneByOne::create();
    
    listen->onTouchBegan = [bgSprite](Touch* touch, Event* event){

        if(!bgSprite->getBoundingBox().containsPoint(touch->getLocation()))
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, ChoosePlayLayer::createScene()));
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, bgSprite);
    
    return true;
}

void ResultLayer::touchButton(cocos2d::Ref *object, ui::Widget::TouchEventType touchType)
{
    if(touchType == Widget::TouchEventType::ENDED)
    {
        _isStart = true;
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameWithCmpLayer::createScene()));
    }
}
