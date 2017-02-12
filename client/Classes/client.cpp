
//
//  client.cpp
//  AsioClient
//
//  Created by shiyi on 2016/12/28.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "client.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "cocos2d.h"
#include <json.h>

USING_NS_CC;

const std::string ip = "127.0.0.1";
const std::string port = "10089";

static boost::asio::io_service IOS;

client::client()
    : m_now_layer(nullptr),
      m_socket(IOS),
      m_work(IOS)
{
    boost::shared_ptr<boost::thread> thread(
                                            new boost::thread(boost::bind(
                                                                          &boost::asio::io_service::run,
                                                                          &IOS)));
    connect(ip, port);
}

client::~client()
{
}

client& client::get()
{
    static client instance;
    return instance;
}

void client::connect(const std::string& ip, const std::string& port)
{
    //解析主机地址
    boost::asio::ip::tcp::resolver resolver(m_socket.get_io_service());
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), ip, port);
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
    //异步连接
    m_socket.async_connect(*iterator, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
}

void client::handle_connect(const boost::system::error_code& e)
{
    if(e)
    {
        std::cout<<e.message()<<std::endl;
        return;
    }
    log("连接成功");
    
    handle_read();
}

void client::write(std::string json)
{
    m_write_message.init(json);
    
    std::cout<<"write:"<<m_write_message.data()<<std::endl;
    
    boost::asio::async_write(m_socket, boost::asio::buffer(m_write_message.data(), m_write_message.length()), boost::bind(&client::handle_write, this, boost::asio::placeholders::error));
}

boost::asio::ip::tcp::socket& client::socket()
{
    return m_socket;
}

void client::handle_read()
{
    const boost::system::error_code e;
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(m_read_message.data(), 4),
                            boost::bind(&client::read_body,
                                        this,
                                        boost::asio::placeholders::error));
}

void client::read_body(const boost::system::error_code &e)
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
                            boost::bind(&client::handle_work,
                                        this,
                                        boost::asio::placeholders::error));

}

void client::handle_work(const boost::system::error_code &e)
{
    if(e)
    {
        std::cout<<e.message()<<std::endl;
        return;
    }
    char data[m_read_message.body_length()+1];
    std::strncpy(data, m_read_message.body(), m_read_message.body_length()+1);
    std::cout<<data<<std::endl;
    
    Json::Reader reader;
    Json::Value json;
    if(reader.parse(m_read_message.body(), json))
    {
        std::string type = json["type"].asString();
        
        if(type == "login")
        {
            std::string result = json["result"].asString();
            if(result == "true")
            {
                log("login succeed");
            }
            else
            {
                log("login failure");
            }
                
        }
        else
        {
            log("else");
        }
    
        
    }
    
    handle_read();
}

void client::handle_write(const boost::system::error_code& e)
{
    std::cout<<"handle_write"<<std::endl;
}

void client::close()
{
    m_socket.close();
}

void client::now_layer(Layer* layer)
{
    m_now_layer = layer;
}

Layer* client::now_layer()
{
    return m_now_layer;
}

void client::now_layer_name(std::string name)
{
    m_layer_name = name;
}

std::string client::now_layer_name()
{
    return m_layer_name;
}
