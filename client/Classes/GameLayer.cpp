//
//  GameLayer.cpp
//  Quoridor
//
//  Created by shiyi on 2016/11/15.
//
//

#include "GameLayer.h"
#include "SettingLayer.h"
#include "GlobalDefine.h"
#include "ResultLayer.h"
#include "ChoosePlayLayer.h"

Scene* GameLayer::createScene()
{
    Layer* layer = GameLayer::create();
    Scene* scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if( !Layer::init() )
        return false;
    
    memset(_board, 0, sizeof(_board));
    memset(_wall, 0, sizeof(_wall));
    
    auto rootNode = CSLoader::createNode("gameLayer.csb");
    _bgSprite = (Sprite*)rootNode->getChildByName("bgSprite");
    _bgSprite->removeFromParent();
    this->addChild(_bgSprite);
    
    //给菜单按钮增加回调
    _menu = (CheckBox*)_bgSprite->getChildByName("menu");
    _menu->addEventListener(CC_CALLBACK_2(GameLayer::touchMenu, this));

    _map = (Sprite*)_bgSprite->getChildByName("map");
    _redBG = (Sprite*)_bgSprite->getChildByName("redBG");
    
    _hbarSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/hbar.png"));
    _vbarSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/vbar.png"));
    
    _map->addChild(_hbarSprite, 2);
    _map->addChild(_vbarSprite, 2);
    _hbarSprite->setVisible(false);
    _vbarSprite->setVisible(false);
    
    //给设置按钮，退出按钮，准备按钮增加回调
    for(int i=101; i<=103; i++)
    {
        Button* button = (Button*)_bgSprite->getChildByTag(i);
        button->addTouchEventListener(CC_CALLBACK_2(GameLayer::touchButton, this));
    }
    
    for(int i=200; i<=203; i++)
    {
        Button* button = (Button*)_bgSprite->getChildByTag(i);
        button->addTouchEventListener(CC_CALLBACK_2(GameLayer::touchButton, this));
    }
    
    //给菜单子按钮增加回调
    for(int i=1; i<=4; i++)
    {
        Button* button = (Button*)_menu->getChildByTag(i);
        button->addTouchEventListener(CC_CALLBACK_2(GameLayer::touchButton, this));
    }
    
    
    _vbarButton = (Button*)_bgSprite->getChildByName("vbar");
    _hbarButton = (Button*)_bgSprite->getChildByName("hbar");
    
    _hbarButton->setContentSize(Size(_hbarButton->getContentSize().width+20, _hbarButton->getContentSize().height));
    
    //设置棋盘触屏监听
    _blackListen = EventListenerTouchOneByOne::create();
    _blackListen->onTouchBegan = [this](Touch* touch, Event* event){
        
        auto pos = touch->getLocation();
        
        if(!_map->getBoundingBox().containsPoint(pos))
            return false;
        pos = _map->convertToNodeSpace(pos);
        float startX = UNIT*2;
        float startY = UNIT*2;
        float width = UNIT*5;
        int x = (pos.x+0.5*UNIT)/width;
        int y = (pos.y+0.5*UNIT)/width;
        
        if(this->isPoint(x, y))
        {
            _playerSpriteVt[0]->setPosition(startX+UNIT*5*x, startY+UNIT*5*y);
        }
        return true;
    };
    
    _blackListen->onTouchMoved = [this](Touch* touch, Event* event){
        auto pos = touch->getLocation();
        pos = _map->convertToNodeSpace(pos);
        
        float startX = UNIT*2;
        float startY = UNIT*2;
        float width = UNIT*5;
        int x = (pos.x+0.5*UNIT)/width;
        int y = (pos.y+0.5*UNIT)/width;
        
        if(this->isPoint(x, y))
        {
            _playerSpriteVt[0]->setPosition(startX+UNIT*5*x, startY+UNIT*5*y);
            
        }
    };
    
    _blackListen->onTouchEnded = [this](Touch* touch, Event* event){
        auto pos = touch->getLocation();
        pos = _map->convertToNodeSpace(pos);
        
        float startX = UNIT*2;
        float startY = UNIT*2;
        float width = UNIT*5;
        int x = (pos.x+0.5*UNIT)/width;
        int y = (pos.y+0.5*UNIT)/width;
        
        
        if(_posVt[0].x == x && _posVt[0].y == y)
        {
            log("show");
            auto moves = getMoves(_posVt[0]);
            for(auto move : moves)
            {
                auto t = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/whiteblock.png"));
                t->setPosition(startX+UNIT*5*move.x, startY+UNIT*5*move.y);
                _redBG->addChild(t);
            }
        }
        else if(this->checkMove(_posVt[0], Vec2(x, y)))
        {
            this->gotoMove(0, x, y);
            this->playerMoveEnd();
        }
        else
        {
            _playerSpriteVt[0]->setPosition(startX+UNIT*5*_posVt[0].x, startY+UNIT*5*_posVt[0].y);
        }
//        log("%d %d %d shortlength", (int)_posVt[0].x, (int)_posVt[0].y, this->getShortPath(_posVt[0], 0));
        
    };
        
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_blackListen, _map);

    
    //给墙增加监听
    _hbarListen = EventListenerTouchOneByOne::create();
    _hbarListen->onTouchBegan = [this](Touch* touch, Event* event){
       
        auto touchPos = touch->getLocation();
        auto buttonPos = _hbarButton->getPosition();
        float x = abs(touchPos.x-buttonPos.x);
        float y = abs(touchPos.y-buttonPos.y);
        if(x > 40 || y > 30)
        {
            return false;
        }
        float width = UNIT*5;
        _hbarSprite->setPosition(UNIT*4.5+3*width, UNIT*4.5-1*width);
        _hbarSprite->setColor(Color3B::BLACK);
        _hbarSprite->setVisible(true);
        
        return true;
    };
    _hbarListen->onTouchMoved = [this](Touch* touch, Event* event){
        float width = UNIT*5;
        Point nowPos = touch->getLocation();
        Point startPos = touch->getStartLocation();
        int x = (nowPos.x-startPos.x)/width + 3;
        int y = (nowPos.y-startPos.y)/width - 1;
        log("%d %d", x, y);
        
        if(isPoint(x, y))
        {
            _hbarSprite->setPosition(UNIT*4.5+x*width, UNIT*4.5+y*width);
        }
    };
    _hbarListen->onTouchEnded = [this](Touch* touch, Event* event){
        float width = UNIT*5;
        int x = (_hbarSprite->getPositionX()-UNIT*4.5)/width;
        int y = (_hbarSprite->getPositionY()-UNIT*4.5)/width;
        
        _hbarSprite->setVisible(false);
        log("%d h %d    %d", x, y, _wallNumVt[Players::ME]);
        
        if(_wallNumVt[Players::ME] > 0 && this->checkWall(0, x, y))
        {
            this->gotoWall(Players::ME, 0, x, y);
            this->playerMoveEnd();
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_hbarListen, _hbarButton);
    
    
    _vbarListen = EventListenerTouchOneByOne::create();
    _vbarListen->onTouchBegan = [this](Touch* touch, Event* event){
        
        auto touchPos = touch->getLocation();
        auto buttonPos = _vbarButton->getPosition();
        float x = abs(touchPos.x-buttonPos.x);
        float y = abs(touchPos.y-buttonPos.y);
        if(x > 15 || y > 30)
        {
            return false;
        }

        
        float width = UNIT*5;
        _vbarSprite->setPosition(UNIT*4.5+2*width, UNIT*4.5-1*width);
        _vbarSprite->setVisible(true);
        _vbarSprite->setColor(Color3B::BLACK);
        
        return true;
    };
    _vbarListen->onTouchMoved = [this](Touch* touch, Event* event){
        float width = UNIT*5;
        Point nowPos = touch->getLocation();
        Point startPos = touch->getStartLocation();
        int x = (nowPos.x-startPos.x)/width + 2;
        int y = (nowPos.y-startPos.y)/width - 1;
        
        if(isPoint(x, y))
        {
            _vbarSprite->setPosition(UNIT*4.5+x*width, UNIT*4.5+y*width);
        }
    };
    _vbarListen->onTouchEnded = [this](Touch* touch, Event* event){
        float width = UNIT*5;
        int x = (_vbarSprite->getPositionX()-UNIT*4.5)/width;
        int y = (_vbarSprite->getPositionY()-UNIT*4.5)/width;
        
        _vbarSprite->setVisible(false);
        log("%d v %d   %d", x, y, _wallNumVt[Players::ME]);
        
        if(_wallNumVt[Players::ME] > 0 && this->checkWall(1, x, y))
        {
            this->gotoWall(Players::ME, 1, x, y);
            this->playerMoveEnd();
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_vbarListen, _vbarButton);
    
    stopListen();
    
    return true;
}

void GameLayer::startListen()
{
    //启动
    _blackListen->setEnabled(true);
    _hbarListen->setEnabled(true);
    _vbarListen->setEnabled(true);
}

void GameLayer::stopListen()
{
    //停止触屏事件
    _blackListen->setEnabled(false);
    _hbarListen->setEnabled(false);
    _vbarListen->setEnabled(false);
}

bool GameLayer::gotoMove(int playerId, int x, int y)
{
    float startX = UNIT*2;
    float startY = UNIT*2;
    
    _playerSpriteVt[playerId]->setPosition(startX+UNIT*5*x, startY+UNIT*5*y);
    _board[(int)_posVt[playerId].x][(int)_posVt[playerId].y] = false;
    _posVt[playerId] = Vec2(x, y);
    _board[(int)_posVt[playerId].x][(int)_posVt[playerId].y] = true;
    
    return true;
}

bool GameLayer::gotoWall(int playerId, int type, int x, int y)
{
    float width = UNIT*5;

    Sprite* temp;
    if(type == 0)
        temp = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/hbar.png"));
    else
        temp = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("image/vbar.png"));

    temp->setPosition(UNIT*4.5+x*width, UNIT*4.5+y*width);
    _map->addChild(temp, 0);
    
    _wall[type][x][y] = playerId + 1;
    log("%d %d %d -=-", type, x, y);
    _wallNumVt[playerId]--;
    
    return true;
}


