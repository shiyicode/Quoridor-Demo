//
// Created by shiyi on 2017/1/1.
//

#ifndef ASIOSERVER_ACTION_H
#define ASIOSERVER_ACTION_H


#include <iostream>
#include <json.h>
#include "../connection.h"

class action
{
public:
    action()
    {
        std::cout<<"action"<<std::endl;
    }

    virtual void doAction(Json::Value json, connection *conn)
    {
        std::cout<<"doAction"<<std::endl;
    }

};

#endif //ASIOSERVER_ACTION_H
