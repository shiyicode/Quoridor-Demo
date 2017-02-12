//
//  SettingLayer.cpp
//  Quoridor
//
//  Created by shiyi on 2016/11/10.
//
//

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SettingLayer.h"
#include "GlobalDefine.h"
#include "ui/UILayout.h"

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

bool SettingLayer::init()
{
    if( !Layer::init() )
        return false;
    
    auto rootNode = CSLoader::createNode("settingLayer.csb");
    auto bgSprite = (Sprite*)rootNode->getChildByName("bgSprite");

    bgSprite->removeFromParent();
    bgSprite->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
    addChild(bgSprite, 1);

    _musicSlider = (Slider*)bgSprite->getChildByName("musicSlider");
    _effectSlider = (Slider*)bgSprite->getChildByName("effectSlider");
    float musicVol = getFloatFromXML(MUSICVOL);
    float effectVol = getFloatFromXML(EFFECTVOL);
    _musicSlider->setPercent(musicVol*100);
    _effectSlider->setPercent(effectVol*100);
    _musicSlider->addEventListener(CC_CALLBACK_2(SettingLayer::touchMusicSlider, this));
    _effectSlider->addEventListener(CC_CALLBACK_2(SettingLayer::touchEffectSlider, this));
    
    Sprite* t = (Sprite*)bgSprite->getChildByName("soundKey");
    auto pos1 = t->getPosition();
    bgSprite->removeChild(t, true);

    t = (Sprite*)bgSprite->getChildByName("shockKey");
    auto pos2 = t->getPosition();
    bgSprite->removeChild(t, true);
    
    _soundNode = createOnOffNode(getBoolFromXML(SOUNDKEY));
    _soundNode->setPosition(pos1);
    _soundNode->setTag(1);
    bgSprite->addChild(_soundNode);

    
    _shockNode = createOnOffNode(getBoolFromXML(SHOCKKEY));
    _shockNode->setPosition(pos2);
    _shockNode->setTag(2);
    bgSprite->addChild(_shockNode);

    //创建开关回调函数
    _soundListener = EventListenerTouchOneByOne::create();
    _soundListener->onTouchBegan = [=](Touch* touch, Event* event){

        Node* node = event->getCurrentTarget();
        Point pos = touch->getLocation();
        
        Size psize = node->getParent()->getContentSize();
        Size nsize = node->getContentSize();
        int x = ORIGIN.x + VISIBLESIZE.width/2 - psize.width/2
        + node->getPositionX() - nsize.width/2;
        int y = ORIGIN.y + VISIBLESIZE.height/2 - psize.height/2
        + node->getPositionY() - nsize.height/2;

        Rect rect = Rect(x, y, nsize.width, nsize.height);

        //如果不在范围则吞没事件
        if(!rect.containsPoint(pos))
        {
            return false;
        }

        Sprite* button = (Sprite*)node->getChildByName("onOffNode")->getChildByName("button");
        button->setColor(Color3B::GRAY);
        
        
        return true;
    };
    
    _soundListener->onTouchMoved = [=](Touch* touch, Event* event){
        ClippingNode* cnode = (ClippingNode*)event->getCurrentTarget();
        Node* onOffSet = cnode->getChildByName("onOffNode");
        
        Point pos = touch->getLocation();
        
        //获取当前位置
        float onOffPosX = onOffSet->getPositionX();
        //增加偏移量
        onOffPosX += pos.x - touch->getPreviousLocation().x;
        
        if(onOffPosX < _left + _buttonSize.width/2)
            onOffPosX = _left + _buttonSize.width/2;
        else if(onOffPosX > _right - _buttonSize.width/2)
            onOffPosX = _right - _buttonSize.width/2;

        onOffSet->setPositionX(onOffPosX);
    };
    
    _soundListener->onTouchEnded = [=](Touch* touch, Event* event){
        
        ClippingNode* cnode = (ClippingNode*)event->getCurrentTarget();
        Node* onOffSet = cnode->getChildByName("onOffNode");
        
        float x = onOffSet->getPositionX();

        if(x < 0)
        {
            x = _left + _buttonSize.width/2;
            this->offKey(cnode->getTag());
        }
        else if(x > 0)
        {
            x = _right - _buttonSize.width/2;
            this->onKey(cnode->getTag());
        }
        MoveTo* move = MoveTo::create(0.1f, Vec2(x, 0));
        onOffSet->runAction(move);
    
        Sprite* button = (Sprite*)cnode->getChildByName("onOffNode")->getChildByName("button");
        button->setColor(_buttonColor);
    };
    
    _shockListener = _soundListener->clone();
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_soundListener, _soundNode);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_shockListener, _shockNode);

    EventListenerTouchOneByOne* touchAway = EventListenerTouchOneByOne::create();
    touchAway->onTouchBegan = [this](Touch* touch, Event* event){
        auto cnode = event->getCurrentTarget();
        Rect rect = cnode->getBoundingBox();

        if(!rect.containsPoint(touch->getLocation()))
        {
            Director::getInstance()->popScene();
        }
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchAway, bgSprite);
    
    return true;
}