//判断格子是否合法
bool GameLayer::isPoint(int x, int y)
{
    if(x >=0 && x < CHESSNUM
       && y >= 0 && y < CHESSNUM)
        return true;
    return false;
}

//判断墙是否合法
bool GameLayer::isWall(int x, int y)
{
    if(x >=0 && x < CHESSNUM-1
       && y >= 0 && y < CHESSNUM-1)
        return true;
    return false;
}

std::vector<std::pair<Vec2, int>> GameLayer::getWallMoves(int playerId)
{
    std::vector<std::pair<Vec2, int>> result;
 
    if(_wallNumVt[playerId] <= 0)
        return result;
    
    for(int type = 0; type <= 1; type++)
    {
        for(int i=0; i<CHESSNUM-1; i++)
        {
            for(int j=0; j<CHESSNUM-1; j++)
            {
                if(checkWall(type, i, j))
                    result.push_back(std::make_pair(Vec2(i, j), type));
            }
        }
    }
    return result;
}

//获取可走位置
std::vector<Vec2> GameLayer::getMoves(Vec2 from)
{
    std::vector<Vec2> moves;
    int x = from.x;
    int y = from.y;

    //0, 1
    if((!isWall(x, y) || _wall[0][x][y] == 0)
       && (!isWall(x-1, y) || _wall[0][x-1][y] == 0))
    {
        if(isPoint(x, y+1) && !_board[x][y+1])
            moves.push_back(Vec2(x, y+1));
        else
        {
            //0, 2
            if(isPoint(x, y+2) && !_board[x][y+2]
               && (!isWall(x, y+1) || _wall[0][x][y+1] == 0)
               && (!isWall(x-1, y+1) || _wall[0][x-1][y+1] == 0))
                moves.push_back(Vec2(x, y+2));
        }
    }
    //-1, 0
    if((!isWall(x-1, y) || _wall[1][x-1][y] == 0)
       && (!isWall(x-1, y-1) || _wall[1][x-1][y-1] == 0))
    {
        if(isPoint(x-1, y) && !_board[x-1][y])
            moves.push_back(Vec2(x-1, y));
        else
        {
            //-2, 0
            if(isPoint(x-2, y) && !_board[x-2][y]
               && (!isWall(x-2, y) || _wall[1][x-2][y] == 0)
               && (!isWall(x-2, y-1) || _wall[1][x-2][y-1] == 0))
                moves.push_back(Vec2(x-2, y));
        }
    }
    //1, 0
    if((!isWall(x, y) || _wall[1][x][y] == 0)
       && (!isWall(x, y-1) || _wall[1][x][y-1] == 0))
    {
        if(isPoint(x+1, y) && !_board[x+1][y])
            moves.push_back(Vec2(x+1, y));
        else
        {
            //2, 0
            if(isPoint(x+2, y) && !_board[x+2][y]
               && (!isWall(x+1, y) || _wall[1][x+1][y] == 0)
               && (!isWall(x+1, y-1) || _wall[1][x+1][y-1] == 0))
                moves.push_back(Vec2(x+2, y));
        }
    }
    //0, -1
    if((!isWall(x, y-1) || _wall[0][x][y-1] == 0)
       && (!isWall(x-1, y-1) || _wall[0][x-1][y-1] == 0))
    {
        if(isPoint(x, y-1) && !_board[x][y-1])
            moves.push_back(Vec2(x, y-1));
        else
        {
            //0, -2
            if(isPoint(x, y-2) && !_board[x][y-2]
               && (!isWall(x, y-2) || _wall[0][x][y-2] == 0)
               && (!isWall(x-1, y-2) || _wall[0][x-1][y-2] == 0))
                moves.push_back(Vec2(x, y-2));
        }
    }

   
    //0, 1
    if(isPoint(x, y+1) && _board[x][y+1]
       && (!isWall(x, y) || _wall[0][x][y] == 0)
       && (!isWall(x-1, y) || _wall[0][x-1][y] == 0)
       && (isWall(x, y+1) && _wall[0][x][y+1]
           || isWall(x-1, y+1) && _wall[0][x-1][y+1]
           || y+1 >= CHESSNUM-1))
    {
        //1, 1
        if(isPoint(x+1, y+1) && !_board[x+1][y+1]
           && (!isWall(x, y+1) || _wall[1][x][y+1] == 0)
           && (!isWall(x, y) || _wall[1][x][y] == 0))
            moves.push_back(Vec2(x+1, y+1));
        //-1, 1
        if(isPoint(x-1, y+1) && !_board[x-1][y+1]
           && (!isWall(x-1, y+1) || _wall[1][x-1][y+1] == 0)
           && (!isWall(x-1, y) || _wall[1][x-1][y] == 0))
            moves.push_back(Vec2(x-1, y+1));
    }
    if(isPoint(x+1, y) && _board[x+1][y]
       && (!isWall(x, y) || _wall[1][x][y] == 0)
       && (!isWall(x, y-1) || _wall[1][x][y-1] == 0)
       && (isWall(x+1, y) && _wall[1][x+1][y]
            || isWall(x+1, y-1) && _wall[1][x+1][y-1]
            || x+1 >= CHESSNUM-1))
    {
        //1, -1
        if(isPoint(x, y-1) && !_board[x][y-1]
           && (!isWall(x, y-1) || _wall[0][x][y-1] == 0)
           && (!isWall(x-1, y-1) || _wall[0][x-1][y-1] == 0))
            moves.push_back(Vec2(x+1, y-1));
        //1, 1
        if(isPoint(x+1, y+1) && !_board[x+1][y+1]
           && (!isWall(x+1, y) || _wall[1][x+1][y] == 0)
           && (!isWall(x, y) || _wall[1][x][y] == 0))
            moves.push_back(Vec2(x+1, y+1));
            
    }
    if(isPoint(x-1, y) && _board[x-1][y]
       && (!isWall(x-1, y) || _wall[1][x-1][y] == 0)
       && (!isWall(x-1, y-1) || _wall[1][x-1][y-1] == 0)
       && (isWall(x-2, y) && _wall[1][x-2][y]
           || isWall(x-2, y-1) && _wall[1][x-2][y-1]
           || x-2 < 0))
    {
        //-1, -1
        if(isPoint(x-1, y-1) && !_board[x-1][y-1]
           && (!isWall(x-1, y-1) || _wall[0][x-1][y-1] == 0)
           && (!isWall(x-2, y-1) || _wall[0][x-2][y-1] == 0))
            moves.push_back(Vec2(x-1, y-1));
        //-1, 1
        if(isPoint(x-1, y+1) && !_board[x-1][y+1]
           && (!isWall(x-1, y) || _wall[0][x-1][y] == 0)
           && (!isWall(x-2, y) || _wall[0][x-2][y] == 0))
            moves.push_back(Vec2(x-1, y+1));
    }
        
    //0, -1
    if(isPoint(x, y-1) && _board[x][y-1]
       && (!isWall(x, y-1) || _wall[0][x][y-1] == 0)
       && (!isWall(x-1, y-1) || _wall[0][x-1][y-1] == 0)
       && (isWall(x, y-2) && _wall[0][x][y-2]
           || isWall(x-1, y-2) && _wall[0][x-1][y-2]
           || y-2 < 0))
    {
        //1, -1
        if(isPoint(x+1, y-1) && !_board[x+1][y-1]
           && (!isWall(x, y-1) || _wall[1][x][y-1] == 0)
           && (!isWall(x, y-2) || _wall[1][x][y-2] == 0))
            moves.push_back(Vec2(x+1, y-1));
        //-1, -1
        if(isPoint(x-1, y-1) && !_board[x-1][y-1]
           && (!isWall(x-1, y-1) || _wall[1][x-1][y-1] == 0)
           && (!isWall(x-1, y-2) || _wall[1][x-1][y-2] == 0))
            moves.push_back(Vec2(x-1, y-1));
    }

    return moves;
}

