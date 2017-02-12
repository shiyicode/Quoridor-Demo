//
//  SettingLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/10.
//
//

#ifndef SettingLayer_H
#define SettingLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class SettingLayer : public Layer
{
public:
    bool init();
    static Scene* createScene(RenderTexture* render);
    CREATE_FUNC(SettingLayer);

    void touchMusicSlider(cocos2d::Ref * ref, cocos2d::ui::Slider::EventType type);
    void touchEffectSlider(cocos2d::Ref * ref, cocos2d::ui::Slider::EventType type);
    
    void onKey(int tag);
    void offKey(int tag);
    void changeSoundKey(bool isOn);
    void changeShockKey(bool isOn);
    void changeEffectVol(float vol);
    void changeMusicVol(float vol);
    
private:
    float _left;
    float _right;
    Node* _soundNode;
    Node* _shockNode;
    cocos2d::ui::Slider* _musicSlider;
    cocos2d::ui::Slider* _effectSlider;
    //创建一个开关组件
    Node* createOnOffNode(bool isOn);
    Color3B _buttonColor;
    Size _buttonSize;
    EventListenerTouchOneByOne* _soundListener;
    EventListenerTouchOneByOne* _shockListener;
};

#endif /* SettingLayer_H */
