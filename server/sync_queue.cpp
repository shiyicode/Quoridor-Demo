//
//  sync_queue.cpp
//  AsioServer
//
//  Created by shiyi on 2016/12/29.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "sync_queue.h"

sync_queue::sync_queue(std::size_t max_size)
    : m_isStop(false),
      m_max_size(max_size)
{
    
}

sync_queue::~sync_queue()
{
    std::cout<<"队列析构"<<std::endl;
    stop();
}

bool sync_queue::push(message& x)
{
    return add(std::move(x));
}

bool sync_queue::push(message&& x)
{
    return add(std::forward<message>(x));
}

message& sync_queue::front()
{
    std::unique_lock<std::mutex> locker(m_mutex);
    return m_queue.front();
}

void sync_queue::pop()
{
    std::unique_lock<std::mutex> locker(m_mutex);
    m_queue.pop();
    
    m_notFull.notify_one();
}

bool sync_queue::empty()
{
    std::lock_guard<std::mutex> lucker(m_mutex);
    return m_queue.size() == 0;
}

void sync_queue::stop()
{
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_isStop = true;
    }
    m_notFull.notify_all();
}

bool sync_queue::full()
{
    return m_max_size <= m_queue.size();
}

bool sync_queue::add(message&& x)
{
    std::unique_lock<std::mutex> locker(m_mutex);
    m_notFull.wait(locker, [this]{
        return m_isStop || !full();
    });

    if(m_isStop)
    {        std::cout<<"sync_stop"<<std::endl;

        //return false;
    }
    bool isEmpty = m_queue.size() == 0;

    m_queue.push(std::forward<message>(x));
    return isEmpty;
}