//判断放墙是否合法
bool GameLayer::checkWall(int type, int x, int y)
{
    if(!isWall(x, y))
        return false;
    
    //横墙
    if(type == 0)
    {
        if((!isWall(x-1, y) || _wall[0][x-1][y] == 0)
            && (!isWall(x, y) || _wall[0][x][y] == 0)
            && (!isWall(x+1, y) || _wall[0][x+1][y] == 0)
           && _wall[1][x][y] == 0)
        {
            _wall[type][x][y] = 1;
            int a = getShortPath(_posVt[PLAYER_ONE], PLAYER_ONE);
            int b = getShortPath(_posVt[ME], ME);
            _wall[type][x][y] = 0;
            if(a != -1 && b != -1)
                return true;
        }
    }
    //竖墙
    else
    {
        if((!isWall(x, y-1) || _wall[1][x][y-1] == 0)
           && (!isWall(x, y) || _wall[1][x][y] == 0)
           && (!isWall(x, y+1) || _wall[1][x][y+1] == 0)
           && _wall[0][x][y] == 0)
        {
            _wall[type][x][y] = 1;
            int a = getShortPath(_posVt[PLAYER_ONE], PLAYER_ONE);
            int b = getShortPath(_posVt[ME], ME);
            _wall[type][x][y] = 0;
            if(a != -1 && b != -1)
                return true;
        }
    }
    return false;
}

