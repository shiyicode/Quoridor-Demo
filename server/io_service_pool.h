//
//  io_service_pool.h
//  AsioServer
//
//  Created by shiyi on 2016/12/26.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef io_service_pool_H
#define io_service_pool_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class io_service_pool : protected boost::noncopyable
{
public:
    //构造调度池
    explicit io_service_pool(std::size_t pool_size);
    
    //运行调度池中的所有调度器
    void run();
    
    //停止调度池中的所有调度器
    void stop();
    
    //获取一个调度器
    boost::asio::io_service& get_io_service();

private:

    using io_service_ptr = boost::shared_ptr<boost::asio::io_service>;
    using work_ptr = boost::shared_ptr<boost::asio::io_service::work>;
    
    //调度池实体
    std::vector<io_service_ptr> m_io_services;
    
    //保证调度器一直运行
    std::vector<work_ptr> m_works;
    
    //下一个调度器
    std::size_t m_next_io_service;
};

#endif /* io_service_pool_H */