Node* SettingLayer::createOnOffNode(bool isOn)
{
    auto onOffNode = CSLoader::createNode("onOffNode.csb");
    auto maskSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/Setting_mask.png"));
    
    Sprite* button = (Sprite*)onOffNode->getChildByName("button");
    _buttonColor = button->getColor();
    
    //给组件设置大小(因为node没有大小)
    _buttonSize = button->getContentSize();
    _left = maskSprite->getPositionX() - maskSprite->getContentSize().width/2;
    _right = maskSprite->getPositionX() + maskSprite->getContentSize().width/2;
    
    onOffNode->setContentSize(Size(_right-_left, _buttonSize.height));


    if(isOn)
    {
        onOffNode->setPositionX(_right - _buttonSize.width/2);
    }
    else
    {
        onOffNode->setPositionX(_left + _buttonSize.width/2);
    }
    
    //设置遮罩
    auto m_clip = ClippingNode::create();
    m_clip->addChild(onOffNode);
    m_clip->setStencil(maskSprite);
    m_clip->setAlphaThreshold(0.5);
    m_clip->setInverted(false);
    
    m_clip->setContentSize(Size(_right-_left, _buttonSize.height));
    m_clip->setAnchorPoint(Vec2(0, 0));

    return m_clip;
}

void SettingLayer::touchMusicSlider(cocos2d::Ref * ref, cocos2d::ui::Slider::EventType type)
{
    if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        int num = ((Slider*)ref)->getPercent();
        changeMusicVol(num*0.01);
    }
}

void SettingLayer::touchEffectSlider(cocos2d::Ref * ref, cocos2d::ui::Slider::EventType type)
{
    if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        int num = ((Slider*)ref)->getPercent();
        changeEffectVol(num*0.01);
    }
}


void SettingLayer::onKey(int tag)
{
    switch(tag)
    {
        case 1:
        {
            changeSoundKey(true);
            _effectSlider->setPercent(0);
            _musicSlider->setPercent(0);
            audioEngine->setEffectsVolume(0);
            audioEngine->setBackgroundMusicVolume(0);
            break;
        }
        case 2:
            changeShockKey(true);
            break;
        default:
            break;
    }
}

void SettingLayer::offKey(int tag)
{
    switch(tag)
    {
        case 1:
        {
            changeSoundKey(false);
            float music = getFloatFromXML(MUSICVOL);
            float effect = getFloatFromXML(EFFECTVOL);
            changeMusicVol(music);
            changeEffectVol(effect);
            _musicSlider->setPercent(music*100);
            _effectSlider->setPercent(effect*100);
            break;
        }
        case 2:
            changeShockKey(false);
            break;
        default:
            break;
    }
}

void SettingLayer::changeSoundKey(bool isOn)
{
    log("%f %f ", _right - _buttonSize.width/2, _left + _buttonSize.width/2);
    if(isOn)
        _soundNode->getChildByName("onOffNode")->setPositionX(_right - _buttonSize.width/2);
    else
        _soundNode->getChildByName("onOffNode")->setPositionX(_left + _buttonSize.width/2);
    setBoolToXML(SOUNDKEY, isOn);
    UserDefault::getInstance()->flush();
}

void SettingLayer::changeShockKey(bool isOn)
{
    if(isOn)
        _shockNode->getChildByName("onOffNode")->setPositionX(_right - _buttonSize.width/2);
    else
        _shockNode->getChildByName("onOffNode")->setPositionX(_left + _buttonSize.width/2);
    
    setBoolToXML(SHOCKKEY, isOn);
    UserDefault::getInstance()->flush();
}

void SettingLayer::changeEffectVol(float vol)
{
    if(getFloatFromXML(SOUNDKEY))
    {
        changeSoundKey(false);
    }
    audioEngine->setEffectsVolume(vol);
    setFloatToXML(EFFECTVOL, vol);
    UserDefault::getInstance()->flush();
}

void SettingLayer::changeMusicVol(float vol)
{
    if(getFloatFromXML(SOUNDKEY))
    {
        changeSoundKey(false);
    }
    audioEngine->setBackgroundMusicVolume(vol);
    setFloatToXML(MUSICVOL, vol);
    UserDefault::getInstance()->flush();
}

Scene* SettingLayer::createScene(RenderTexture* render)
{
    Sprite* bg = Sprite::createWithTexture(render->getSprite()->getTexture());
    bg->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
    bg->setFlippedY(true);
    bg->setColor(Color3B(100, 100, 100));
    
    auto layer = SettingLayer::create();
    layer->addChild(bg, 0);
    auto scene = Scene::create();
    scene->addChild(layer);
    
    return scene;
}

