//
//  AI.h
//  Quoridor
//
//  Created by shiyi on 2016/11/19.
//
//

#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

struct MoveNode{
    MoveNode(){}
    MoveNode(int s, int type, Vec2 p){
        score = s;
        moveType = type;
        pos = p;
    }
    bool operator <(const MoveNode& t) const {return this->score < t.score;}
    int score;
    int moveType;
    Vec2 pos;
};

class AI
{
public:
    AI() = default;
    AI(int depth, int time, GameLayer* game);
    
    std::pair<Vec2, int> getNextMove();
    int alphaBeta(int depth, int depthSum, int alpha, int beta);
    int evaluate();
    long long getSystemTime();
    
    bool isRuning;
    int _depth;
    int _time;
    GameLayer* _game;
    
private:

};

#endif /* AI_H */
