//
//  GameWithCmpLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/16.
//
//

#ifndef GameWithCmpLayer_H
#define GameWithCmpLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "GlobalDefine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameLayer.h"
#include "AI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

enum GameState
{
    BEGIN = 0,
    PLAYER_MOVE,
    CMP_MOVE,
    END
};

class GameWithCmpLayer : public GameLayer
{
public:
    bool init();
    static Scene* createScene();
    CREATE_FUNC(GameWithCmpLayer);

    void giveUp();
    void checkEnd(float a);
    void sueForPeace();
    void playerMoveEnd();
    void cmpMove();
    void setState(int state);
    void changeState();
    void readyGame();
private:
    //当前游戏状态
    int _state;
    AI _cmp_ai;
    Sprite* _wait0;
    Sprite* _wait1;
    Node* _nameAndLevel;
    Node* _nameAndLevel1;
    Sequence* _waitAction;

};


#endif /* GameWithCmpLayer_H */
