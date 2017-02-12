//
//  ChoosePlayLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/13.
//
//

#ifndef ChoosePlayLayer_H
#define ChoosePlayLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "GlobalDefine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class ChoosePlayLayer : public Layer
{
public:
    bool init();
    static Scene* createScene();
    CREATE_FUNC(ChoosePlayLayer);
    

private:
    void touchButton(Ref* object, ui::Widget::TouchEventType touchType);
    void showSetLayer();
    void startGameWhithCmp();
};

#endif /* ChoosePlayLayer_H */
