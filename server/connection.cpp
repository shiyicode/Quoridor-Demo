//
//  connection.cpp
//  AsioServer
//
//  Created by shiyi on 2016/12/26.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "connection.h"
#include <boost/bind.hpp>
#include <iostream>
#include "action/action.h"
#include "factory.hpp"

std::map<std::string, boost::shared_ptr<connection>> connection::map_connection;

connection::connection(boost::asio::io_service& io_service)
    : m_socket(io_service),
      m_write_queue(100),
      m_name()
{
}

connection::~connection()
{
    std::cout<<"~connection"<<std::endl;
    map_connection.erase(m_name);
}

std::string connection::name()
{
    return m_name;
}

void connection::name(std::string name)
{
    m_name = name;
}

boost::asio::ip::tcp::socket& connection::socket()
{
    return m_socket;
}

void connection::start()
{
    std::cout<<"connection new"<<std::endl;
    handle_read();
}

void connection::add_write_message(message& x)
{
    bool isEmpty = m_write_queue.push(x);
    if(isEmpty)
    {
        write();
    }
}

void connection::handle_read()
{
    boost::system::error_code e;
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(m_read_message.data(), 4),
                            boost::bind(&connection::read_body,
                                        shared_from_this(),
                                        boost::asio::placeholders::error));
}

void connection::read_body(const boost::system::error_code &e)
{
    if(e)
    {
        std::cout<<e.message()<<std::endl;
        return;
    }
    bool flag = m_read_message.decode_header();
    //生成包体长度不合法，停止服务
    if(!flag)
        return;
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(m_read_message.body(),
                                                m_read_message.body_length()),
                            boost::bind(&connection::handle_work,
                                        shared_from_this(),
                                        boost::asio::placeholders::error));
}

void connection::handle_work(const boost::system::error_code &e)
{
    if(e)
    {
        std::cout<<e.message()<<std::endl;
        return;
    }
//    char data[m_read_message.body_length()+1];
//    std::strncpy(data, m_read_message.body(), m_read_message.body_length()+1);
//    std::cout<<data<<std::endl;

    std::cout<<m_read_message.data()<<std::endl;

    Json::Reader reader;
    Json::Value json;
    if(reader.parse(m_read_message.body(), json))
    {
        std::string type = json["type"].asString();
        boost::shared_ptr<action> action(factory::produce(type));
        action->doAction(json, this);
    }

    handle_read();
}

void connection::write()
{
    std::cout<<"write"<<std::endl;
    message write_message = m_write_queue.front();
    std::cout<<write_message.data()<<std::endl;
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(write_message.data(), write_message.length()),
                             boost::bind(&connection::handle_write, shared_from_this(), boost::asio::placeholders::error));
}

void connection::handle_write(const boost::system::error_code &e)
{
    if(e)
    {
        std::cout<<e.message()<<std::endl;
        return;
    }
    m_write_queue.pop();
    if(!m_write_queue.empty())
        write();
}
