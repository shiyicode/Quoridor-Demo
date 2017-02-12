//
//  server.cpp
//  AsioServer
//
//  Created by shiyi on 2016/12/26.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "server.h"
#include <boost/bind.hpp>

server::server(const std::string& address, const std::string& port, std::size_t io_service_pool_size)
    : m_io_service_pool(io_service_pool_size),
      m_signals(m_io_service_pool.get_io_service()),
      m_acceptor(m_io_service_pool.get_io_service()),
      m_new_connection()
{
    m_signals.add(SIGINT);
    m_signals.add(SIGTERM);
    m_signals.async_wait(boost::bind(&server::handle_stop, this));
    
    boost::asio::ip::tcp::resolver resolver(m_acceptor.get_io_service());
    boost::asio::ip::tcp::resolver::query query(address, port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();
    
    start_accept();
    
    std::cout<<"server start"<<std::endl;
}

void server::run()
{
    m_io_service_pool.run();
}

void server::start_accept()
{
    m_new_connection.reset(new connection(m_io_service_pool.get_io_service()));
    m_acceptor.async_accept(m_new_connection->socket(),
                            boost::bind(&server::handle_accept,
                                        this,
                                        boost::asio::placeholders::error));
}

//异步接收回调
void server::handle_accept(const boost::system::error_code& e)
{
    if(e)
    {
        std::cout<<e.message()<<std::endl;
        start_accept();
        return;
    }
    m_new_connection->start();
    start_accept();
}

//停止运行
void server::handle_stop()
{
    m_io_service_pool.stop();
}
