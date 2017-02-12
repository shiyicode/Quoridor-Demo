//
//  connection.h
//  AsioServer
//
//  Created by shiyi on 2016/12/26.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef connection_H
#define connection_H

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "sync_queue.h"
#include "message.h"

class connection : protected boost::noncopyable,
                   public boost::enable_shared_from_this<connection>
{
public:
    static std::map<std::string, boost::shared_ptr<connection>> map_connection;

    explicit connection(boost::asio::io_service& io_service);

    ~connection();

    boost::asio::ip::tcp::socket& socket();
    
    //开始对该连接的异步操作
    void start();
    
    void add_write_message(message& x);

    std::string name();

    void name(std::string);
    
private:
    void handle_read();
    
    void read_body(const boost::system::error_code &e);
    
    void write();
    
    void handle_write(const boost::system::error_code& e);
    
    void handle_work(const boost::system::error_code& e);
    
    message m_read_message;

    std::string m_name;
    
    sync_queue m_write_queue;
    
    boost::asio::ip::tcp::socket m_socket;
};


using connection_ptr = boost::shared_ptr<connection>;

#endif /* connection_H */
