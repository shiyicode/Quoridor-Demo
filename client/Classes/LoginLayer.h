//
//  LoginLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/28.
//
//

#ifndef LoginLayer_H
#define LoginLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GlobalDefine.h"
#include "ui/UILayout.h"

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
USING_NS_CC;

class LoginLayer : Layer
{
public:
    
    static Scene* createScene();
    bool init();
    CREATE_FUNC(LoginLayer);
    void touchButton(cocos2d::Ref *object, ui::Widget::TouchEventType touchType);
    void textFieldEvent(Ref* ref, TextField::EventType event);
    void touchCheck(Ref* object, CheckBox::EventType type);
    void startGameWhithCmp();
    void doLogin();
private:

    CheckBox* _autoLogin;
    CheckBox* _keepMind;
    Button* _buttonUser;
    Button* _buttonPass;
    TextField* _pass;
    TextField* _user;
    
};

#endif /* LoginLayer_H */
