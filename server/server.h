//
//  server.h
//  AsioServer
//
//  Created by shiyi on 2016/12/26.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef server_H
#define server_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/system/error_code.hpp>
#include "io_service_pool.h"
#include "connection.h"

class server : protected boost::noncopyable
{
public:
    explicit server(const std::string& address, const std::string&, std::size_t io_service_pool_size);
 
    //运行调度池
    void run();
    
private:
    //启动异步接收
    void start_accept();
    
    //异步接收回调
    void handle_accept(const boost::system::error_code& e);
    
    //停止运行
    void handle_stop();
    
    //调度池
    io_service_pool m_io_service_pool;

    //信号集合
    boost::asio::signal_set m_signals;
    
    //连接器
    boost::asio::ip::tcp::acceptor m_acceptor;
    
    //下一个连接
    connection_ptr m_new_connection;
    
};

#endif /* server_H */
