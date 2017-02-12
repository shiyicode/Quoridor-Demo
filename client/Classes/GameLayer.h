//
//  GameLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/15.
//
//

#ifndef GameLayer_H
#define GameLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "GlobalDefine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GlobalDefine.h"
#include <vector>
#include <queue>

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

enum Players
{
    ME = 0,
    PLAYER_ONE,
    PLAYER_TWO,
    PLAYER_THREE
};

class GameLayer : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(GameLayer);

    //玩家人数
    int _playerCnt;
    //玩家坐标 自己在v[0]
    std::vector<Vec2> _posVt;
    //玩家所剩墙数
    std::vector<int> _wallNumVt;
    //保存棋盘墙 横竖 值为0表示空，
    int _wall[2][CHESSNUM][CHESSNUM];
    //判断格子是否有棋子
    bool _board[CHESSNUM][CHESSNUM];
    
    int _menuItemId;
    CheckBox* _menu;
    std::vector<Sprite*> _playerSpriteVt;
    Sprite* _bgSprite;
    Sprite* _hbarSprite;
    Sprite* _vbarSprite;
    Button* _hbarButton;
    Button* _vbarButton;
    Sprite* _map;
    Sprite* _redBG;
    EventListenerTouchOneByOne* _blackListen;
    EventListenerTouchOneByOne* _hbarListen;
    EventListenerTouchOneByOne* _vbarListen;
    
    void touchButton(Ref* object, ui::Widget::TouchEventType touchType);
    void touchMenu(Ref* object, CheckBox::EventType type);
    void menuUpdate(float delay);
    void touchWall(Ref* object, ui::Widget::TouchEventType touchType);
    
    bool gotoMove(int playerId, int x, int y);
    bool gotoWall(int playerId, int type, int x, int y);
    int getShortPath(Vec2 start, int playerId);
    
    //判断格子坐标是否合法
    bool isPoint(int x, int y);
    //判断墙坐标是否合法
    bool isWall(int x, int y);
    
    bool checkWall(int type, int x, int y);
    bool checkMove(Vec2 from, Vec2 to);
    std::vector<Vec2> getMoves(Vec2 from);
    std::vector<std::pair<Vec2, int>> getWallMoves(int playerId);
    
    void startListen();
    void stopListen();
    virtual void playerMoveEnd();
    virtual void showSetLayer();
    virtual void showResultLayer(int type, std::string name, int level, int score, cocos2d::Texture2D *head);
    virtual void toChooseLayer();
    virtual void readyGame();
    virtual void giveUp();
    virtual void sueForPeace();
    virtual void getChat();
    virtual void undoMove();

    virtual void setHead();
    virtual void setNameAndLevel(Text* nameText, Text* levelText, std::string name, int level);

};

#endif /* GameLayer_H */
