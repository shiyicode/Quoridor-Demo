//
//  AI.cpp
//  Quoridor
//
//  Created by shiyi on 2016/11/19.
//
//

#include "AI.h"
#include <sys/timeb.h>
#include <algorithm>

AI::AI(int depth, int time, GameLayer* game)
{
    _depth = depth;
    _time = time;
    _game = game;
    isRuning = false;
}

std::pair<Vec2, int> AI::getNextMove()
{
    isRuning = true;
    int startTime = getSystemTime();
    
    std::vector<MoveNode> moveVt;
    
    std::vector<Vec2> moves = _game->getMoves(_game->_posVt[Players::PLAYER_ONE]);
    std::vector<std::pair<Vec2, int>> wallMoves = _game->getWallMoves(PLAYER_ONE);

    log("%d %d", moves.size(), wallMoves.size());
    
    for(auto move : moves)
    {
        //2表示落子
        moveVt.push_back(MoveNode(0, 2, move));
    }

    
    for(auto wallMove : wallMoves)
    {
        moveVt.push_back(MoveNode(0, wallMove.second, wallMove.first));
    }
    
    auto size = moveVt.size();
    MoveNode ans;
    
    for(int i_depth=1; i_depth<=_depth; i_depth++)
    {
        int timeLen = getSystemTime() - startTime;

        if(timeLen >= _time)
        {
            log("%fs %d层", timeLen/1000.0, i_depth);
            break;
        }
        int val;
        int alpha = -1000000;
        int beta = 1000000;
        MoveNode moveNode;
        
        for(auto i = 0; i < size; i++)
        {
            int x = moveVt[i].pos.x;
            int y = moveVt[i].pos.y;
            
            if(moveVt[i].moveType == 2)
            {
                auto tempPos = _game->_posVt[PLAYER_ONE];
                _game->_board[(int)tempPos.x][(int)tempPos.y] = false;
                
                _game->_posVt[PLAYER_ONE] = Vec2(x, y);
                _game->_board[x][y] = true;
                
                val = -alphaBeta(i_depth, ME, -beta, -alpha);
                
                _game->_board[x][y] = false;
                _game->_posVt[PLAYER_ONE] = tempPos;
                _game->_board[(int)_game->_posVt[PLAYER_ONE].x][(int)_game->_posVt[PLAYER_ONE].y] = true;
            }
            else
            {
                _game->_wall[moveVt[i].moveType][x][y] = PLAYER_ONE + 1;
                val = -alphaBeta(i_depth, ME, -beta, -alpha);
                
                _game->_wall[moveVt[i].moveType][x][y] = 0;
            }
            
            if(val > alpha)
            {
                moveNode = moveVt[i];
                alpha = val;
            }
            moveVt[i].score = alpha;
        }
        
        ans = moveNode;
        log("val %d  move type=%d x=%d y=%d", val, ans.moveType, (int)ans.pos.x, (int)ans.pos.y);

        std::sort(moveVt.begin(), moveVt.end());
    }

    isRuning = false;
    
    return std::make_pair(ans.pos, ans.moveType);
}

int AI::alphaBeta(int depth, int playerId, int alpha, int beta)
{
    if(depth == 0)
    {
        int score = evaluate();
        if(playerId == 0)
            score = -score;
            
        return score;
    }
    
    std::vector<Vec2> moves = _game->getMoves(_game->_posVt[playerId]);
    
    int val;
    
    for(auto move : moves)
    {
        Vec2 tpos = _game->_posVt[playerId];
        _game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = false;
        
        _game->_posVt[playerId] = move;
        _game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = true;

        val = -alphaBeta(depth-1, 1-playerId, -beta, -alpha);
      
        _game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = false;
        
        _game->_posVt[playerId] = tpos;
        _game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = true;
        
        if(val >= beta)
            return beta;
        if(val > alpha)
            alpha = val;
    }
    
    std::vector<std::pair<Vec2, int>> wallMoves = _game->getWallMoves(playerId);
    
    for(auto wallMove : wallMoves)
    {
        _game->_wall[wallMove.second][(int)wallMove.first.x][(int)wallMove.first.y] = playerId + 1;
        
        val = -alphaBeta(depth-1, 1-playerId, -beta, -alpha);
        
        _game->_wall[wallMove.second][(int)wallMove.first.x][(int)wallMove.first.y] = 0;
        
        if(val >= beta)
            return beta;
        if(val > alpha)
            alpha = val;
    }
    
    return alpha;
}

int AI::evaluate()
{
    int cmpShortLength = _game->getShortPath(_game->_posVt[PLAYER_ONE], PLAYER_ONE);
    int meShortLength = _game->getShortPath(_game->_posVt[ME], ME);
    int cmpWallNum = _game->_wallNumVt[PLAYER_ONE];
    int meWallNum = _game->_wallNumVt[ME];
    
    if(cmpShortLength == 0)
        return 200;
    
    if(meShortLength == 0)
        return 0;
    
    int score = 100-cmpShortLength+meShortLength+1*cmpWallNum-1*meWallNum;

//    int score = 100 - cmpShortLength;
    return score;
}

long long AI::getSystemTime()
{
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}
