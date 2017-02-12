//
//  client.h
//  AsioClient
//
//  Created by shiyi on 2016/12/28.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef client_H
#define client_H

#include <stdio.h>
#include <iostream>
#include <boost/asio.hpp>
#include "message.h"
#include <boost/noncopyable.hpp>
#include "cocos2d.h"

USING_NS_CC;

class client : protected boost::noncopyable
{
public:
   
    static client& get();
    
    ~client();
    
    void connect(const std::string& ip, const std::string& port);

    void write(std::string json);

    void now_layer(Layer* layer);
    
    Layer* now_layer();
    
    void now_layer_name(std::string name);
    
    std::string now_layer_name();
    
private:
    client();
    
    boost::asio::ip::tcp::socket& socket();
    
    void handle_connect(const boost::system::error_code& e);
    
    void handle_read();
    
    void read_body(const boost::system::error_code &e);
    
    void handle_work(const boost::system::error_code &e);
    
    void handle_write(const boost::system::error_code& e);
    
    void close();
    
    
    
    message m_read_message;
    
    message m_write_message;
    
    boost::asio::ip::tcp::socket m_socket;
    
    Layer* m_now_layer;
    
    std::string m_layer_name;
    
    boost::asio::io_service::work m_work;
};

#endif /* client_H */
