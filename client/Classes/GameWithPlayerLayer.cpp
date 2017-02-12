//
//  GameWithPlayerLayer.cpp
//  Quoridor
//
//  Created by shiyi on 2017/1/3.
//
//

#include "GameWithPlayerLayer.h"

#include <unistd.h>
#include <thread>
#include "ResultLayer.h"

Scene* GameWithPlayerLayer::createScene()
{
    Layer* layer = GameWithPlayerLayer::create();
    Scene* scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

bool GameWithPlayerLayer::init()
{
    if( !GameLayer::init() )
        return false;
    
    //设置头像 名字 等级
    _nameAndLevel = _bgSprite->getChildByName("nameAndLevel");
    setNameAndLevel((Text*)_nameAndLevel->getChildByName("name"), (Text*)_nameAndLevel->getChildByName("level"), "师妃暄", 1);
    
    _nameAndLevel1 = _bgSprite->getChildByName("nameAndLevel1");
    setNameAndLevel((Text*)_nameAndLevel1->getChildByName("name"), (Text*)_nameAndLevel1->getChildByName("level"), "师逍遥", 9);
    
    auto button = (Button*)_bgSprite->getChildByName("start");
    button->setVisible(true);
    
    auto head = _bgSprite->getChildByName("head");
    auto t = Sprite::createWithSpriteFrameName("local_robot_head_0.png");
    t->setPosition(head->getContentSize().width/2, t->getContentSize().height/2+2);
    head->addChild(t);
    
    auto head1 = _bgSprite->getChildByName("head1");
    auto t1 = Sprite::createWithSpriteFrameName("local_robot_head_2.png");
    t1->setPosition(head1->getContentSize().width/2, t1->getContentSize().height/2+2);
    head1->addChild(t1);
    
    _wait0 = (Sprite*)_bgSprite->getChildByName("wait");
    _wait1 = (Sprite*)_bgSprite->getChildByName("wait1");
    
    //设置等待动画
    auto scaleAction = ScaleBy::create(2, 0.6);
    auto scaleActionR = scaleAction->reverse();
    _waitAction = Sequence::create(scaleAction, scaleActionR ,NULL);
    _wait0->runAction(RepeatForever::create(_waitAction));
    _wait1->runAction(RepeatForever::create(_waitAction));
    _wait0->setVisible(false);
    _wait1->setVisible(false);
    
    Sprite* black = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/black.png"));
    Sprite* white = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/white.png"));
    
    //默认双人
    _map->addChild(black);
    _map->addChild(white);
    
    _playerSpriteVt.push_back(black);
    _playerSpriteVt.push_back(white);
    
    _playerCnt = 2;
    _posVt.push_back(Vec2(CHESSNUM/2, 0));
    _posVt.push_back(Vec2(CHESSNUM/2, CHESSNUM-1));
    
    _board[CHESSNUM/2][0] = true;
    _board[CHESSNUM/2][CHESSNUM-1] = true;
    
    gotoMove(0, CHESSNUM/2, 0);
    gotoMove(1, CHESSNUM/2, CHESSNUM-1);
    
    if(ResultLayer::_isStart)
        readyGame();
    
    //    _board[CHESSNUM/2][CHESSNUM/2] = true;
    //    gotoMove(1, CHESSNUM/2, 4);
    
    return true;
}

void GameWithPlayerLayer::readyGame()
{
    Button* button = (Button*)_bgSprite->getChildByName("start");
    button->setVisible(false);
    
    //开启求和
    button = (Button*)_menu->getChildByTag(2);
    button->setBright(true);
    button->setEnabled(true);
    //开启认输
    button = (Button*)_menu->getChildByTag(3);
    button->setBright(true);
    button->setEnabled(true);
    
    _wallNumVt.clear();
    _wallNumVt.push_back(10);
    _wallNumVt.push_back(10);
    
    memset(_board, 0, sizeof(_board));
    memset(_wall, 0, sizeof(_wall));
    
    _posVt[0] = Vec2(CHESSNUM/2, 0);
    _posVt[1] = Vec2(CHESSNUM/2, CHESSNUM-1);
    
    _board[CHESSNUM/2][0] = true;
    _board[CHESSNUM/2][CHESSNUM-1] = true;
    
    gotoMove(0, CHESSNUM/2, 0);
    gotoMove(1, CHESSNUM/2, CHESSNUM-1);
    
    startListen();
    
    this->schedule(schedule_selector(GameWithPlayerLayer::checkEnd), 0.1f);
    
    setState(0);
}

void GameWithPlayerLayer::sueForPeace()
{
    showResultLayer(1, "师妃暄", 1, 0, SpriteFrameCache::getInstance()->getSpriteFrameByName("local_robot_head_0.png")->getTexture());
}

void GameWithPlayerLayer::giveUp()
{
    showResultLayer(2, "师妃暄", 1, -10, SpriteFrameCache::getInstance()->getSpriteFrameByName("local_robot_head_0.png")->getTexture());
}

void GameWithPlayerLayer::playerMoveEnd()
{
    _redBG->removeAllChildrenWithCleanup(true);
    setState(PEOPLE_MOVE);
}

void GameWithPlayerLayer::peopleMove(std::pair<Vec2, int> move)
{
    stopListen();
    
    switch(move.second){
        case 2:
            gotoMove(PLAYER_ONE, move.first.x, move.first.y);
            break;
        case 0:
            gotoWall(PLAYER_ONE, 0, move.first.x, move.first.y);
            break;
        case 1:
            gotoWall(PLAYER_ONE, 1, move.first.x, move.first.y);
            break;
    }
    
    startListen();
    
    setState(GameState::PLAYER_MOVE);
}

void GameWithPlayerLayer::setState(int state)
{
    _state = state;
    changeState();
}

void GameWithPlayerLayer::checkEnd(float a)
{
//    if(_cmp_ai.isRuning)
//        return;
    
    Text* num = (Text*)_nameAndLevel->getChildByName("num");
    num->setString(StringUtils::format("【%d】", _wallNumVt[0]));
    //    log("%d", );
    Text* num1 = (Text*)_nameAndLevel1->getChildByName("num");
    num1->setString(StringUtils::format("【%d】", _wallNumVt[1]));
    
    if(_posVt[ME].y == CHESSNUM-1)
    {
        this->unschedule(schedule_selector(GameWithPlayerLayer::checkEnd));
        
        showResultLayer(0, "师妃暄", 1, +10, Sprite::createWithSpriteFrameName("local_robot_head_0.png")->getTexture());
        
    }
    else if(_posVt[PLAYER_ONE].y == 0)
    {
        showResultLayer(2, "师妃暄", 1, -10, Sprite::createWithSpriteFrameName("local_robot_head_0.png")->getTexture());
    }
}

void GameWithPlayerLayer::changeState()
{
    switch(_state)
    {
        case GameState::BEGIN:
            setState(GameState::PLAYER_MOVE);
            break;
        case GameState::PLAYER_MOVE:
        {
            //关闭所有等待指示灯 开启对方
            _wait1->setVisible(false);
            _wait0->setVisible(true);
            break;
        }
        case GameState::PEOPLE_MOVE:
        {
            _wait0->setVisible(false);
            _wait1->setVisible(true);
            break;
        }
        case GameState::END:
        {
            break;
        }
    }
}

