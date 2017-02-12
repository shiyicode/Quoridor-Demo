//
// Created by shiyi on 2017/1/1.
//

#ifndef ASIOSERVER_REGISTER_H
#define ASIOSERVER_REGISTER_H

#include "action.h"
#include <iostream>
#include "../factory.hpp"

class register_action : public action
{
public:
    register_action()
    {
        std::cout<<"register_action"<<std::endl;
    }

    void doAction(Json::Value json, connection *conn)
    {
        std::cout<<"do_register_action"<<std::endl;
    }
};

REGISTER_ACTION(register_action, "register");

#endif //ASIOSERVER_REGISTER_H