bool GameLayer::checkMove(cocos2d::Vec2 from, cocos2d::Vec2 to)
{
    auto moves = getMoves(from);
    
    
    for(auto pos : moves)
    {
        if(to == pos)
            return true;
    }
    
    return false;
}

void GameLayer::toChooseLayer()
{
    
    auto scene = ChoosePlayLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));

}

void GameLayer::touchMenu(Ref* object, CheckBox::EventType type)
{
    if(type == CheckBox::EventType::SELECTED)
    {
        _menuItemId = 1;
        schedule(schedule_selector(GameLayer::menuUpdate), 0.04f, 3, 0);
    }
    else
    {
        _menuItemId = 4;
        schedule(schedule_selector(GameLayer::menuUpdate), 0.04f, 3, 0);
    }
}

void GameLayer::menuUpdate(float delay)
{
    Button* button = (Button*)_menu->getChildByTag(_menuItemId);
    if(_menu->isSelected())
    {
        _menuItemId++;
        button->setVisible(true);
    }
    else
    {
        _menuItemId--;
        button->setVisible(false);
    }
    
}

void GameLayer::setNameAndLevel(cocos2d::ui::Text *nameText, cocos2d::ui::Text *levelText, std::string name, int level)
{
    nameText->setString(name);
    levelText->setString(NUM[level]+"级");
}

