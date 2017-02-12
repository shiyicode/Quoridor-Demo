//
// Created by shiyi on 2017/1/19.
//

#ifndef ASIOSERVER_BEFORE_GAME_ACTION_H
#define ASIOSERVER_BEFORE_GAME_ACTION_H

#include "action.h"
#include <iostream>
#include "../factory.hpp"

class before_game_action : public action {
public:
    before_game_action()
    {
        std::cout<<"before_game_action"<<std::endl;
    }

    void doAction(Json::Value json, connection *conn)
    {
        std::cout<<"do_before_game_action"<<std::endl;
        std::cout<<json.toStyledString()<<std::endl;
    }
};

REGISTER_ACTION(before_game_action, "before_game");


#endif //ASIOSERVER_BEFORE_GAME_ACTION_H
