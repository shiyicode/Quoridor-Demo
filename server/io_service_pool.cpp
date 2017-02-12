//
//  io_service_pool.cpp
//  AsioServer
//
//  Created by shiyi on 2016/12/26.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "io_service_pool.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

io_service_pool::io_service_pool(std::size_t pool_size)
    : m_next_io_service(0)
{
    if(pool_size == 0)
        throw std::runtime_error("io_service_pool size is 0");
    
    for(std::size_t i = 0; i < pool_size; ++i)
    {
        io_service_ptr io_service(new boost::asio::io_service);
        work_ptr work(new boost::asio::io_service::work(*io_service));
        m_io_services.push_back(io_service);
        m_works.push_back(work);
    }
}

void io_service_pool::run()
{
    //创建线程池去执行所有调度器
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for(std::size_t i = 0; i < m_io_services.size(); ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
               boost::bind(&boost::asio::io_service::run, m_io_services[i])));
        threads.push_back(thread);
    }
    
    //等待线程池结束
    for(std::size_t i = 0; i < threads.size(); ++i)
    {
        threads[i]->join();
    }
}

void io_service_pool::stop()
{
    //停止所有调度器
    for(std::size_t i = 0; i < m_io_services.size(); ++i)
    {
        m_io_services[i]->stop();
    }
}

boost::asio::io_service& io_service_pool::get_io_service()
{
    //计数器轮询
    boost::asio::io_service& io_service = *m_io_services[m_next_io_service];
    ++m_next_io_service;
    if(m_next_io_service == m_io_services.size())
        m_next_io_service = 0;
    return io_service;
}