void GameLayer::setHead()
{
    
}

//返回最短路线长度，-1表示无法走到终点
int GameLayer::getShortPath(Vec2 start, int playerId)
{
    bool flag[CHESSNUM][CHESSNUM];
    std::queue<std::pair<Vec2, int>> queue;
    
    memset(flag, 0, sizeof(flag));
    flag[(int)start.x][(int)start.y] = true;
    queue.push(std::make_pair(start, 0));
    
    while(!queue.empty())
    {
        auto now = queue.front();
        queue.pop();
        
        //log("%d %d", (int)now.first.x, (int)now.first.y);
        
        switch (playerId) {
            case Players::ME:
                if((int)now.first.y == CHESSNUM-1)
                    return now.second;
                break;
            case Players::PLAYER_ONE:
                if((int)now.first.y == 0)
                    return now.second;
                break;
            default:
                break;
        }
        
        
        auto tempPos = _posVt[PLAYER_ONE];
        _board[(int)tempPos.x][(int)tempPos.y] = false;
        
        _posVt[PLAYER_ONE] = now.first;
        _board[(int)now.first.x][(int)now.first.y] = true;
        
        auto moves = getMoves(now.first);
        
        _board[(int)now.first.x][(int)now.first.y] = false;
        _posVt[PLAYER_ONE] = tempPos;
        _board[(int)_posVt[PLAYER_ONE].x][(int)_posVt[PLAYER_ONE].y] = true;
        
//        log("-=-");
        
        for(auto move : moves)
        {
//            log("%d %d", (int)move.x,(int)move.y);
            
            if(!flag[(int)move.x][(int)move.y])
            {
                flag[(int)move.x][(int)move.y] = true;
                queue.push(std::make_pair(move, now.second+1));
            }
            
        }
//        log("-=-");

    }

    return -1;
}

