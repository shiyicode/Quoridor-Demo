//
//  ChoosePlayLayer.cpp
//  Quoridor
//
//  Created by shiyi on 2016/11/13.
//
//

#include "ChoosePlayLayer.h"
#include "SettingLayer.h"
#include "GameWithCmpLayer.h"
#include <json.h>
#include "client.h"

using namespace cocostudio::timeline;


bool ChoosePlayLayer::init()
{
    if( !Layer::init() )
        return false;
    
    audioEngine->playBackgroundMusic("sound/gameBGM.wav");
    
    auto rootNode = CSLoader::createNode("chooseLayer.csb");
    auto bgSprite = (Sprite*)rootNode->getChildByName("bgSprite");
    // bgSprite->setScale(0.5);
    bgSprite->removeFromParent();
    bgSprite->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
    addChild(bgSprite);
    
    for(int i=1; i<=8; i++)
    {
        Button* button = (Button*)bgSprite->getChildByTag(i);
        button->addTouchEventListener(CC_CALLBACK_2(ChoosePlayLayer::touchButton, this));
    }
    
    return true;
}

void ChoosePlayLayer::touchButton(cocos2d::Ref *object, ui::Widget::TouchEventType touchType)
{
    if(touchType == Widget::TouchEventType::ENDED)
    {
        int tag = ((Node*)object)->getTag();
        log("touch %d", tag);

        switch(tag)
        {
            case 1:
            {
                Json::Value data;
                data["type"] = "before_game";
                data["value"] = "ordinary";
                client::get().write(data.toStyledString());
                
                exit(0);
                break;
            }
            case 2:
                showSetLayer();
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                startGameWhithCmp();
                break;
            case 8:
                break;
            default:
                break;
        }
    }
}

void ChoosePlayLayer::startGameWhithCmp()
{
    auto scene = GameWithCmpLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void ChoosePlayLayer::showSetLayer()
{
    RenderTexture* render = RenderTexture::create(WIDTH, HEIGHT);
    render->begin();
    this->getParent()->visit();
    render->end();
    
    auto scene = SettingLayer::createScene(render);
    Director::getInstance()->pushScene(scene);
}

Scene* ChoosePlayLayer::createScene()
{
    auto layer = ChoosePlayLayer::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    
    return scene;
}
