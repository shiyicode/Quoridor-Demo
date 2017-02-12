//
//  GameWithPlayerLayer.h
//  Quoridor
//
//  Created by shiyi on 2017/1/3.
//
//

#ifndef GameWithPlayerLayer_H
#define GameWithPlayerLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "GlobalDefine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

enum GameState
{
    BEGIN = 0,
    PLAYER_MOVE,
    PEOPLE_MOVE,
    END
};

class GameWithPlayerLayer : public GameLayer
{
public:
    bool init();
    static Scene* createScene();
    CREATE_FUNC(GameWithPlayerLayer);
    
    void giveUp();
    void checkEnd(float a);
    void sueForPeace();
    void playerMoveEnd();
    void peopleMove(std::pair<Vec2, int> move);
    void setState(int state);
    void changeState();
    void readyGame();
private:
    //当前游戏状态
    int _state;
    Sprite* _wait0;
    Sprite* _wait1;
    Node* _nameAndLevel;
    Node* _nameAndLevel1;
    Sequence* _waitAction;
    
};


#endif /* GameWithPlayerLayer_H */
