//
//  main.cpp
//  AsioServer
//
//  Created by shiyi on 2016/12/10.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "server.h"
#include <string>
#include "action/login_action.h"
#include "action/register_action.h"
#include <map>

using namespace std;

//int main()
//{
//    action *login = factory::produce("login_action");
//    action *rter = factory::produce("register_action");
//    login->doAction();
//    rter->doAction();
//    delete(login);
//    delete(rter);
//}


int main(int argc, char* argv[])
{

    std::map<std::string, int> m;

    auto t = make_pair("asas", 23);
    m.insert(t);
    int a = m.erase("asas");
    int b = m.erase("fsf");

    cout<<a<<"  "<<b<<endl;

    std::string adress = "127.0.0.1";
    std::string port = "10089";
    int io_service_size = 2;

    server server(adress, port, io_service_size);
    server.run();

    cout<<"测试json写入"<<endl;
    Json::Value jsonRoot;
    Json::Value jsonItem;
    jsonItem["item1"] = "第一个条目";
    jsonItem["item2"] = "第二个条目";
    jsonItem["item3"] = 3;
    jsonRoot["sdsd"] = jsonItem;
//    jsonRoot.append(jsonItem);
    jsonItem.clear();//清除上面已经赋值的项
    jsonItem["First"]="1";
    jsonItem["Second"]=2;
    jsonItem["Third"]=3.0F;
    jsonRoot["aa"] = jsonItem;

//    jsonRoot.append(jsonItem);
    cout<<jsonRoot.toStyledString()<<endl;
    return 0;
}
