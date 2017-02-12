//
// Created by shiyi on 2017/1/1.
//

#ifndef ASIOSERVER_LOGIN_ACTION_H
#define ASIOSERVER_LOGIN_ACTION_H

#include "action.h"
#include <iostream>
#include "../factory.hpp"

class login_action : public action {
public:
    login_action()
    {
        std::cout<<"login_action"<<std::endl;
    }

    void doAction(Json::Value json, connection *conn)
    {
        std::cout<<"do_login_action"<<std::endl;

        Json::Value data;
        data["type"] = "login";

        std::string user = json["user"].asString();
        std::string pass = json["pass"].asString();

        if(pass == "shiyi")
            data["result"] = "true";
        else
            data["result"] = "false";

        message msg;
        msg.init(data.toStyledString());
        conn->add_write_message(msg);
    }
};

REGISTER_ACTION(login_action, "login");


#endif //ASIOSERVER_LOGIN_ACTION_H