//玩家走子后的操作
void GameLayer::playerMoveEnd()
{
    
}

//准备
void GameLayer::readyGame()
{
    log("ready");
}

//认输
void GameLayer::giveUp()
{

}

//聊天
void GameLayer::getChat()
{
    
}

//悔棋
void GameLayer::undoMove()
{
    
}

//求和
void GameLayer::sueForPeace()
{
    
}

//设置
void GameLayer::showSetLayer()
{
    RenderTexture* render = RenderTexture::create(WIDTH, HEIGHT);
    render->begin();
    this->getParent()->visit();
    render->end();
    
    auto scene = SettingLayer::createScene(render);
    Director::getInstance()->pushScene(scene);
}

//显示结果
void GameLayer::showResultLayer(int type, std::string name, int level, int score, cocos2d::Texture2D *head)
{
    RenderTexture* render = RenderTexture::create(WIDTH, HEIGHT);
    render->begin();
    _bgSprite->visit();
    render->end();
    
    Button* button = (Button*)_bgSprite->getChildByName("start");
    button->setVisible(false);
    
    auto scene = ResultLayer::createScene(render, type, name, level, score, head);
    Director::getInstance()->pushScene(scene);
}

void GameLayer::touchWall(Ref* object, ui::Widget::TouchEventType touchType)
{
    
    switch(touchType)
    {
        case Widget::TouchEventType::BEGAN:
        {
            
            break;
        }
        case Widget::TouchEventType::MOVED:
        {
            float width = UNIT*5;
            float startX = UNIT*2;
            float startY = UNIT*2;
            int x = (_hbarSprite->getPositionX()-startX)/width;
            int y = (_hbarSprite->getPositionY()-startY)/width;
            log("%d -=- %d", x, y);
            if(isPoint(x, y))
            {
                _hbarSprite->setPosition(UNIT*4.5+x*width, UNIT*4.5+y*width);
            }
                
            break;
        }
        case Widget::TouchEventType::ENDED:
        {
            break;
        }
    }
    
}


void GameLayer::touchButton(cocos2d::Ref *object, ui::Widget::TouchEventType touchType)
{
    if(touchType == Widget::TouchEventType::ENDED)
    {
        int tag = ((Node*)object)->getTag();
        log("touch %d", tag);
        
        switch(tag)
        {
            //菜单栏四项
            case 1:
                //悔棋
                undoMove();
                break;
            case 2:
                //求和
                sueForPeace();
                break;
            case 3:
                //认输
                giveUp();
                break;
            case 4:
                //聊天
                getChat();
                break;
            case 101:
                //设置
                showSetLayer();
                break;
            case 102:
                //退出
                toChooseLayer();
                break;
            case 103:
                //开始
                readyGame();
                break;
            case 200:
                //换桌
                break;
            case 201:
                //我的信息
                break;
            case 202:
                //双人时对方的信息
                break;
            case 203:
                //准备
                readyGame();
                break;
            case 401:
                //四人时对方信息
                break;
            case 402:
                //四人时对方信息
                break;
            case 403:
                //四人时对方信息
                break;
            default:
                break;
        }
    }
}
