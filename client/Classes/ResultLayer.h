//
//  ResultLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/20.
//
//

#ifndef ResultLayer_H
#define ResultLayer_H

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

class ResultLayer : Layer
{
public:
    static bool _isStart;
    
    static Scene* createScene(RenderTexture* render, int type, std::string name, int level, int score, Texture2D* head);
    bool init();
    CREATE_FUNC(ResultLayer);
    void touchButton(cocos2d::Ref *object, ui::Widget::TouchEventType touchType);
        
private:
    
    static int _type;
    static std::string _name;
    static int _level;
    static int _score;
    static Texture2D* _head;

};

#endif /* ResultLayer_H */
